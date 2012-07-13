/**
 * ======================== legal notice ======================
 * 
 * File:      AbstractSocket.cc
 * Created:   4. Juli 2012, 07:13
 * Author:    <a href="mailto:geronimo013@gmx.de">Geronimo</a>
 * Project:   libnetworking: classes for tcp/ip sockets and http-protocol handling
 * 
 * CMP - compound media player
 * 
 * is a client/server mediaplayer intended to play any media from any workstation
 * without the need to export or mount shares. cmps is an easy to use backend
 * with a (ready to use) HTML-interface. Additionally the backend supports
 * authentication via HTTP-digest authorization.
 * cmpc is a client with vdr-like osd-menues.
 * 
 * Copyright (c) 2012 Reinhard Mantey, some rights reserved!
 * published under Creative Commons by-sa
 * For details see http://creativecommons.org/licenses/by-sa/3.0/
 * 
 * The cmp project's homepage is at http://projects.vdr-developer.org/projects/cmp
 * 
 * --------------------------------------------------------------
 */
#include <AbstractSocket.h>
#include <Logging.h>
#include <stddef.h>
#include <arpa/inet.h>
#include <resolv.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <poll.h>

cAbstractSocket::cAbstractSocket(int Port, int Queue)
 : sock(-1)
 , queue(Queue)
 , blocking(true)
 , thisSide(NULL)
{
}

cAbstractSocket::cAbstractSocket(const char *ServerName, int Port)
 : sock(-1)
 , queue(0)
 , blocking(true)
 , thisSide(NULL)
{
   others.push_back(new cConnectionPoint(ServerName, Port));
}

cAbstractSocket::~cAbstractSocket()
{
  Close();
  if (thisSide) delete thisSide;
  cConnectionPoint *p;

  for (size_t i=0; i < others.size(); ++i) {
      p = others[i];
      delete p;
      }
}

void cAbstractSocket::Close(void)
{
  if (sock >= 0) {
     close(sock);
     sock = -1;
     }
}

// the client side
bool cAbstractSocket::Connect(void)
{
  if (sock < 0) {
     struct addrinfo hints, *result, *rp;
     char buf[20];
     int s;

     /* Obtain address(es) matching host/port */
     memset(buf, 0, sizeof(buf));
     memset(&hints, 0, sizeof(struct addrinfo));
     hints.ai_family = AF_UNSPEC;   // Allow IPv4 or IPv6
     hints.ai_socktype = SOCK_STREAM;
     snprintf(buf, sizeof(buf), "%d", OtherSide()->Port());

     if ((s = getaddrinfo(OtherSide()->HostName(), buf, &hints, &result))) {
        esyslog("getaddrinfo: %s", gai_strerror(s));

        return -1;
        }

     // getaddrinfo potentially returns a list of addresses, that may fit,
     // so try each address until we successfully connect
     for (rp = result; rp; rp = rp->ai_next) {
         sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
         if (sock == -1) continue;

         if (connect(sock, rp->ai_addr, rp->ai_addrlen) != -1)
            break; // we got a connection
         close(sock);
         }
     if (rp == NULL) { // no address could be connected to
        esyslog("Could not connect!");
        Close();

        return false;
        }
     // here we have a valid connection, so lets gather some information
     thisSide = GetNameAndAddress(sock, rp->ai_addr, rp->ai_addrlen);
     OtherSide()->SetSocket(sock);
     char nameBuf[512];

     memset(nameBuf, 0, sizeof(nameBuf));
     if ((s = getnameinfo(rp->ai_addr, rp->ai_addrlen, nameBuf, sizeof(nameBuf), NULL, 0, NI_NAMEREQD))) {
        esyslog("failed to determine servers hostname %s", gai_strerror(s));
        }
     else {
        OtherSide()->SetRealName(nameBuf);
        }
     freeaddrinfo(result);
     }
  return sock > 0;
}

// as each address may be IP4 or IP6, cut this off
static void * getAddr(struct sockaddr *sa)
{
  if (sa->sa_family == AF_INET)
     return &(((struct sockaddr_in*)sa)->sin_addr);
  return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

// same is true for port access
static int getPort(struct sockaddr *sa)
{
  if (sa->sa_family == AF_INET)
     return ((struct sockaddr_in*)sa)->sin_port;
  return ((struct sockaddr_in6*)sa)->sin6_port;
}

cConnectionPoint *cAbstractSocket::GetNameAndAddress(int Socket, struct sockaddr *sa, socklen_t sa_size)
{
  cConnectionPoint *rv = NULL;
  char nameBuf[512], addrBuf[INET6_ADDRSTRLEN];

  if (getnameinfo(sa, sa_size, nameBuf, sizeof(nameBuf), NULL, 0, NI_NAMEREQD)) {
     // ok, just ip address has to suffice to start work
     rv = new cConnectionPoint(inet_ntop(sa->sa_family, getAddr(sa), addrBuf, sizeof(addrBuf))
                                  , ntohs(getPort(sa))
                                  , inet_ntop(sa->sa_family, getAddr(sa), addrBuf, sizeof(addrBuf)));
     }
  else {
     rv = new cConnectionPoint(inet_ntop(sa->sa_family, getAddr(sa), addrBuf, sizeof(addrBuf))
                                  , ntohs(getPort(sa))
                                  , nameBuf);
     }
  if (rv) rv->SetSocket(Socket);

  return rv;
}

void cAbstractSocket::SetBlockingIO(bool ForceBlockingIO)
{
  blocking = ForceBlockingIO;
}

// server side first part
bool cAbstractSocket::Open(int Port)
{
  if (sock < 0) {
     isyslog("socket is < 0 - so start a new connection ...");
     struct addrinfo hints, *result, *rp;
     char buf[20];
     int s;

     memset(&hints, 0, sizeof(hints));
     memset(buf, 0, sizeof(buf));
     hints.ai_family = AF_UNSPEC;     // allow IPv4 or IPv6
     hints.ai_socktype = SOCK_STREAM;
     hints.ai_flags = AI_PASSIVE;
     snprintf(buf, sizeof(buf), "%d", Port);

     if ((s = getaddrinfo(NULL, buf, &hints, &result))) {
        esyslog("getaddrinfo: %s\n", gai_strerror(s));

        return false;
        }
     int yes=1;

     // getaddrinfo potentially returns a list of addresses, that may fit,
     // so try each address until we successfully bound
     for (rp = result; rp; rp = rp->ai_next) {
         sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
         if (sock == -1) continue;

         setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

         if (bind(sock, rp->ai_addr, rp->ai_addrlen) != -1)
            break; // ok, we succeeded to bind
         close(sock);
         }
     if (!rp) {
        esyslog("could not bind");
        Close();

        return false;
        }
     ConfigureSocket(sock);
     freeaddrinfo(result);

     // listen to the socket:
     if (listen(sock, queue) < 0) {
        esyslog("failed to listen to bound socket!");
        Close();
        return (false);
        }
     }
  return (true);
}

// server side second part
cConnectionPoint *cAbstractSocket::Accept(int Port, int TimeoutMs)
{
  cConnectionPoint *client = NULL;

  if (Open(Port)) {
     struct sockaddr_storage clientname;
     uint cl_size = sizeof(clientname);
     struct pollfd pf[1];

     pf[0].fd = sock;
     pf[0].events = POLLIN;

     if (poll(pf, 1, TimeoutMs) < 1) return NULL;
     int  newsock = accept(sock, (struct sockaddr *) &clientname, &cl_size);

     if (newsock > 0) {
        isyslog("ok, got client connection request ...");

        // if server address has not been restricted at bind-time, its possible that we don't
        // have a local address yet. If server is bound to 0 (any address), we can determine
        // the real server address in use now. But only do it once.
        if (!thisSide) {
           struct sockaddr_storage server;
           uint sa_size = sizeof(server);

           if (getpeername(newsock, (struct sockaddr *) &server, &sa_size)) {
              esyslog("getpeername failed: #%d", errno);
              }
           else thisSide = GetNameAndAddress(newsock, (struct sockaddr *) &server, sa_size);
           }

        // At server side, multiple clients can have open connections at the same time,
        // so get rid of that here. We always fetch connections informations
        // before any access decisions, so those could be extended to use names
        // some day ...
        client = GetNameAndAddress(newsock, (struct sockaddr *) &clientname, cl_size);
        if (client) {
           bool accepted = true;
           //FIXME: change determination of accepting client access!
           // accepted = SVDRPhosts.Acceptable(clientname.sin_addr.s_addr);
           // change to:
           // accepted = SVDRPHosts.Acceptable(cpi);
           // so in SVDRPHosts you have IP-Address and real name (if accessible)

           if (!accepted) {
              const char *s = "Access denied!\n";

              if (write(newsock, s, strlen(s)) < 0) {
                 esyslog(s);
                 close(newsock);
                 }
              newsock = -1;
              client = NULL;
              }
           else {
              others.push_back(client);
              }
           isyslog("connect from %s, port %hu - %s", client->HostName(), client->Port(), accepted ? "accepted" : "DENIED");
           }
        }
     else if (errno != EINTR && errno != EAGAIN) {
        esyslog("failed to accept client");
        }
     }
  return (client);
}

/**
 * ======================== legal notice ======================
 *
 * File:      ServerSocket.cc
 * Created:   4. Juli 2012, 07:28
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
#include <ServerSocket.h>
#include <Logging.h>
#include <fcntl.h>

cServerSocket::cServerSocket(int Port, int Queue)
 : cAbstractSocket(Port, Queue)
 , port(Port)
 , active(false)
{
}

cServerSocket::~cServerSocket()
{
}

bool cServerSocket::Open(void)
{
  bool rv = cAbstractSocket::Open(port);

  if (rv) active = true;

  return rv;
}

void cServerSocket::Close(void)
{
  active = false;
  cAbstractSocket::Close();
}

cConnectionPoint *cServerSocket::Accept(void)
{
  cConnectionPoint *rv = NULL;

  while (active && !rv) {
        rv = cAbstractSocket::Accept(port, 500);
        }
  return rv;
}

void cServerSocket::ConfigureSocket(int Socket)
{
  if (!ForceBlockingIO()) {
     // make it non-blocking:
     int oldflags = fcntl(Socket, F_GETFL, 0);

     if (oldflags < 0) {
        esyslog("could not retrieve old socket flags");

        return;
        }

     oldflags |= O_NONBLOCK;
     if (fcntl(Socket, F_SETFL, oldflags) < 0) {
        esyslog("failed to set nonblocking state of socket");

        return;
        }
     }
}

void cServerSocket::SetBlockingIO(bool ForceBlockingIO)
{
  cAbstractSocket::SetBlockingIO(ForceBlockingIO);
}

bool cServerSocket::ForceBlockingIO() const
{
  return cAbstractSocket::ForceBlockingIO();
}

void cServerSocket::SetPort(int Port)
{
  if (active) {
     esyslog("ERROR: server socket is already active! Can't change port settings!");
     return;
     }
  port = Port;
}
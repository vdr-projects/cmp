/**
 * ======================== legal notice ======================
 * 
 * File:      AbstractSocket.h
 * Created:   4. Juli 2012, 07
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
#ifndef ABSTRACTSOCKET_H
#define	ABSTRACTSOCKET_H

#include <ConnectionPoint.h>
#include <sys/socket.h>

class cAbstractSocket {
public:
  virtual ~cAbstractSocket();
  const cConnectionPoint *ThisSide(void) const { return thisSide; }
  const cConnectionPoint *OtherSide(void) const { return others[0]; }
  cConnectionPoint *ThisSide(void) { return thisSide; }
  cConnectionPoint *OtherSide(void) { return others[0]; }
  virtual void ConfigureSocket(int Socket) {}

protected:
  cAbstractSocket(int Port, int Queue = 1);
  cAbstractSocket(const char *ServerName, int Port);
  bool ForceBlockingIO(void) const { return blocking; }
  void SetBlockingIO(bool ForceBlockingIO = true);
  cConnectionPoint *GetNameAndAddress(int Socket, struct sockaddr *sa, socklen_t sa_size);
  virtual cConnectionPoint *Accept(int Port, int TimeoutMs = -1);
  virtual bool Connect();
  virtual bool Open(int Port);
  virtual void Close(void);

private:
  int sock;
  int queue;
  bool blocking;
  cConnectionPoint *thisSide;
  ConnectionPointList others; ///< client sockets have only one other side,
  ///< but server sockets can have multiple connections open at the same time,
  ///< so we probabely need a container here.
  //  cConnectionPointInfo *FetchLocalInfo(int Socket, struct addrinfo *AI);
  };

#endif	/* ABSTRACTSOCKET_H */


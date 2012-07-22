/**
 * ======================== legal notice ======================
 * 
 * File:      ClientSocket.h
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
#ifndef CLIENTSOCKET_H
#define	CLIENTSOCKET_H

#include <AbstractSocket.h>

class cClientSocket : public cAbstractSocket {
public:
  cClientSocket(const char *serverName, int Port);
  virtual ~cClientSocket();
  bool Connect(void);
  void Close(void);
  };

#endif	/* CLIENTSOCKET_H */


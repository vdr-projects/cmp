/**
 * ======================== legal notice ======================
 * 
 * File:      ServerSocket.h
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
#ifndef SERVERSOCKET_H
#define	SERVERSOCKET_H

#include <AbstractSocket.h>

class cServerSocket : public cAbstractSocket {
public:
  cServerSocket(int Port, int Queue = 1);
  virtual ~cServerSocket();
  bool Open(void);
  bool Active(void) const { return active; }
  void SetActive(bool Active = true) { active = Active; }
  cConnectionPoint *Accept(void);
  int Port(void) const { return port; }
  int ReUseAddress(void) const;
  void SetReUseAddress(int ReUse);
  void ConfigureSocket(int Socket);
  bool ForceBlockingIO(void) const;
  void SetBlockingIO(bool ForceBlockingIO = true);

private:
  int port; ///< in case we plenty open and close server sockets
  ///< we need a place to remember the server port
  bool active;
  };

#endif	/* SERVERSOCKET_H */


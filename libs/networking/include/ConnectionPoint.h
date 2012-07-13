/**
 * ======================== legal notice ======================
 * 
 * File:      ConnectionPoint.h
 * Created:   4. Juli 2012, 06:29
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
#ifndef CONNECTIONPOINT_H
#define	CONNECTIONPOINT_H

#include <stddef.h>
#include <vector>

class cConnectionPoint {
public:
  cConnectionPoint(const char *NameOrIP, int Port, const char *RealName = NULL);
  virtual ~cConnectionPoint();
  
  int IOWait(long MilliSeconds = 300);
  const char *HostName(void) const { return nameOrIP; }
  const char *RealName(void) const { return realName ? realName : "unknown"; }
  const char *ToString() const { return combined ? combined : AssembleCombined(); }
  int Port(void) const { return port; }
  int Socket(void) const { return sock; }

private:
  char *nameOrIP;
  char *realName;
  mutable char *combined;
  int port;
  int sock;
  const char *AssembleCombined(void) const;
  void Close(void);
  void SetSocket(int Socket) { sock = Socket; }
  void SetRealName(const char *Name);
  friend class cAbstractSocket;
  friend class cConnectionHandler;
  };

typedef std::vector<cConnectionPoint *> ConnectionPointList;

#endif	/* CONNECTIONPOINT_H */


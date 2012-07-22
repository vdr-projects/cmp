/**
 * ======================== legal notice ======================
 * 
 * File:      HTTPServer.h
 * Created:   4. Juli 2012, 12
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
#ifndef HTTPSERVER_H
#define	HTTPSERVER_H

#include <ServerConfig.h>
#include <Mutex.h>
#include <vector>

class cThread;
class cHTTPServer /* : public cThread */ {
public:
  cHTTPServer(cServerConfig &Config);
  ~cHTTPServer();

  bool Start(void);
  void Stop(void);

protected:
  void Action(void);
  bool AuthorizationRequired(void) const { return config.AuthorizationRequired(); }
  bool Running(void);
  cServerSocket &ServerSocket() { return config.server; }

private:
#ifdef LIVE_CLEANUP
  void Cleanup(cThread *ThreadContext);
  static int cleanerThread(void *opaque, cThread *ThreadContext);
  cThread *cleaner;
  cMutex poolMutex;
#else
  void Cleanup();
#endif
  cServerConfig &config;
  std::vector<cThread *> *threads;
  };

#endif	/* HTTPSERVER_H */


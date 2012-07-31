/**
 * ======================== legal notice ======================
 * 
 * File:      HTTPRequestHandler.h
 * Created:   4. Juli 2012, 15
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
#ifndef HTTPREQUESTHANDLER_H
#define	HTTPREQUESTHANDLER_H

class cHTTPRequest;
class cHTTPResponse;
class cStringBuilder;
class cHTTPRequestHandler {
public:
  cHTTPRequestHandler();
  virtual ~cHTTPRequestHandler();

  virtual cHTTPResponse *ProcessRequest(cHTTPRequest &Request) = 0;
  virtual void Usage(cStringBuilder &sb) = 0;
  const char *ID() const { return prefix; }

private:
  void SetID(const char *UrlPrefix);
  char *prefix;
  friend class cHTTPRequestHandlers;
  };

#endif	/* HTTPREQUESTHANDLER_H */


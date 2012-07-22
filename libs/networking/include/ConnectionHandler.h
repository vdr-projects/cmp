/**
 * ======================== legal notice ======================
 * 
 * File:      ConnectionHandler.h
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
#ifndef CONNECTIONHANDLER_H
#define	CONNECTIONHANDLER_H

#include <Thread.h>
#include <ServerConfig.h>
#include <sys/types.h>

class cConnectionPoint;
class cAuthorization;
class cHTTPResponse;
class cHTTPRequest;
class cFileHandler;
class cHTTPRequestHandler;
class cStringBuilder;
class cConnectionHandler : public cThread {
public:
  cConnectionHandler(cConnectionPoint &Client, cServerConfig &Config, bool StayConnected = false);
  virtual ~cConnectionHandler();

  void Action(void);

  bool AuthorizationRequired(void) { return config.AuthorizationRequired(); }
  const char *NOnce(void) const { return nonce; }
  bool StayConnected(void) const { return stayConnected; }
  virtual void Cancel(int WaitSeconds = 0);

  static void RegisterRequestHandler(const char *UrlPrefix, cHTTPRequestHandler *CommandHandler);
  static void RegisterDefaultHandler(cHTTPRequestHandler *DefaultHandler);
  static void Cleanup(void);

protected:
  cAuthorizations &Authorizations(void) { return config.authorizations; }
  cServerSocket &ServerSocket(void) { return config.server; }
  cHTTPResponse *ProcessRequest(cHTTPRequest &Request);
  void TransferResponse(cHTTPResponse *Response);
  void SetNonce(char *NOnce) { nonce = NOnce; }
  bool IsAuthorizationValid(cAuthorization *ServerAuth, const cHTTPRequest &request);
  void Usage(cStringBuilder &sb);

private:
  void Init(void);
  cServerConfig &config;
  cConnectionPoint &client;
  unsigned long connectionNumber;
  size_t bufSize;
  char *scratch;
  char *nonce;
  bool stayConnected;
  friend class cTestUnit;
  };

#endif	/* CONNECTIONHANDLER_H */


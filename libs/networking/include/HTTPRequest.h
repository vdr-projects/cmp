/**
 * ======================== legal notice ======================
 * 
 * File:      HTTPRequest.h
 * Created:   3. Juli 2012, 17:54
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
#ifndef HTTPREQUEST_H
#define	HTTPREQUEST_H

#include <HTTPMessage.h>
#include <Url.h>

class cHTTPResponse;
class cHTTPRequest : public cHTTPMessage {
///< a message sent from client to server to access a certain resource
public:
  typedef enum { INVALID, GET, POST } HTTPRequestMethod;
  cHTTPRequest(const char *MessageBuf);
  cHTTPRequest(HTTPRequestMethod Format, const char *Url);
  cHTTPRequest(const cHTTPResponse &res, const char *Url);
  virtual ~cHTTPRequest();
  HTTPRequestMethod Method(void) const { return method; }
  const cUrl &Url() const { return url; }
  cUrl &Url() { return url; }
  const char *UserAgent() const;
  const char *ClientHost(void) const;
  void SetUser(const char *UserID, const char *Password);

protected:
  void SetMethod(HTTPRequestMethod Method) { method = Method; }
  void SetURL(const char *Url);
  virtual size_t WriteFirstLine(char *Buffer, size_t BufSize);
  void ParseMessage(const char *MessageBuf);

private:
  HTTPRequestMethod method;
  cUrl url;
  friend class HTTPParser;
  };

extern const char *requestMethod2String(cHTTPRequest::HTTPRequestMethod Method);

#endif	/* HTTPREQUEST_H */


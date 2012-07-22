/**
 * ======================== legal notice ======================
 * 
 * File:      HTTPMessage.h
 * Created:   3. Juli 2012, 17
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
#ifndef HTTPMESSAGE_H
#define	HTTPMESSAGE_H

#define MT_Html         "text/html"

#include <ManagedMap.h>

class cAuthorization;
class cHTTPMessage {
public:
  typedef enum { Unknown, HTTP_1_0, HTTP_1_1 } HTTPProtocol;

  cHTTPMessage(HTTPProtocol Proto=HTTP_1_1);
  virtual ~cHTTPMessage();

  HTTPProtocol Protocol(void) { return protocol; }
  const char *ProtocolString(void);
  const char *ContentType(void) const { return contentType; }
  virtual size_t ContentSize(void) const;
  const char *GetHeader(const char *Name) const;
  const cAuthorization *Authorization(void) const { return auth; }
  void SetAuthorization(cAuthorization *Authorization);
  size_t WritePrefix(char *Buffer, size_t BufSize); ///< writes message header, so content will follow
  virtual void Dump(void);

protected:
  enum ParseState {
      ExpectFormat
    , ExpectURL
    , ExpectProtocol
    , ExpectStatus
    , ExpectHeader
    , ExpectContent
    };
  enum ParseResult {
      UnknownError
    , UnsupportedFormat
    , InvalidURL
    , InvalidName
    , UnsupportedProtocol
    , Continue
    , Done
    };
  virtual size_t WriteFirstLine(char *Buffer, size_t BufSize) = 0;
  virtual void SetContentType(const char *ContentType);
  virtual void SetContentSize(size_t ContentSize) { contentSize = ContentSize; }
  void SetHeader(const char *Name, const char *Value);
  void SetProtocol(HTTPProtocol Protocol) { protocol = Protocol; }
  cAuthorization *Authorization(void) { return auth; }
  char *FormatTime(time_t time);
  const cManagedMap &Headers() const { return header; }
  int WriteTime(char *Buffer, size_t BufSize);
  void Reset(void);

private:
  HTTPProtocol protocol;
  time_t timeStamp;
  cManagedMap header;
  cAuthorization *auth;
  size_t contentSize;
  char *contentType;
  friend class cMediaListHandler;
  friend class cConnectionHandler;
  friend class cTestUnit;
  };

#endif	/* HTTPMESSAGE_H */


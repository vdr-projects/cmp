/**
 * ======================== legal notice ======================
 * 
 * File:      HTTPResponse.h
 * Created:   4. Juli 2012, 06
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
#ifndef HTTPRESPONSE_H
#define	HTTPRESPONSE_H

#define MT_Unknown      "unsupported/unknown"
#define MT_CSS          "text/css"
#define MT_JavaScript   "application/javascript"
#define MT_Gif          "image/gif"
#define MT_Png          "image/png"
#define MT_Ico          "image/x-icon"
#define MT_Jpg          "image/jpeg"
#define MT_Xml          "application/xml"
#define MT_XmlDtd       "application/xml-dtd"

#include <HTTPStatus.h>
#include <HTTPMessage.h>
#include <StringBuilder.h>

class cHTTPResponse : public cHTTPMessage {
public:
  cHTTPResponse(HTTPStatusCode Status = HTTP_OK);
        ///< server side creates a response by status code
  cHTTPResponse(const char *Buffer);
        ///< client side creates a response from receiving buffer
  virtual ~cHTTPResponse();

  HTTPStatusCode Status(void) const { return status; }
  virtual size_t ContentSize(void) const;
  virtual void SetContentType(const char *ContentType) { cHTTPMessage::SetContentType(ContentType); }
  virtual void SetContentSize(size_t ContentSize) { cHTTPMessage::SetContentSize(ContentSize); }
  cStringBuilder &StringBuilder(void) { return content; }

  static const char *ServerID(void);
  static void SetServerID(const char *ServerID);

protected:
  virtual size_t WriteFirstLine(char *Buffer, size_t BufSize);
  void ParseMessage(const char *MessageBuf);

private:
  virtual size_t ReadContentChunk(char *Buf, size_t bufSize);
  void SetDefaultStatusBody(HTTPStatusCode Status);
  HTTPStatusCode status;
  cStringBuilder content;
  friend class cConnectionHandler;
  friend class HTTPParser;
  };

#endif	/* HTTPRESPONSE_H */


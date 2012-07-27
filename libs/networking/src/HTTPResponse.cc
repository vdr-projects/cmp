/**
 * ======================== legal notice ======================
 *
 * File:      HTTPResponse.cc
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
#include <HTTPResponse.h>
#include <Authorization.h>
#include <stddef.h>
#include <stdio.h>
#include <util.h>

static const char *serverID = NULL;
cHTTPResponse::cHTTPResponse(HTTPStatusCode Status)
 : status(Status)
 , content(512)
{
  SetHeader("Server", serverID);
  if (!(Status <= HTTP_OK /* || Status == HTTP_NoContent */ || Status == 304))
     SetDefaultStatusBody(Status);
}

cHTTPResponse::cHTTPResponse(const char *Buffer)
{
  ParseMessage(Buffer);
  if (Authorization()) Authorization()->SetServerID(ServerID());
}

cHTTPResponse::~cHTTPResponse()
{
}

size_t cHTTPResponse::ContentSize() const
{
  if (content.Size()) return content.Size();
  return cHTTPMessage::ContentSize();
}

const char * cHTTPResponse::ServerID(void)
{
  return serverID;
}

void cHTTPResponse::SetServerID(const char* ServerID)
{
  serverID = ServerID;
}

void cHTTPResponse::SetDefaultStatusBody(HTTPStatusCode Status)
{
  SetContentType(MT_Html);
  content.Append("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" "
"\"http://www.w3.org/TR/1999/REC-html401-19991224/loose.dtd\">\n"
"<HTML>\n"
"  <HEAD>\n"
"    <TITLE>Error ");
  content.Append(Status).Append("</TITLE>\n"
"    <META HTTP-EQUIV=\"Content-Type\" CONTENT=\"text/html; charset=ISO-8859-1\">\n"
"  </HEAD>\n"
"  <BODY><H1>");
  content.Append(Status).Append(" ").Append(httpStatus2Text(Status)).Append(".</H1></BODY>\n"
"</HTML>\n");
}

void cHTTPResponse::HandleAbort(void)
///< handle cases where client closes connection while transfer was in progress
{
  // default: do nothing
}

size_t cHTTPResponse::ReadContentChunk(char* Buf, size_t bufSize)
{
  return content.Copy(Buf, bufSize);
}

size_t cHTTPResponse::WriteFirstLine(char* Buffer, size_t BufSize)
{
  return snprintf(Buffer, BufSize, "%s %d %s\n", ProtocolString(), status, httpStatus2Text(status));
}

//static const char *SampleRawResponse =
//HTTP/1.1 401 Unauthorized
//Date: Tue, 29 May 2012 03:54:02 GMT
//Server: (null)
//Connection: Close
//WWW-Authenticate: Digest realm="validUsers@MyTestApp", nonce="dbe67572c707d25689a394ef7a9a9e8c", opaque="94c70a11bef0589719f190baf192bbcd", qop="auth"
//Content-Type: text/html
//Content-Length: 301

//<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/1999/REC-html401-19991224/loose.dtd">
//<HTML>
//  <HEAD>
//    <TITLE>Error</TITLE>
//    <META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=ISO-8859-1">
//  </HEAD>
//  <BODY><H1>401 Unauthorized.</H1></BODY>
//</HTML>
//
void cHTTPResponse::ParseMessage(const char *RawMessage)
{
  char scratch[512];
  const char *p = RawMessage;
  char *tmp;
  ParseState state = ExpectProtocol;
  ParseResult status = Continue;

  Reset();
  while (status == Continue) {
        memset(scratch, 0, sizeof(scratch));
        switch (state) {
          case ExpectStatus:
               p = getWord(scratch, sizeof(scratch), p);
               this->status = strtoHTTPStatus(scratch);
               p = restOfLine(scratch, sizeof(scratch), p); // just read the rest of the line
               state = ExpectHeader;
               break;

          case ExpectProtocol:
               p = getWord(scratch, sizeof(scratch), p);
               if (!strcmp(scratch, "HTTP/1.0")) {
                  SetProtocol(HTTP_1_0);
                  state = ExpectStatus;
                  }
               else if (!strcmp(scratch, "HTTP/1.1")) {
                  SetProtocol(HTTP_1_1);
                  state = ExpectStatus;
                  }
               else status = UnsupportedProtocol;
               break;

          case ExpectContent:
               printf("should read %ld bytes from %10.10s\n", ContentSize(), p);
               status = Done;
               break;

          case ExpectHeader:
               p = getWord(scratch, sizeof(scratch), p);
               if (!strncmp(p, "\n\n", 2)) {
                  p += 2;
                  state = ExpectContent;
                  break;
                  }
               if (!strncmp(p, "\r\n\r\n", 4)) {
                  p += 4;
                  state = ExpectContent;
                  break;
                  }
               tmp = scratch + strlen(scratch);
               if (*(tmp -1) == ':') {
                  *(tmp -1) = 0;
                  tmp = strdup(scratch);
                  p = restOfLine(scratch, sizeof(scratch), p);
                  if (!strcasecmp(tmp, "WWW-Authenticate") || !strcasecmp(tmp, "Authorization-Info"))
                     SetAuthorization(new cAuthorization(cHTTPRequest::GET, scratch));
                  else if (!strcasecmp(tmp, "content-type"))
                     SetContentType(scratch);
                  else if (!strcasecmp(tmp, "content-length"))
                     SetContentSize(atol(scratch));
                  else SetHeader(tmp, scratch);
                  FREE(tmp);
                  }
               else {
                  status = InvalidName;
                  }
               break;

          default: break;
          } // end switch
        } // end while (status == OK)
}


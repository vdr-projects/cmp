/**
 * ======================== legal notice ======================
 * 
 * File:      HTTPRequest.cc
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
#include <HTTPRequest.h>
#include <HTTPResponse.h>
#include <Authorization.h>
#include <Principal.h>
#include <Logging.h>
#include <util.h>
#include <stdio.h>


cHTTPRequest::cHTTPRequest(const char *MessageBuf)
 : method(INVALID)
 , url(NULL)
{
  ParseMessage(MessageBuf);
}

cHTTPRequest::cHTTPRequest(cHTTPRequest::HTTPRequestMethod Method, const char* Url)
 : method(Method)
 , url(Url)
{
}

cHTTPRequest::cHTTPRequest(const cHTTPResponse &res, const char *Url)
  : method(cHTTPRequest::GET)
  , url(Url)
{
  SetAuthorization(new cAuthorization(*res.Authorization()));
  Authorization()->SetUri(Url);
}


cHTTPRequest::~cHTTPRequest()
{
}

const char *requestMethod2String(cHTTPRequest::HTTPRequestMethod Method)
{
  switch (Method) {
    case cHTTPRequest::GET: return "GET";
    case cHTTPRequest::POST: return "POST";
    default: return "unknown/unsupported";
    }
}

void cHTTPRequest::SetURL(const char *Url)
{
  url.ParseURL(Url);
}

const char *cHTTPRequest::ClientHost(void ) const
{
  return (const char *) Headers().get("Host");
}

const char *cHTTPRequest::UserAgent() const
{
  return (const char *) Headers().get("User-Agent");
}

void cHTTPRequest::SetUser(const char *UserID, const char *Password)
{
  char *uri = Url().ToString();
  this->Authorization()->CalculateResponse(uri, UserID, Password);
  free(uri);
}

static const char *fetchLine(char *Buf, int BufSize, const char *Source)
{
  const char *end = strchr(Source, '\r');
  int len = 0;

  if (!end) end = strchr(Source, '\n');
  if (!end) end = Source + strlen(Source);
  len = end - Source;
  if (len > BufSize) len = BufSize - 1;

  strncpy(Buf, Source, len);
  Buf[len] = 0;
  end = Source + len;

  return end;
}

void cHTTPRequest::ParseMessage(const char *RequestBuf)
{
  char scratch[512];
  const char *start = RequestBuf, *end = strchr(start, ' ');
  const char *name;
  char *value;

  if (strncasecmp("GET", start, end - start)) SetMethod(GET);
  else if (strncasecmp("POST", start, end - start)) SetMethod(POST);
  start = end;
  while (*start == ' ') ++start;
  end = strchr(start, ' ');
//  printf("request-URI %*.*s\n", (int)(end - start), (int)(end - start), start);
  if ((end - start) >= (int)sizeof(scratch)) {
     esyslog("URI exhausted buffer - abort request!");
     return;
     }
  else {
     strncpy(scratch, start, end - start);
     scratch[end - start] = 0;
     SetURL(scratch);
     }
  start = end;
  while (*start == ' ') ++start;
  end = strchr(start, '\r');
  if (!end) end = strchr(start, '\n');
//  printf("http-protocol %*.*s\n", (int)(end - start), (int)(end - start), start);
  if (!strncmp("HTTP/1.1", start, end - start)) SetProtocol(HTTP_1_1);
  else SetProtocol(HTTP_1_0);

  for (start = end; start && *start; start = end) {
      if (*start == '\r') ++start;
      if (*start == '\n') ++start;
      if (!*start) break;
      end = fetchLine(scratch, sizeof(scratch), start);
//    printf("a line from request (%03d) [%s]\n", strlen(scratch), scratch);

      name = scratch;
      value = strchr((char *)name, ':');
      if (value) {
         if (value) *value++ = 0;
         if (*value == ' ') *value++ = 0;

         SetHeader(name, value);
         }
      else {
//         printf("possibly end of header ...\n");
         continue;
         }
//    printf("\nresult - name [%s] => |>%s<|\n", name, value);
      }
}

size_t cHTTPRequest::WriteFirstLine(char* Buffer, size_t BufSize)
{
  size_t n = snprintf(Buffer, BufSize, "%s ", requestMethod2String(Method()));
  int tmp = url.WriteBuf(Buffer + n, BufSize - n);

  if (tmp > 0) n += tmp;
  n += snprintf(Buffer + n, BufSize - n, " %s\n", ProtocolString());

  return n;
}


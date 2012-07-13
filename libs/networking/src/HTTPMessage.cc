/**
 * ======================== legal notice ======================
 * 
 * File:      HTTPMessage.cc
 * Created:   3. Juli 2012, 17:40
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
#include <HTTPMessage.h>
#include <Authorization.h>
#include <stdio.h>
#include <stddef.h>
#include <util.h>

static void freeHeaderCallback(void *elem)
{
  free(elem);
}

cHTTPMessage::cHTTPMessage(HTTPProtocol Proto)
 : protocol(Proto)
 , timeStamp(0)
 , header(freeHeaderCallback)
 , auth(NULL)
 , contentSize(0)
 , contentType(NULL)
{
}

cHTTPMessage::~cHTTPMessage()
{
  if (auth) delete auth;
  FREE(contentType);
}

char *cHTTPMessage::FormatTime(time_t timeStamp)
{
  struct tm *t = gmtime(&timeStamp);
  char buf[128];

  strftime(buf, sizeof(buf), "%a, %d %b %Y %H:%M:%S GMT", t);

  return strdup(buf);
}

void cHTTPMessage::SetHeader(const char *Name, const char *Value)
{
  header.put(Name, Value ? strdup(Value) : NULL);
}

const char *cHTTPMessage::GetHeader(const char* Name) const
{
  return (const char *) header.get(Name);
}

size_t cHTTPMessage::WritePrefix(char *Buffer, size_t BufSize)
///< writes message prefix to existing buffer. Prefix is the message without
///< the content body, so internal and external content will be processed
///< separately.
///< IMPORTANT: content size and content type has to be set before this call!
///<            or this information needs to be added by custom call.
{
  cManagedMap::const_iterator it = Headers().begin();
  size_t n = WriteFirstLine(Buffer, BufSize);

  strcpy(Buffer + n, "Date: ");
  n += 6;
  n += WriteTime(Buffer + n, BufSize - n);
  while (it != Headers().end()) {
        n += snprintf(Buffer + n, BufSize - n, "%s: %s\r\n", it->first.c_str(), (const char *) it->second);
        ++it;
        }
  if (auth) n += auth->Write(Buffer + n, BufSize - n);
  if (ContentSize() > 0) {
     n += snprintf(Buffer + n, BufSize - n, "Content-Type: %s\r\n", ContentType());
     n += snprintf(Buffer + n, BufSize - n, "Content-Length: %ld\r\n", ContentSize());
     if (n < BufSize - 3) {
        Buffer[n++] = '\n'; // this is the separator between header and content!
        Buffer[n] = 0;
        }
     }
  return n;
}

int cHTTPMessage::WriteTime(char *Buffer, size_t BufSize)
{
  if (!timeStamp) timeStamp = time(NULL);
  struct tm *t = gmtime(&timeStamp);

  return strftime(Buffer, BufSize, "%a, %d %b %Y %H:%M:%S GMT\r\n", t);
}

void cHTTPMessage::Reset()
{
  header.clear();
  contentSize = 0;
}

size_t cHTTPMessage::ContentSize() const
{
  return contentSize;
}

void cHTTPMessage::SetContentType(const char* ContentType)
{
  FREE(contentType);
  contentType = ContentType ? strdup(ContentType) : NULL;
}

void cHTTPMessage::SetAuthorization(cAuthorization* Authorization)
{
  if (auth) {
     delete auth;
     auth = NULL;
     }
  auth = Authorization;
}

const char *cHTTPMessage::ProtocolString(void) {
  switch (protocol) {
    case HTTP_1_0: return "HTTP/1.0";
    case HTTP_1_1: return "HTTP/1.1";
    default: return "Unknown/Unsupported";
    }
}

void cHTTPMessage::Dump(void )
{
  cManagedMap::const_iterator it = Headers().begin();
  char buf[1024];

  WriteFirstLine(buf, sizeof(buf));
  printf("=========== Dump HTTP message ==============\n");
  printf("Protocol: %s\n", ProtocolString());
  printf("first line: %s\n", buf);
  printf("header entries:\n");
  while (it != Headers().end()) {
        printf("\t[%s] ==> >|%s|<\n", it->first.c_str(), (const char *) it->second);
        ++it;
        }
  if (auth) auth->Dump();
  if (ContentSize()) {
     printf("---------- content (%ld Bytes of type %s) -------------\n"
           , ContentSize(), ContentType());
     }
  else printf(">>> NO Content!\n");
  printf("========== End Dump HTTP message ===========\n");
}


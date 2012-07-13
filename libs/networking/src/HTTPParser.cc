/**
 * ======================== legal notice ======================
 * 
 * File:      HTTPParser.cc
 * Created:   10. Juli 2012, 08:37
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
#include <HTTPParser.h>
#include <HTTPRequest.h>
#include <HTTPResponse.h>
#include <string.h>

cHTTPParser::cHTTPParser()
{
}

cHTTPParser::~cHTTPParser()
{
}

cHTTPMessage *cHTTPParser::ParseMessage(const char* MessageBuf)
{
  if (!strncmp("HTTP", MessageBuf, 4)) return new cHTTPResponse(MessageBuf);
  return new cHTTPRequest(MessageBuf);
}

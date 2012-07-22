/**
 * ======================== legal notice ======================
 * 
 * File:      HTTPParser.h
 * Created:   10. Juli 2012, 08
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
#ifndef HTTPPARSER_H
#define	HTTPPARSER_H

class cHTTPMessage;
class cHTTPRequest;
class cHTTPResponse;
class cHTTPParser
{
public:
  cHTTPParser();
  virtual ~cHTTPParser();

  cHTTPMessage *ParseMessage(const char *MessageBuf);

protected:
  cHTTPRequest *parseRequest(const char *MessageBuf);
  cHTTPResponse *parseResponse(const char *MessageBuf);

private:
};

#endif	/* HTTPPARSER_H */


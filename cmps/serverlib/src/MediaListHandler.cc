/**
 * ======================== legal notice ======================
 * 
 * File:      MediaListHandler.cc
 * Created:   5. Juli 2012, 08:06
 * Author:    <a href="mailto:geronimo013@gmx.de">Geronimo</a>
 * Project:   cmps - the backend (server) part of compound media player
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
#include <MediaListHandler.h>
#include <AbstractListAssembler.h>
#include <FilesystemScanner.h>
#include <HTTPRequest.h>
#include <HTTPResponse.h>
#include <StringBuilder.h>
#include <Logging.h>

cMediaListHandler::cMediaListHandler()
{
}

cMediaListHandler::~cMediaListHandler()
{
  AssemblerList::iterator it = listAssemblers.begin();

  while (it != listAssemblers.end()) {
        delete it->second;
        ++it;
        }
  if (defaultListAssembler) delete defaultListAssembler;
}

cAbstractListAssembler *cMediaListHandler::ListAssembler(const char* ID)
{
  if (!ID) return defaultListAssembler;
  cAbstractListAssembler *rv = listAssemblers[ID];

  if (rv) return rv;
  return defaultListAssembler;
}

cHTTPResponse *cMediaListHandler::ProcessRequest(cHTTPRequest& Request)
{
  isyslog("cMediaListHandler::ProcessRequest ...");
  cHTTPResponse *res = NULL;
  cAbstractListAssembler *la = ListAssembler(Request.Url().Parameter("format"));
  const char *hdStart = Request.Url().Parameter("start");
  const char *hdDelta = Request.Url().Parameter("limit");
  int start = 0;
  int delta = 40;

  if (hdStart) start = atol(hdStart);
  if (hdDelta) delta = atol(hdDelta);
  if (!la) return new cHTTPResponse(HTTP_NotFound);
  res = new cHTTPResponse(HTTP_OK);
  res->SetContentType(la->MediaType());
  la->AssembleList(res->StringBuilder(), FileSystemScanner()->MediaPool(), FileSystemScanner()->Categories(), start, delta);

  return res;
}

void cMediaListHandler::Usage(cStringBuilder& sb)
{
  isyslog("start of cMediaListHandler::Usage() ...");
  sb.Append("returns a list of known/supported media on this machine. To access any media from the list, ");
  sb.Append("use the path as uri (using the http protocol).<br/>");
  sb.Append("<strong>supported parameters:</strong><ul>");
  sb.Append("<dl><dt>start=#</dt>");
  sb.Append("<dd>used to step list by chunks, where <em>#</em> stands for the index of the first element to retrieve</dd>");
  sb.Append("<dt>limit=#</dt>");
  sb.Append("<dd>gives the chunksize (default is 40), where <em>#</em> stands for the number of elements to retrieve</dd>");
  sb.Append("<dt>format=json</dt>");
  sb.Append("<dd>default format is html, so if you like to get the list in json format, use this parameter</dd>");
  sb.Append("</dl></ul>");
  isyslog("end of cMediaListHandler::Usage() ...");
}

void cMediaListHandler::SetDefaultListAssembler(cAbstractListAssembler* assembler)
{
  defaultListAssembler = assembler;
}

void cMediaListHandler::SetListAssembler(const char* ID, cAbstractListAssembler* assembler)
{
  listAssemblers[ID] = assembler;
}

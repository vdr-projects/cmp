/**
 * ======================== legal notice ======================
 * 
 * File:      MediaFileHandler.cc
 * Created:   5. Juli 2012, 08
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
#include <MediaFileHandler.h>
#include <AbstractMedia.h>
#include <FilesystemScanner.h>
#include <HTTPRequest.h>
#include <HTTPMediaResponse.h>
#include <StringBuilder.h>
#include <Logging.h>

cMediaFileHandler::cMediaFileHandler()
{
}

cMediaFileHandler::~cMediaFileHandler()
{
}

cHTTPResponse *cMediaFileHandler::ProcessRequest(cHTTPRequest& Request)
{
  cAbstractMedia *media = FileSystemScanner()->FindMedia(Request.Url().Path());

  isyslog("cMediaFileHandler::ProcessRequest ... %0X", media);

  if (!media) return NULL;
  media->Refresh();

  return new cHTTPMediaResponse(media);
}

void cMediaFileHandler::Usage(cStringBuilder& sb)
{
  isyslog("start of cMediaFileHandler::Usage() ...");
  sb.Append("<dl><dt><em>");
  sb.Append("/any/path/to/media/file");
  sb.Append("</em></dt><dd>");
  sb.Append("returns the media-file ready to be played by client media-players.");
  sb.Append("</dd></dl>");
  isyslog("end of cMediaFileHandler::Usage() ...");
}
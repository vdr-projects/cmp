/**
 * ======================== legal notice ======================
 * 
 * File:      HTTPMediaResponse.cc
 * Created:   6. Juli 2012, 07:44
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
#include <HTTPMediaResponse.h>
#include <stdlib.h>

cHTTPMediaResponse::cHTTPMediaResponse(cAbstractMedia *Media)
 : cHTTPFileResponse()
 , media(Media)
{
  if (media) {
     char *lm = FormatTime(media->LastModified());

     SetHeader("LastModified", lm);
     free(lm);
     SetContentSize(media->Size());
     SetContentType(media->MimeType());
     }
}

cHTTPMediaResponse::~cHTTPMediaResponse()
{
}

size_t cHTTPMediaResponse::ReadContentChunk(char* Buf, size_t bufSize)
{
  if (!media) return 0;
  return media->ReadChunk(Buf, bufSize);
}
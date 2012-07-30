/**
 * ======================== legal notice ======================
 * 
 * File:      Movie.cc
 * Created:   2. Juli 2012, 15
 * Author:    <a href="mailto:geronimo013@gmx.de">Geronimo</a>
 * Project:   libfsScan: mediatypes and filesystem scanning
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
#include <Movie.h>
#include <stddef.h>
#include <string.h>

SupportedExtension cMovie::knownExtensions[] = {
  { "asd",  "video/x-ms-asf" },
  { "asf",  "video/x-ms-asf" },
  { "avi",  "video/x-msvideo" },
  { "dv",   "video/x-dv" },
  { "flv",  "video/x-flv" },
  { "gl",   "video/x-gl" },
  { "iso",  "application/x-iso9660-image" },
  { "ogv",  "video/ogg" },
  { "mkv",  "video/x-matroska" },
  { "mov",  "video/quicktime" },
  { "mpg", "video/mpeg" },
  { "mpeg", "video/mpeg" },
  { "swf",  "application/x-shockwave-flash" },
  { NULL, NULL }
};

cMovie::cMovie(const cFile &File, const char *Mime, SupportedMediaType Type)
 : cAbstractMedia(File, Mime, Type)
{
}

cMovie::~cMovie()
{
}

const char *cMovie::ContentType(const char* Extension)
{
  for (SupportedExtension *p = knownExtensions; p && p->extension; ++p) {
      if (!strcasecmp(p->extension, Extension))  return p->mimeType;
      }
  return NULL;
}

bool cMovie::NeedsFurtherScan(void) const
{
//TODO: common meta data: width, height, interlaced
  return true;
}

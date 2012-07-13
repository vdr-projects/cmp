/**
 * ======================== legal notice ======================
 * 
 * File:      Picture.cc
 * Created:   2. Juli 2012, 15:18
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
#include <Picture.h>
#include <stddef.h>
#include <string.h>

SupportedExtension cPicture::knownExtensions[] = {
  { "bmp",  "image/x-windows-bmp" },
  { "gif",  "image/gif" },
  { "jff",  "image/jpeg" },
  { "jfif", "image/jpeg" },
  { "jif",  "image/jpeg" },
  { "jp2",  "image/jp2" },
  { "jpe",  "image/jpeg" },
  { "jpeg", "image/jpeg" },
  { "jpg",  "image/jpeg" },
  { "jpm",  "image/jpm" },
  { "jpx",  "image/jpx" },
  { "pbm",  "image/x-portable-bitmap" },
  { "pct",  "image/x-pict" },
  { "pcx",  "image/x-pcx" },
  { "png",  "image/png" },
  { "pnm",  "image/x-portable-anymap" },
  { "ppm",  "image/x-portable-pixmap" },
  { "qti",  "image/quicktime" },
  { "ras",  "image/x-cmu-raster" },
  { "rgb",  "image/x-rgb" },
  { NULL, NULL }
};

cPicture::cPicture(const char *Name, const char *Logical, const char *Path, const char *Mime)
: cAbstractMedia(Picture, Name, Logical, Path, Mime)
{
}

cPicture::~cPicture()
{
}

const char *cPicture::ContentType(const char* Extension)
{
  for (SupportedExtension *p = knownExtensions; p && p->extension; ++p) {
      if (!strcasecmp(p->extension, Extension))  return p->mimeType;
      }
  return NULL;
}


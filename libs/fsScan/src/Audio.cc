/**
 * ======================== legal notice ======================
 * 
 * File:      Audio.cc
 * Created:   2. Juli 2012, 15:00
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
#include <Audio.h>
#include <stddef.h>
#include <string.h>

SupportedExtension cAudio::knownExtensions[] = {
  { "aac",  "audio/aac" },
  { "aif",  "audio/x-aiff" },
  { "aiff", "audio/x-aiff" },
  { "aifc", "audio/x-aiff" },
  { "au",   "audio/x-au" },
  { "fla",  "audio/flac" },
  { "flac", "audio/flac" },
  { "oga",  "audio/ogg" },
  { "ogg",  "audio/ogg" },
  { "mka",  "audio/x-matroska" },
  { "mp3",  "audio/mpeg" },
  { "mp4",  "audio/x-mpeg4" },
  { "m4a",  "audio/x-m4" },
  { "mpg",  "audio/mpeg" },
  { "mpp",  "audio/x-musepack" },
  { "ram",  "audio/x-realaudio" },
  { NULL, NULL }
};

cAudio::cAudio(const char *Name, const char *Logical, const char *Path, const char *Mime)
 : cAbstractMedia(Audio, Name, Logical, Path, Mime)
{
}

cAudio::~cAudio()
{
}

const char *cAudio::ContentType(const char* Extension)
{
  for (SupportedExtension *p = knownExtensions; p && p->extension; ++p) {
      if (!strcasecmp(p->extension, Extension))  return p->mimeType;
      }
  return NULL;
}

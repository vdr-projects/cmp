/**
 * ======================== legal notice ======================
 * 
 * File:      Audio.cc
 * Created:   2. Juli 2012, 15
 * Author:    <a href="mailto:geronimo013@gmx.de">Geronimo</a>
 * Project:   libMediaScan: mediatypes and media scanning
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
#include <StringBuilder.h>
#include <Logging.h>
#include <stddef.h>
#include <string.h>
#include <util.h>

static bool deepScanEnabled = false;

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
//  { "mpg",  "audio/mpeg" },
  { "mpp",  "audio/x-musepack" },
  { "ram",  "audio/x-realaudio" },
  { NULL, NULL }
};

cAudio::cAudio(const cFile &File, const char *Mime)
 : cAbstractMedia(File, Mime, Audio)
 , name(NULL)
{
}

cAudio::~cAudio()
{
  free(name);
}

void cAudio::AddMeta(cMediainfoReader::InfoEntry* Entry)
{
  if (!Entry) return;
  std::string name = std::get<0>(*Entry);
  std::string value = std::get<1>(*Entry);

  if (!strcmp("Bit rate", name.c_str())) width = parseInt(value);
  cAbstractMedia::AddMeta(Entry);
}

void cAudio::EnableDeepScan(bool DoScan)
{
  deepScanEnabled = DoScan;
  isyslog("cAudio::enableDeepScan(%s)", deepScanEnabled ? "true" : "false");
}

const char *cAudio::ContentType(const char* Extension)
{
  for (SupportedExtension *p = knownExtensions; p && p->extension; ++p) {
      if (!strcasecmp(p->extension, Extension))  return p->mimeType;
      }
  return NULL;
}

const char *cAudio::Name(void) const
{
  if (!name) {
     cMediainfoReader::InfoEntry *performer = NULL, *album = NULL, *track = NULL;

     for (size_t i=0; i < meta.size(); ++i) {
         cMediainfoReader::InfoEntry *ie = meta[i];
         std::string name = std::get<0>(*ie);

         if (!strcmp("Album", name.c_str())) album = ie;
         else if (!strcmp("Performer", name.c_str())) performer = ie;
         else if (!strcmp("Track name", name.c_str())) track = ie;
         }

     if (track) {
        std::string tmp = std::get<1>(*track);
        cStringBuilder sb(tmp.c_str());

        if (performer) {
           tmp = std::get<1>(*performer);
           sb.Append(" - ").Append(tmp.c_str());
           }
        if (album) {
           tmp = std::get<1>(*album);
           sb.Append(" (").Append(tmp.c_str()).Append(")");
           }
        name = sb.toString();
        }
     else {
        name = strdup(cAbstractMedia::Name());
        }
     }
  return name;
}

bool cAudio::NeedsFurtherScan(void) const
{
  return deepScanEnabled;
}

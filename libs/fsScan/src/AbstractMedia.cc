/**
 * ======================== legal notice ======================
 * 
 * File:      AbstractMedia.cc
 * Created:   2. Juli 2012, 14
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
#include <AbstractMedia.h>
#include <Logging.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <util.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

cAbstractMedia::cAbstractMedia(cAbstractMedia::SupportedMediaType Type, const char *Name, const char *Logical, const char *Path, const char *Mime)
 : fd(-1)
 , mediaType(Type)
 , logicalPath(Logical ? strdup(Logical) : NULL)
 , realPath(Path ? strdup(Path) : NULL)
 , name(Name ? strdup(Name) : NULL)
 , mimeType(Mime ? strdup(Mime) : NULL)
 , lastModified(0)
 , size(0)
{
}

cAbstractMedia::~cAbstractMedia()
{
  free(logicalPath);
  free(realPath);
  free(name);
  free(mimeType);
}

void cAbstractMedia::Refresh(void)
{
}

size_t cAbstractMedia::ReadChunk(char* Buf, size_t bufSize)
{
  long rv = 0;

  if (fd < 1) { // fp stays open between various calls
     fd = open(RealPath(), O_RDONLY | O_LARGEFILE);
     if (fd < 1) {
        esyslog("could not open requested path %s - Error #%d", RealPath(), errno);
        return 0;
        }
     }
  isyslog("have filehandle #%d (%s)", fd, RealPath());
  if ((rv = read(fd, Buf, bufSize)) < 0)
     esyslog("ERROR: failed to read from file %s #%d", RealPath(), errno);
  else
     isyslog("read %u bytes from file", rv);
  if (rv < (long) bufSize) { // most probabely end of file
     close(fd);
     }
  return rv;
}

const char *cAbstractMedia::MediaType2Text(int Type)
{
  switch(Type) {
  case Audio:              return TO_STRING(Audio);
  case Movie:              return TO_STRING(Movie);
  case DVDImage:           return TO_STRING(DVDImage);
  case LegacyVdrRecording: return TO_STRING(LegacyVdrRecording);
  case VdrRecording:       return TO_STRING(VdrRecording);
  case Picture:            return TO_STRING(Picture);
  default:                 return TO_STRING(Invalid);
  }
}
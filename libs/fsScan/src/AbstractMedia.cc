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
#include <File.h>
#include <Url.h>
#include <Codec.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <util.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

cAbstractMedia::cAbstractMedia(const cFile &File, const char *Mime, SupportedMediaType Type)
 : fd(-1)
 , mediaType(Type)
 , mimeType(Mime ? strdup(Mime) : NULL)
 , uri(NULL)
 , keyPath(File)
{
  char *tmp = keyPath.toURI();
  uri = cUrl::Decoder()->Decode(tmp);
  free(tmp);
}

cAbstractMedia::~cAbstractMedia()
{
  free(mimeType);
  free(uri);
}

const char *cAbstractMedia::Name(void) const
{
  return keyPath.Name();
}

void cAbstractMedia::Refresh(void)
{
}

size_t cAbstractMedia::ReadChunk(char* Buf, size_t bufSize)
{
  long rv = 0;
  const char *path = AbsolutePath();

  if (fd < 1) { // fd stays open between various calls
     fd = open(path, O_RDONLY | O_LARGEFILE);
     if (fd < 1) {
        esyslog("could not open requested path %s - Error #%d", path, errno);
        return 0;
        }
     }
  isyslog("have filehandle #%d (%s)", fd, path);
  if ((rv = read(fd, Buf, bufSize)) < 0)
     esyslog("ERROR: failed to read from file %s #%d", path, errno);
  else
     isyslog("read %u bytes from file %s", rv, path);
  if (rv < (long) bufSize) { // most probabely end of file
     close(fd);
     }
  return rv;
}

size_t cAbstractMedia::Size(void) const
{
  return keyPath.Size();
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

const char *cAbstractMedia::AbsolutePath(void) const
{
  return keyPath.AbsolutePath();
}

ulong cAbstractMedia::LastModified(void) const
{
  return keyPath.LastModified();
}

const char *cAbstractMedia::URI(void) const
{
  return uri;
}

void cAbstractMedia::SetMimeType(const char *MimeType)
{
  if (mimeType == MimeType) return;
  free(mimeType);
  mimeType = strdup(MimeType);
}

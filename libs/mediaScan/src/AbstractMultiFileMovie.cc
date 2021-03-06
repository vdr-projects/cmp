/**
 * ======================== legal notice ======================
 * 
 * File:      AbstractMultiFileMovie.cc
 * Created:   3. Juli 2012, 07
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
#include <AbstractMultiFileMovie.h>
#include <Logging.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

cAbstractMultiFileMovie::cAbstractMultiFileMovie(const cFile &File, const char *Mime, SupportedMediaType Type)
 : cMovie(File, Mime, Type)
 , movieFiles(0)
 , curFileNo(0)
 , buf(NULL)
 , bufSize(0)
 , name(NULL)
{
}

cAbstractMultiFileMovie::~cAbstractMultiFileMovie()
{
  free(name);
  free(buf);
}

bool cAbstractMultiFileMovie::checkBuffer(void) const
{
  if (!buf && bufSize) {
     buf = (char *) malloc(bufSize);
     }
  return buf != NULL;
}

const char *cAbstractMultiFileMovie::KeyFile(void) const
{
  return FirstFile();
}

size_t cAbstractMultiFileMovie::ReadChunk(char* Buf, size_t bufSize)
{
  long rv = 0;
  const char *path = NULL;

  if (fd < 1) {
     curFileNo = 1;
     path = FirstFile();
     fd = open(path, O_RDONLY | O_LARGEFILE);
     if (fd < 1) {
        esyslog("could not open requested path %s - Error #%d", path, errno);
        return 0;
        }
     }
  isyslog("have filehandle #%d (%s)", fd, path);
  rv = read(fd, Buf, bufSize);

  if (rv < (long) bufSize) {
     path = NextFile();

     if (path) {
        close(fd);
        fd = open(path, O_RDONLY | O_LARGEFILE);
        if (fd < 1) {
            esyslog("could not open requested path %s - Error #%d", path, errno);
            return 0;
            }
        isyslog("have filehandle #%d (%s)", fd, path);
        rv = read(fd, Buf, bufSize);
        }
     if (rv < (long) bufSize) {
        close(fd);
        fd = -1;
        }
     }
  return rv;
}

void cAbstractMultiFileMovie::Reset()
{
  cMovie::Reset();
  curFileNo = 0;
}

void cAbstractMultiFileMovie::SetName(char* Name)
///< Name must have already been allocated from heap!
{
  name = Name;
}

void cAbstractMultiFileMovie::SetSize(size_t Size)
{
  size = Size;
}
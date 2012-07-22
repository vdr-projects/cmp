/**
 * ======================== legal notice ======================
 * 
 * File:      AbstractMultiFileMovie.cc
 * Created:   3. Juli 2012, 07
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
#include <AbstractMultiFileMovie.h>
#include <Logging.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

cAbstractMultiFileMovie::cAbstractMultiFileMovie(const char *Name, const char *Logical, const char *Path, const char *Mime, SupportedMediaType Type)
 : cMovie(Name, Logical, Path, Mime, Type)
 , movieFiles(0)
 , curFileNo(0)
 , fileNameBuf(NULL)
 , bufSize(0)
{
}

cAbstractMultiFileMovie::~cAbstractMultiFileMovie()
{
  free(fileNameBuf);
}

size_t cAbstractMultiFileMovie::ReadChunk(char* Buf, size_t bufSize)
{
  long rv = 0;

  if (fd < 1) {
     fd = open(FirstFile(), O_RDONLY | O_LARGEFILE);
     if (fd < 1) {
        esyslog("could not open requested path %s - Error #%d", FirstFile(), errno);
        return 0;
        }
     }
  isyslog("have filehandle #%d (%s)", fd, FirstFile());
  rv = read(fd, Buf, bufSize);

  if (rv < (long) bufSize) {
     const char *nextFilename = NextFile();

     if (nextFilename) {
        close(fd);
        fd = open(nextFilename, O_RDONLY | O_LARGEFILE);
        if (fd < 1) {
            esyslog("could not open requested path %s - Error #%d", nextFilename, errno);
            return 0;
            }
        isyslog("have filehandle #%d (%s)", fd, nextFilename);
        rv = read(fd, Buf, bufSize);
        }
     if (rv < (long) bufSize) {
        close(fd);
        fd = -1;
        }
     }
  return rv;
}

//int cAbstractMultiFileMovie::ReadBlah(char* buf, size_t bufSize)
//{
//  size_t bytesRead = 0;
//
//  if (!fp) {
//     if (!(fp = f open(FirstFile(), "r"))) {
//        //TODO: add some verbose error message?
//        return 0;
//        }
//     }
//
//  bytesRead = f read(buf, sizeof(char), bufSize, fp);
//
//  if (bytesRead < bufSize) {
//     const char *nextFilename = NextFile();
//
//     if (nextFilename) {
//        f close(fp);
//        if (!(fp = f open(nextFilename, "r"))) {
//           //TODO: be verbose
//           return 0;
//           }
//        bytesRead += f read(buf + bytesRead, sizeof(char), bufSize - bytesRead, fp);
//        }
//     if (bytesRead < bufSize) {
//        f close(fp);
//        fp = NULL;
//        }
//     }
//  return bytesRead;
//}

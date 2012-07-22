/**
 * ======================== legal notice ======================
 * 
 * File:      DVDImage.cc
 * Created:   3. Juli 2012, 08
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
#include <DVDImage.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define FILE_MASK       "VIDEO_TS/VTS_%02d_%d.VOB"

cDVDImage::cDVDImage(const char *Name, const char *Logical, const char *Path)
 : cAbstractMultiFileMovie(Name, Logical, Path, "video/mpeg", DVDImage)
{
}

cDVDImage::~cDVDImage()
{
}

void cDVDImage::Refresh(void)
{
  struct stat stBuf;
  size_t maxSize = 0;
  size_t total = 0;
  time_t lastMod = 0;

  if (!fileNameBuf) {
     if (!(fileNameBuf = (char *)malloc(strlen(RealPath()) + 10))) {
        //TODO: some error message?
        return;
        }
     strcpy(fileNameBuf, RealPath());
     }
  movieFiles = 0;
  mainMovie = 0;

  for (int movie = 1; movie < 100; ++movie) {
      total = 0;
      for (int fileNo = 1;; ++fileNo) {
          sprintf(fileNameBuf + strlen(RealPath()), FILE_MASK, movie, fileNo);
          if (stat(fileNameBuf, &stBuf) < 0) {
            movieFiles = fileNo - 1;
            break;
            }
          total += stBuf.st_size;
          if (stBuf.st_mtime > lastMod) lastMod = stBuf.st_mtime;
          }
      if (total > maxSize) {
         maxSize = total;
         mainMovie = movie;
         }
      }
  SetSize(total);
  SetLastModified(lastMod);
}

const char *cDVDImage::FirstFile(void)
{
  if (!fileNameBuf) {
     if (!(fileNameBuf = (char *)malloc(strlen(RealPath()) + 10))) {
        //TODO: some error message?
        return NULL;
        }
     strcpy(fileNameBuf, RealPath());
     }
  curFileNo = 1;
  sprintf(fileNameBuf + strlen(RealPath()), FILE_MASK, mainMovie, curFileNo);

  return fileNameBuf;
}

const char *cDVDImage::NextFile(void)
{
  if (++curFileNo < movieFiles) {
     sprintf(fileNameBuf + strlen(RealPath()), FILE_MASK, mainMovie, curFileNo);

     return fileNameBuf;
     }
  return NULL;
}

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

#include "File.h"
#define FILE_MASK       "VIDEO_TS/VTS_%02d_%d.VOB"

cDVDImage::cDVDImage(const cFile &File)
 : cAbstractMultiFileMovie(File, "video/mpeg", DVDImage)
{
  bufSize = 32;
}

cDVDImage::~cDVDImage()
{
}

const char *cDVDImage::Name(void) const
{
  return cAbstractMedia::Name();
}

size_t cDVDImage::Size(void) const
{
  return cAbstractMedia::Size();
}

void cDVDImage::Refresh(void)
{
  size_t maxSize = 0;
  size_t total = 0;
  int numOfMovieFiles = 0;
  cFile *tmp;

  movieFiles = 0;
  mainMovie = 0;
  if (!checkBuffer()) return;
  for (int movie = 1; movie < 100; ++movie) {
      total = 0;
      for (int fileNo = 1;; ++fileNo) {
          sprintf(buf, FILE_MASK, movie, fileNo);
          tmp = new cFile(KeyPath(), buf);

          if (!tmp || !tmp->Exists()) {
            numOfMovieFiles = fileNo - 1;
            break;
            }
          total += tmp->Size();
          delete tmp;
          }
      if (total > maxSize) {
         maxSize = total;
         mainMovie = movie;
         movieFiles = numOfMovieFiles;
         }
      }
  SetSize(total);
}

const char *cDVDImage::FirstFile(void)
{
  if (!checkBuffer()) return NULL;

  curFileNo = 1;
  sprintf(buf, FILE_MASK, mainMovie, curFileNo);
  cFile *tmp = new cFile(KeyPath(), buf);
  const char *rv = NULL;

  if (tmp) {
     rv = tmp->AbsolutePath();
     delete tmp;
     }
  return rv;
}

const char *cDVDImage::NextFile(void)
{
  if (++curFileNo < movieFiles) {
     if (!checkBuffer()) return NULL;
     sprintf(buf, FILE_MASK, mainMovie, curFileNo);
     cFile *tmp = new cFile(KeyPath(), buf);
     const char *rv = NULL;

     if (tmp) {
        tmp->AbsolutePath();
        delete tmp;

        return rv;
        }
     }
  return NULL;
}

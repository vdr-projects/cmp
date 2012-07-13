/**
 * ======================== legal notice ======================
 * 
 * File:      VdrRecording.cc
 * Created:   3. Juli 2012, 08:30
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
#include <VdrRecording.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define FILE_MASK       "/%05d.ts"

cVdrRecording::cVdrRecording(const char *Name, const char *Logical, const char *Path)
 : cAbstractMultiFileMovie(Name, Logical, Path, "video/mpeg", VdrRecording)
{
}

cVdrRecording::~cVdrRecording()
{
}

void cVdrRecording::Refresh(void)
{
  struct stat stBuf;
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

  for (int fileNo = 1;; ++fileNo) {
      sprintf(fileNameBuf + strlen(RealPath()), FILE_MASK, fileNo);
      if (stat(fileNameBuf, &stBuf) < 0) {
         movieFiles = fileNo - 1;
         break;
         }
      total += stBuf.st_size;
      if (stBuf.st_mtime > lastMod) lastMod = stBuf.st_mtime;
      }
  SetSize(total);
  SetLastModified(lastMod);
}

const char *cVdrRecording::FirstFile(void)
{
  if (!fileNameBuf) {
     if (!(fileNameBuf = (char *)malloc(strlen(RealPath()) + 16))) {
        //TODO: some error message?
        return NULL;
        }
     strcpy(fileNameBuf, RealPath());
     }
  curFileNo = 1;
  sprintf(fileNameBuf + strlen(RealPath()), FILE_MASK, curFileNo);

  return fileNameBuf;
}

const char *cVdrRecording::NextFile(void)
{
  if (++curFileNo < movieFiles) {
     sprintf(fileNameBuf + strlen(RealPath()), FILE_MASK, curFileNo);

     return fileNameBuf;
     }
  return NULL;
}

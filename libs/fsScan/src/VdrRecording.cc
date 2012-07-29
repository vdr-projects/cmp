/**
 * ======================== legal notice ======================
 * 
 * File:      VdrRecording.cc
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
#include <VdrRecording.h>
#include <StringBuilder.h>
#include <File.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define FILE_MASK       "/%05d.ts"

cVdrRecording::cVdrRecording(const cFile &File)
 : cAbstractMultiFileMovie(File, "video/mpeg", VdrRecording)
{
  cStringBuilder sb;
  cFile *parent = File.Parent();

  sb.Append(parent->Name());
  sb.Append(" (").Append(File.Name()).Append(")");
  delete parent;
  SetName(sb.toString());
  bufSize = 10;
}

cVdrRecording::~cVdrRecording()
{
}

void cVdrRecording::Refresh(void)
{
  size_t total = 0;
  cFile *tmp;

  if (!checkBuffer()) return;
  movieFiles = 0;
  for (int fileNo = 1;; ++fileNo) {
      sprintf(buf, FILE_MASK, fileNo);
      tmp = new cFile(KeyPath(), buf);

      if (!tmp || !tmp->Exists()) {
         movieFiles = fileNo - 1;
         delete tmp;
         break;
         }
      total += tmp->Size();
      delete tmp;
      }
  SetSize(total);
}

const char *cVdrRecording::FirstFile(void)
{
  if (!checkBuffer()) return NULL;
  curFileNo = 1;
  sprintf(buf, FILE_MASK, curFileNo);
  cFile *tmp = new cFile(KeyPath(), buf);
  const char *rv = NULL;

  if (tmp) {
     rv = tmp->AbsolutePath();
     delete tmp;
     }
  return rv;
}

const char *cVdrRecording::NextFile(void)
{
  if (++curFileNo < movieFiles) {
     if (!checkBuffer()) return NULL;
     sprintf(buf, FILE_MASK, curFileNo);
     cFile *tmp = new cFile(KeyPath(), buf);
     const char *rv = NULL;

     if (tmp) {
        rv = tmp->AbsolutePath();
        delete tmp;

        return rv;
        }
     }
  return NULL;
}

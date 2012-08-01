/**
 * ======================== legal notice ======================
 * 
 * File:      LegacyVdrRecording.cc
 * Created:   3. Juli 2012, 08
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
#include <LegacyVdrRecording.h>
#include <StringBuilder.h>
#include <File.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define FILE_MASK       "%03d.vdr"

static bool deepScanEnabled = true;

cLegacyVdrRecording::cLegacyVdrRecording(const cFile &File)
 : cAbstractMultiFileMovie(File, "video/mpeg", LegacyVdrRecording)
{
  cStringBuilder sb;
  cFile *parent = File.Parent();

  sb.Append(parent->Name());
  sb.Append(" (").Append(File.Name()).Append(")");
  delete parent;
  SetName(sb.toString());
  bufSize = 8;
}

cLegacyVdrRecording::~cLegacyVdrRecording()
{
}

void cLegacyVdrRecording::EnableDeepScan(bool DoScan)
{
  deepScanEnabled = DoScan;
}

bool cLegacyVdrRecording::NeedsFurtherScan(void) const
{
  return deepScanEnabled;
}

void cLegacyVdrRecording::Refresh(void)
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

const char *cLegacyVdrRecording::FirstFile(void) const
{
  if (!checkBuffer()) return NULL;
  sprintf(buf, FILE_MASK, 1);
  cFile *tmp = new cFile(KeyPath(), buf);
  const char *rv = NULL;

  if (tmp) {
     rv = tmp->AbsolutePath();
     delete tmp;
     }
  return rv;
}

const char *cLegacyVdrRecording::NextFile(void)
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

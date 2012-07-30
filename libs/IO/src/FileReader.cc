/**
 * ======================== legal notice ======================
 * 
 * File:      FileReader.cc
 * Created:   28. Juli 2012, 15:00
 * Author:    <a href="mailto:geronimo013@gmx.de">Geronimo</a>
 * Project:   libIO: classes for files, filesystem and input/output
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
#include <FileReader.h>
#include <File.h>
#include <Logging.h>
#include <fcntl.h>
#include <unistd.h>

cFileReader::cFileReader(cFile *Input)
 : file(Input)
{
  Open();
}

bool cFileReader::Open()
{
  if (file && file->Exists() && file->CanRead()) {
     fd = open(file->AbsolutePath(), O_RDONLY);
     if (fd < 0) esyslog("ERROR: could not open %s", file->AbsolutePath());
     }
  return fd > 0;
}

cFileReader::~cFileReader()
{
  Close();
}

void cFileReader::Close()
{
  if (fd > 0) {
     close(fd);
     fd = -1;
     }
  if (file) {
     delete file;
     file = NULL;
     }
}

/**
 * ======================== legal notice ======================
 * 
 * File:      Reader.cc
 * Created:   30. Juli 2012, 08:11
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
#include <Reader.h>
#include <Logging.h>
#include <unistd.h>

cReader::cReader()
 : fd(-1)
{
}

cReader::~cReader()
{
}

int cReader::Read(char* buf, int bufSize)
{
  if (fd < 0) Open();
  if (fd > 0) return read(fd, buf, bufSize);
  esyslog("ERROR: no valid filehandle to read from!");
  return 0;
}

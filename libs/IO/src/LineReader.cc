/**
 * ======================== legal notice ======================
 * 
 * File:      LineReader.cc
 * Created:   28. Juli 2012, 06
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
#include <LineReader.h>
#include <Reader.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

cLineReader::cLineReader(cReader *FileReader)
 : reader(FileReader)
 , bytesRead(0)
 , off(0)
 , bufSize(1024)
 , buf(NULL)
 , lastLine(NULL)
{
  buf = (char *) malloc(bufSize + 1);
  if (buf) {
     buf[bufSize] = 0;
     *buf = 0;
     }
}

cLineReader::~cLineReader()
{
  Close();
}

void cLineReader::Close()
{
  if (reader) {
     delete reader;
     reader = NULL;
     }
  free(buf);
  buf = NULL;
  off = NULL;
}

const char *cLineReader::ReadLine(void)
{
  const char *rv = NULL;
  char *p;

  if (lastLine) lastLine += strlen(lastLine) + 1;
  else lastLine = buf;
  if (bytesRead && lastLine - buf >= bytesRead) return NULL;
  p = strchr(lastLine, '\n');

  if (!p && strlen(lastLine)) {
     memmove(buf, lastLine, strlen(lastLine));
     buf[strlen(lastLine)] = 0;
     lastLine = buf;
     }

  if (!p && (!bytesRead || bytesRead == bufSize)) {
     bytesRead = strlen(buf);
     int br = reader->Read(buf + bytesRead, bufSize - bytesRead);

     if (br > 0) bytesRead += br;
     if (bytesRead < bufSize) memset(buf + bytesRead, 0, bufSize - bytesRead);
     }

  if (!p) p = strchr(lastLine, '\n');

  if (p) {
     if (p - buf <= bytesRead) {
        *p = 0;
        rv = lastLine;
        }
     }
  else {
     if (strlen(lastLine)) rv = lastLine;
     }
  return rv;
}

/**
 * ======================== legal notice ======================
 * 
 * File:      util.cc
 * Created:   4. Juli 2012, 05
 * Author:    <a href="mailto:geronimo013@gmx.de">Geronimo</a>
 * Project:   libutil - base classes used by other libraries
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
#include <util.h>
#include <string.h>
#include <ctype.h>

const char * skipWhitespace(const char *Buffer)
{
  while (*Buffer && isspace(*Buffer)) ++Buffer;

  return Buffer;
}

const char *getWord(char *buf, int bufSize, const char *src)
{
  const char *s = src;
  char *d = buf;

  if (!strncmp(src, "\n\n", 2) || !strncmp(src, "\r\n\r\n", 4))
     return src;

  while (*s && isspace(*s)) ++s;
  while (*s && ((d - buf) < bufSize) && !isspace(*s)) *d++ = *s++;
  *d = 0;

  return *s ? s : NULL;
}

const char *restOfLine(char *buf, int bufSize, const char *src)
{
  const char *s = src;
  char *d = buf;

  while (*s && isspace(*s)) ++s;
  while (*s && ((d - buf) < bufSize) && *s != '\n' && *s != '\r') *d++ = *s++;
  *d = 0;

  return *s ? s : NULL;
}

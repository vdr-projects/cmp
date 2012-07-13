/**
 * ======================== legal notice ======================
 * 
 * File:      MD5Calculator.cc
 * Created:   3. Juli 2012, 13:15
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
#include <MD5Calculator.h>
#include <Codec.h>
#include <string.h>

cMD5Calculator::cMD5Calculator()
{
  MD5_Init(&context);
}

cMD5Calculator::~cMD5Calculator()
{
}

void cMD5Calculator::AddContent(const char* Buf, size_t bufSize)
{
  if (!bufSize) bufSize = strlen(Buf);
  MD5_Update(&context, Buf, bufSize);
}

char * cMD5Calculator::Hash(void)
{
  unsigned char md[20];

  MD5_Final(md, &context);

  return getHexEncoder()->Encode(md, 16);
}

void cMD5Calculator::Reset()
{
  memset(&context, 0, sizeof(context));
  MD5_Init(&context);
}
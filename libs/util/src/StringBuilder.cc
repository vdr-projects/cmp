/**
 * ======================== legal notice ======================
 * 
 * File:      StringBuilder.cc
 * Created:   6. Juli 2012, 10
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
#include <StringBuilder.h>
#include <Logging.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static void freeStringCallback(void *elem)
{
  free(elem);
}

cStringBuilder::cStringBuilder(const char *First)
 : chunkSize(127)
 , readOffset(0)
 , writeOffset(0)
 , firstChunk(NULL)
 , pool(freeStringCallback)
{
  init();
  if (First) Append(First);
}

cStringBuilder::cStringBuilder(int ChunkSize)
 : chunkSize(ChunkSize)
 , readOffset(0)
 , writeOffset(0)
 , firstChunk(NULL)
 , pool(freeStringCallback)
{
  init();
}

cStringBuilder::~cStringBuilder()
{
}

void cStringBuilder::init(void)
{
  char *first = (char *) malloc(chunkSize);

  pool.push_back(first);
  firstChunk = first;
}

void cStringBuilder::Write(const char *Text)
{
  if (!Text) {
     esyslog("ERROR: text to add is a NULL-pointer!");
     return;
     }
  uint chunkFree = chunkSize - writeOffset;
  char *curChunk = (char *) pool[pool.size() - 1];
  const char *p = Text;

  while (strlen(p) >= chunkFree) {
        strncpy(curChunk + writeOffset, p, chunkFree);
        p += chunkFree;

        curChunk = (char *) malloc(chunkSize);
        pool.push_back(curChunk);
        writeOffset = 0;
        chunkFree = chunkSize;
        }
  if (strlen(p)) {
     strcpy(curChunk + writeOffset, p);
     writeOffset += strlen(p);
     }
}

size_t cStringBuilder::Size()
{
  return (pool.size() - 1) * chunkSize + writeOffset;
}

size_t cStringBuilder::Size() const
{
  return (pool.size() - 1) * chunkSize + writeOffset;
}

size_t cStringBuilder::Copy(char* Buf, size_t BufSize)
{
  uint chunkNo = readOffset / chunkSize;
  uint chunkOff = readOffset % chunkSize;
  uint bytes2Write = chunkSize;
  char *curChunk = (char *) pool[chunkNo];
  size_t bytesWritten = 0;

  if (chunkNo == (pool.size() - 1)) bytes2Write = writeOffset;
  while ((BufSize - bytesWritten) > (bytes2Write - chunkOff)) {
        strncpy(Buf + bytesWritten, curChunk + chunkOff, bytes2Write - chunkOff);
        bytesWritten += bytes2Write - chunkOff;

        chunkOff = 0;
        if (++chunkNo < (pool.size() - 1)) bytes2Write = chunkSize;
        else bytes2Write = writeOffset;
        if (chunkNo == pool.size()) break;
        curChunk = (char *) pool[chunkNo];
        }
  readOffset += bytesWritten;

  return bytesWritten;
}

cStringBuilder &cStringBuilder::Append(const char* Text)
{
  if (!Text) Write("(null)");
  Write(Text);

  return *this;
}

cStringBuilder &cStringBuilder::Append(char c)
{
  char buf[2];

  *buf = c;
  buf[1] = 0;

  Write(buf);

  return *this;
}

cStringBuilder &cStringBuilder::Append(bool v, const char *TrueValue, const char *FalseValue)
{
  if (v) Write(TrueValue);
  else Write(FalseValue);

  return *this;
}

cStringBuilder &cStringBuilder::Append(double v)
{
  char *elem = NULL;

  asprintf(&elem, "%lg", v);
  if (elem) {
     Write(elem);
     free(elem);
     }
  return *this;
}

cStringBuilder &cStringBuilder::Append(int v)
{
  char buf[12];

  if (snprintf(buf, sizeof(buf), "%d", v)) Write(buf);

  return *this;
}

cStringBuilder &cStringBuilder::Append(long v)
{
  char buf[24];

  if (snprintf(buf, sizeof(buf), "%ld", v)) Write(buf);

  return *this;
}

cStringBuilder &cStringBuilder::Append(size_t v)
{
  char buf[24];

  if (snprintf(buf, sizeof(buf), "%lu", v)) Write(buf);

  return *this;
}

char *cStringBuilder::toString(void)
{
  char *rv = (char *) malloc(Size() + 1);

  if (rv) {
     readOffset = 0;
     Copy(rv, Size() + 1);
     *(rv + Size()) = 0;
     }
  return rv;
}

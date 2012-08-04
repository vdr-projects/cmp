/**
 * ======================== legal notice ======================
 * 
 * File:      StringBuilder.h
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
#ifndef STRINGBUILDER_H
#define	STRINGBUILDER_H

#include <ManagedVector.h>
#include <time.h>

class cStringBuilder {
public:
  cStringBuilder(const char *First);
  cStringBuilder(int chunkSize = 127);
  virtual ~cStringBuilder();

  cStringBuilder &Append(const char *Text, const char char2Replace[] = NULL, const char *replacements[] = NULL);
  cStringBuilder &Append(char c);
  cStringBuilder &Append(bool v, const char *TrueValue = "X", const char *FalseValue="-");
  cStringBuilder &Append(double v);
  cStringBuilder &Append(int v);
  cStringBuilder &Append(long v);
  cStringBuilder &Append(size_t s);
  void Clear(void);
  size_t Size(void);
  size_t Size(void) const;
  void Rewind(void) { readOffset = 0; }
  size_t Copy(char *Buf, size_t BufSize);
  char *toString(void);

protected:
  void Write(const char *Text);
  void WriteAndReplace(const char *Text, const char char2Replace[], const char *replacements[]);

private:
  void init(void);
  int chunkSize;
  size_t readOffset; ///< read offest is the offset over all chunks (thus goes from 0 to size)
                     ///< Copy can be called subsequently, if Buf is smaller than StringBuilders size
  int writeOffset;   ///< write offset is the offset inside the last chunk (thus goes from 0 to chunkSize)
  char *firstChunk;  ///< for debugging purpose only
  cManagedVector pool;
  };

#endif	/* STRINGBUILDER_H */


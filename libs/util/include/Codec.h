/**
 * ======================== legal notice ======================
 * 
 * File:      Codec.h
 * Created:   21. Mai 2012, 14:00
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
#ifndef CODEC_H
#define	CODEC_H

#include <stddef.h>

class cCodec {
///< base class for simple (character based) encoding/decoding
public:
  cCodec(const char *Table, char KeyChar = '#');
  virtual ~cCodec();
  char KeyChar() const { return keyChar; }
  const char *TranslateTable() const { return translateTable; }
  virtual size_t DecodeSequence(unsigned char *d, unsigned char *s);

protected:
  char *translateTable;
  char keyChar;
  };

class cEncoder : public cCodec {
public:
  cEncoder(char SpecialChar = '#', const char *TrTable = "0123456789ABCDEF");
  virtual ~cEncoder();
  char *Encode(const char *Source, size_t SourceLength = 0); ///< encode Source,
  ///< optionally limited by SourceLength (default is to encode a 0-terminated cstring)
  };

class cURLEncoder : public cEncoder {
public:
  cURLEncoder();
  virtual ~cURLEncoder();
  };

class cDecoder : public cCodec {
public:
  cDecoder(char KeyChar = '#', const char *TrTable = "0123456789ABCDEF");
  virtual ~cDecoder();
  char *Decode(const char *Source, size_t SourceLength = 0); ///< decode Source,
  ///< optionally limited by SourceLength (default is to decode a 0-terminated cstring)
  virtual size_t DecodeSequence(unsigned char *d, unsigned char *s);
  };

class cURLDecoder : public cDecoder {
public:
  cURLDecoder();
  virtual ~cURLDecoder();
  };

class cHexEncoder : public cEncoder {
public:
  cHexEncoder();
  virtual ~cHexEncoder();
  char *Encode(const unsigned char* Source, size_t SourceLength = 0);
  };

class cHexDecoder : public cDecoder {
public:
  cHexDecoder();
  virtual ~cHexDecoder();
  char *Decode(const char *Source, size_t SourceLength = 0);
  };

extern cHexEncoder * getHexEncoder(void);
extern cHexDecoder * getHexDecoder(void);
extern void codecCleanUp(void);

#endif	/* CODEC_H */


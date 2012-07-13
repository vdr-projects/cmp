/**
 * ======================== legal notice ======================
 * 
 * File:      Codec.cc
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
#include "Codec.h"
#include "util.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <openssl/md5.h>

// --- Codec ------------------------------------------------------------------
static cHexEncoder * hexEncoder = NULL;
static cHexDecoder * hexDecoder = NULL;

cCodec::cCodec(const char *Table, char SpecialChar)
 : translateTable(strdup(Table))
 , keyChar(SpecialChar)
{
}

cCodec::~cCodec()
{
  FREE(translateTable);
}

size_t cCodec::DecodeSequence(unsigned char *d, unsigned char *s)
{
  *d = *s;

  return 1;
}

// --- Encoder ----------------------------------------------------------------

cEncoder::cEncoder(char SpecialChar, const char *TrTable)
 : cCodec(TrTable, SpecialChar)
{
}

cEncoder::~cEncoder()
{
}

char *cEncoder::Encode(const char *Source, size_t SourceLength)
{
  if (!Source) return NULL;
  if (!SourceLength) SourceLength = strlen(Source);

  const unsigned char *s = (const unsigned char *)Source;
  const unsigned char *last = (const unsigned char *)(Source + SourceLength);
  char *rv = (char *)malloc(SourceLength * 3 + 1);
  char *d = rv;
  unsigned char c;

  for (; s < last; ++s) {
      c = *s;
      if (c < 0x80 && (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~'))
         *d++ = c;
      else if (c == ' ')
         *d++ = '+';
      else {
         *d++ = KeyChar();
         *d++ = TranslateTable()[c >> 4];
         *d++ = TranslateTable()[c & 0x0F];
         }
      }
  *d = 0;

  return rv;
}

// --- URLEncoder -------------------------------------------------------------

cURLEncoder::cURLEncoder()
 : cEncoder('%')
{
}

cURLEncoder::~cURLEncoder()
{
}

// --- Decoder ----------------------------------------------------------------

cDecoder::cDecoder(char SpecialChar, const char *TrTable)
 : cCodec(TrTable, SpecialChar)
{
}

cDecoder::~cDecoder()
{
}

char *cDecoder::Decode(const char *Source, size_t SourceLength)
{
  if (!Source) return NULL;
  if (!SourceLength) SourceLength = strlen(Source);

  const unsigned char *s = (const unsigned char *)Source;
  const unsigned char *last = (const unsigned char *)(Source + SourceLength);
  char *rv = (char *)malloc(SourceLength + 1);
  unsigned char *d = (unsigned char *) rv;
  size_t seqLen;

  for (; s < last; ++s) {
      if (*s == KeyChar()) {
         seqLen = DecodeSequence(d++, (unsigned char *) ++s);
         s += seqLen;
         }
      else if (*s == '+') {
         *d++ = ' ';
         }
      else {
         *d++ = *s;
         }
      }
  *d = 0;

  return rv;
}

size_t cDecoder::DecodeSequence(unsigned char *d, unsigned char *s)
{
  // just transform hex sequence back to character
  unsigned char c = s[0] >= 'A' ? ((s[0] & 0xDF) - 'A') + 10 : (s[0] - '0');

  c *= 16;
  c += s[1] >= 'A' ? ((s[1] & 0xDF) - 'A') + 10 : (s[1] - '0');
  *d = c;

  return 1;
}

// --- URLDecoder -------------------------------------------------------------

cURLDecoder::cURLDecoder()
 : cDecoder('%')
{
}

cURLDecoder::~cURLDecoder()
{
}

// --- HexEncoder -------------------------------------------------------------

cHexEncoder::cHexEncoder()
 : cEncoder('#', "0123456789abcdef")
{
}

cHexEncoder::~cHexEncoder()
{
}

char* cHexEncoder::Encode(const unsigned char* Source, size_t SourceLength)
{
  if (!SourceLength) SourceLength = strlen((const char *)Source);
  const unsigned char *s = (const unsigned char *)Source;
  char *rv = (char *)malloc(SourceLength * 3 + 1);
  char *d = rv;
  unsigned char c;

  for (int i=0; i < 16; ++i, ++s) {
      c = *s;
      *d++ = TranslateTable()[c >> 4];
      *d++ = TranslateTable()[c & 0x0F];
      }
  *d = 0;

  return rv;
}

cHexEncoder * getHexEncoder(void) {
  if (!hexEncoder) hexEncoder = new cHexEncoder();
  return hexEncoder;
}

// --- HexDecoder -------------------------------------------------------------

cHexDecoder::cHexDecoder()
{
}

cHexDecoder::~cHexDecoder()
{
}

char* cHexDecoder::Decode(const char* Source, size_t SourceLength)
{
  if (!Source) return NULL;
  if (!SourceLength) SourceLength = strlen(Source);

  const unsigned char *s = (const unsigned char *)Source;
  const unsigned char *last = (const unsigned char *)(Source + SourceLength);
  char *rv = (char *)malloc(SourceLength + 1);
  unsigned char *d = (unsigned char *) rv;
  unsigned char c0, c1;

  for (; s < last; s += 2) {
      c0 = toupper(s[0]);
      c1 = c0 >= 'A' ? ((c0 & 0xDF) - 'A') + 10 : (c0 - '0');
      c1 *= 16;
      c0 = toupper(s[1]);
      c1 = c0 >= 'A' ? ((c0 & 0xDF) - 'A') + 10 : (c0 - '0');
      *d++ = c1;
      }
  *d = 0;

  return rv;
}

cHexDecoder * getHexDecoder(void) {
  if (!hexDecoder) hexDecoder = new cHexDecoder();
  return hexDecoder;
}

void codecCleanUp(void) {
  if (hexEncoder) {
     delete hexEncoder;
     hexEncoder = NULL;
     }
  if (hexDecoder) {
     delete hexDecoder;
     hexDecoder = NULL;
     }
}

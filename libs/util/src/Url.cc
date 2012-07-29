/**
 * ======================== legal notice ======================
 * 
 * File:      Url.cc
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
#include <Url.h>
#include <Codec.h>
#include <util.h>
#ifdef DEBUG
#include <iostream>
#endif
#include <stdio.h>
#include <string.h>
#include <vector>

static cURLEncoder * encoder = NULL;
static cURLDecoder * decoder = NULL;

cUrl::cUrl(const char* RawURL)
 : path(NULL)
{
  ParseURL(RawURL);
}

cUrl::~cUrl()
{
  FREE(path);
}

cURLDecoder* cUrl::Decoder(void)
{
  if (!decoder) decoder = new cURLDecoder();
  return decoder;
}

cURLEncoder* cUrl::Encoder(void)
{
  if (!encoder) encoder = new cURLEncoder();
  return encoder;
}

const char *cUrl::Parameter(const char* Name)
{
  std::tr1::unordered_map<std::string, std::string>::iterator found = parameters.find(Name);
  if (found != parameters.end()) return found->second.c_str();
  return NULL;
}

void cUrl::SetParameter(const char* Name, const char* Value)
{
  std::string name = Name;
  std::string value = Value ? Value : " ";
  parameters[name] = value;
}

size_t cUrl::EstimatedSize(void ) const
{
  size_t rv = parameters.size() * 3;

  if (path) rv += strlen(path) + 4;
  ParameterMap::const_iterator pm = parameters.begin();

  while (pm != parameters.end()) {
        rv += pm->first.length() * 3;
        rv += pm->second.length() * 3;
        ++pm;
        }
  return rv;
}

void cUrl::ParseURL(const char *URL)
{
  FREE(path);
  parameters.clear();
  if (!URL) return;
  const char *q = strchr(URL, '?'); // divider between url and querystring
//  char *realURL;
//  size_t l;

  if (!q) q = URL + strlen(URL);
//  l = q - URL;
//  realURL = (char *)malloc(l + 2);
//  if (!realURL) return;
//  strncpy(realURL, URL, l);
//  realURL[l] = 0;
  path = Decoder()->Decode(URL, q - URL);
  if (*q) ParseQueryString(++q);
}

void cUrl::ParseQueryString(const char* QueryString)
{
  if (!(QueryString && *QueryString)) return;
  const char *start, *last;
  char *scratch = strdup(QueryString);
  char *p, *end;
  size_t srcLen = strlen(QueryString);

  for (start = (const char *)scratch, end = (char *) start, last = scratch + srcLen; end && start < last; start = (const char *)++end) {
      end = (char *) strchr(start, '&');
      if (!end) end = (char *)start + strlen(start);
      *end = 0;
      p = (char *) strchr(start, '=');
      if (p) {
         *p++ = 0;
         char *pn = p ? Decoder()->Decode(start) : NULL;
         char *pv = p ? Decoder()->Decode(p) : NULL;

         std::string name = pn;
         std::string value = pv ? pv : " ";

         parameters[name] = value;

         free(pn);
         free(pv);
         }
      else {
         char *pn = Decoder()->Decode(start);

         std::string name = pn;
         parameters[name] = " ";
         free(pn);
         }
      }
  free(scratch);
}

char* cUrl::ToString(void) const
///< returns the address of the newly allocated buffer
{
  size_t bufSize = EstimatedSize();
  char *rv = (char *)malloc(bufSize);

  if (!rv) return NULL;
  int n = WriteBuf(rv, bufSize);

  if (n < 0) {
     bufSize += 128;
     rv = (char *) realloc(rv, bufSize);
     WriteBuf(rv, bufSize);
     }
  return rv;
}

int cUrl::WriteBuf(char* buf, size_t bufSize) const
///< returns the characters written. -1 as return value indicates a buffer overrun.
{
  char *p, *tmp;
  bool first = true;
  int n = 0;

  if (path) n += snprintf(buf + n, bufSize - n, "%s", path);
  p = buf + n;
  ParameterMap::const_iterator pm = parameters.begin();

  while (pm != parameters.end()) {
        tmp = Encoder()->Encode(pm->first.c_str());
        if (p - buf + strlen(tmp) + 2 > bufSize)
           return -1;
        if (first) {
           first = false;
           *p++ = '?';
           }
        else *p++ = '&';
        strcpy(p, tmp);
        p += strlen(p);
        FREE(tmp);

        if (strcmp(pm->second.c_str(), " ")) {
           tmp = Encoder()->Encode(pm->second.c_str());
           if (p - buf + strlen(tmp) + 2 > bufSize)
              return -1;
           *p++ = '=';
           strcpy(p, tmp);
           p += strlen(p);
           FREE(tmp);
           }
        ++pm;
        }
  p += strlen(p);

  return p - buf;
}

#ifdef DEBUG
void cUrl::Dump(void )
{
  ParameterMap::const_iterator pm = parameters.begin();

  while (pm != parameters.end()) {
        std::cout << "parameter [" << pm->first << "]";
        if (strcmp(pm->second.c_str(), " "))
          std::cout << " has value <|" << pm->second << "|>" << std::endl;
        else
          std::cout << " has NO value!" << std::endl;
        ++pm;
        }
}
#endif

void cUrl::Cleanup(void )
{
  if (encoder) {
     delete encoder;
     encoder = NULL;
     }
  if (decoder) {
     delete decoder;
     decoder = NULL;
     }
}
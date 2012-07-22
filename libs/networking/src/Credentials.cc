/**
 * ======================== legal notice ======================
 * 
 * File:      Credentials.cc
 * Created:   3. Juli 2012, 14
 * Author:    <a href="mailto:geronimo013@gmx.de">Geronimo</a>
 * Project:   libnetworking: classes for tcp/ip sockets and http-protocol handling
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
#include <Credentials.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

cCredentials Credentials;
static const char *appRealm = NULL;

cCredentials::cCredentials()
{
}

cCredentials::~cCredentials()
{
  Clear();
}

void cCredentials::Clear()
{
  iterator it = internalMap.begin();

  while (it != internalMap.end()) {
        delete it->second;
        ++it;
        }
}

const char *cCredentials::ApplicationRealm() const
{
  return appRealm;
}

const cPrincipal *cCredentials::FindPrincipal(const char* Name, const char* Realm)
{
  std::string tmp = Name;
  cPrincipal *rv = internalMap[tmp];

  if (!strcmp(rv->Name(), Name) && !strcmp(rv->Realm(), Realm)) return rv;
  return NULL;
}

void cCredentials::SetApplicationRealm(const char* ApplicationRealm)
{
  appRealm = ApplicationRealm;
}

void cCredentials::Put(const char* Key, cPrincipal* p)
{
  internalMap[Key] = p;
}

cPrincipal *cCredentials::Get(const char* Key)
{
  iterator it = internalMap.find(Key);

  if (it != internalMap.end()) return it->second;
  return NULL;
}

int cCredentials::Load(const char *FileName)
{
  char buf[256];
  FILE *fp = fopen(FileName, "r");
  cPrincipal *principal = NULL;
  char *chunk = buf;
  int principalsProcessed = 0;
  int bytesRead = 0;

  if (!fp) {
     //TODO: verbose message?
     return 0;
     }
  while ((bytesRead = fread(chunk, sizeof(char), sizeof(buf) - (chunk - buf), fp)) > 0) {
        char *endOfLine = index(buf, '\n');

        while (chunk && endOfLine) {
              principal = parsePrincipal(chunk, endOfLine - chunk);
              if (!principal) break;
              std::string userid = principal->Name();

              internalMap[userid] = principal;
              ++principalsProcessed;
              chunk = endOfLine < (buf + sizeof(buf)) ? endOfLine + 1 : NULL;
              endOfLine = index(chunk, '\n');
              }
        // shift rest of buffer down and read a smaller chunk
        if (chunk && !endOfLine) {
           int rest = sizeof(buf) - (chunk - buf);

           memmove(buf, chunk, rest);
           chunk = buf + rest;
           }
        }
  fclose(fp);

  return principalsProcessed;
}

cPrincipal *cCredentials::parsePrincipal(char* buf, size_t bufSize)
///< format is:         name:hash:age:extendedInfo
{
  if (!buf || !*buf || bufSize < 30) return NULL;
  cPrincipal *rv = NULL;
  char *hash = index(buf, ':') + 1;
  char *age = index(hash, ':') + 1;
  char *xi = index(age, ':') + 1;

  if (hash == (char *)1 || !*hash) return NULL;
  if (age == (char *)1 || !*age) return NULL;
  if (xi == (char *)1 || !*xi) return NULL;

  *(hash - 1) = 0;
  *(age - 1) = 0;
  *(xi - 1) = 0;
  *(buf + bufSize - 1) = 0;

  rv = new cPrincipal(buf, ApplicationRealm());
  if (rv) {
     rv->SetHash(hash);
     rv->SetAge(atoi(age));
     rv->SetExtendedInfo(xi);
     }
  return rv;
}

int cCredentials::Store(const char* FileName)
{
  FILE *fp = fopen(FileName, "w");
  cPrincipal *p;
  int principalsProcessed = 0;

  if (!fp) {
     //TODO: verbose message?
     return 0;
     }
  cCredentials::const_iterator principals = begin();

  while (principals != end()) {
        p = principals->second;
        fprintf(fp, "%s:%s:%d:%s\n", p->Name(), p->Hash(), p->Age(), p->ExtendedInfo() ? p->ExtendedInfo() : " ");
        ++principalsProcessed;
        ++principals;
        }
  fclose(fp);

  return principalsProcessed;
}
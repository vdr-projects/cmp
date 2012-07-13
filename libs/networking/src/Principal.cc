/**
 * ======================== legal notice ======================
 * 
 * File:      Principal.cc
 * Created:   3. Juli 2012, 12:50
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
#include <Principal.h>
#include <MD5Calculator.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <util.h>

cPrincipal::cPrincipal(const char *Name, const char *Realm)
 : name(strdup(Name))
 , realm(strdup(Realm))
 , hash(NULL)
 , xinfo(NULL)
 , age(0)
{
}

cPrincipal::cPrincipal(const cPrincipal& other)
 : name(other.name ? strdup(other.name) : NULL)
 , realm(other.realm ? strdup(other.realm) : NULL)
 , hash(other.hash ? strdup(other.hash) : NULL)
 , xinfo(other.xinfo ? strdup(other.xinfo) : NULL)
 , age(other.age)
{
}

cPrincipal::~cPrincipal()
{
  FREE(name);
  FREE(realm);
  FREE(hash);
  FREE(xinfo);
}

void cPrincipal::CreateHash(const char* Password)
{
  cMD5Calculator hc;

  FREE(hash);
  hc.AddContent(name, strlen(name));
  hc.AddContent(":", 1);
  hc.AddContent(realm, strlen(realm));
  hc.AddContent(":", 1);
  hc.AddContent(Password, strlen(Password));

  hash = hc.Hash();
}

void cPrincipal::SetName(const char* Name)
{
  FREE(name);
  name = Name ? strdup(Name) : NULL;
}

void cPrincipal::SetRealm(const char* Realm)
{
  FREE(realm);
  realm = Realm ? strdup(Realm) : NULL;
}

void cPrincipal::SetHash(const char* Hash)
{
  FREE(hash);
  hash = Hash ? strdup(Hash) : NULL;
}

void cPrincipal::SetExtendedInfo(const char* Info)
{
  FREE(xinfo);
  xinfo = Info ? strdup(Info) : NULL;
}

void cPrincipal::Dump(void) const
{
  printf(">>> ========= Principal ======================\n");
  printf("name ....: >%s<\n", name);
  printf("realm ...: >%s<\n", realm);
  printf("hash ....: >%s<\n", hash);
  printf("age .....: >%d<\n", age);
  printf("ext. info: >%s<\n", xinfo);
  printf("------------- Principal ------------------ <<<\n");
}

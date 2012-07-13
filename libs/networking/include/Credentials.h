/**
 * ======================== legal notice ======================
 * 
 * File:      Credentials.h
 * Created:   3. Juli 2012, 14:37
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
#ifndef CREDENTIALS_H
#define	CREDENTIALS_H

#include <Principal.h>
#include <string>
#include <tr1/unordered_map>

class cCredentials {
public:
  typedef std::tr1::unordered_map<std::string, cPrincipal *>::const_iterator const_iterator;
  cCredentials();
  virtual ~cCredentials();

  const cPrincipal *FindPrincipal(const char *Name, const char *Realm);
  const char *ApplicationRealm(void) const;
  void SetApplicationRealm(const char *ApplicationRealm = "knownUser@myApp");

  int Load(const char *FileName);
  int Store(const char *FileName);

  void Put(const char *Key, cPrincipal *p);
  cPrincipal *Get(const char *Key);
  void Clear(void);

  const_iterator begin() { return internalMap.begin(); }
  const_iterator end() { return internalMap.end(); }

private:
  cPrincipal *parsePrincipal(char *buf, size_t bufSize);
  std::tr1::unordered_map<std::string, cPrincipal *> internalMap;
  typedef std::tr1::unordered_map<std::string, cPrincipal *>::iterator iterator;
  };

extern cCredentials Credentials;

#endif	/* CREDENTIALS_H */


/**
 * ======================== legal notice ======================
 * 
 * File:      Principal.h
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
#ifndef PRINCIPAL_H
#define	PRINCIPAL_H

class cPrincipal {
public:
  cPrincipal(const char *Name, const char *Realm);
  cPrincipal(const cPrincipal &other);
  virtual ~cPrincipal();
  cPrincipal &operator =(const cPrincipal &other);
  const char *operator *(void) { return name; }

  void CreateHash(const char *Password);

  const char *Name(void) const { return name; }
  const char *Realm(void) const { return realm; }
  const char *ExtendedInfo(void) const { return xinfo; }
  int Age(void) const { return age; }
  void SetAge(int Age) { age = Age; }
  const char *Hash(void) const { return hash; }

  void Dump(void) const;

protected:
  void SetName(const char *Name);
  void SetRealm(const char *Realm);
  void SetExtendedInfo(const char *Info);
  void SetHash(const char *Hash);

private:
  char *name;
  char *realm;
  char *hash;
  char *xinfo;
  int age;
  friend class cAuthorization;
  friend class cCredentials;
  };

#endif	/* PRINCIPAL_H */


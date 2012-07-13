/**
 * ======================== legal notice ======================
 * 
 * File:      ManagedMap.h
 * Created:   7. Juli 2012, 08:28
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
#ifndef MANAGEDMAP_H
#define	MANAGEDMAP_H

#include <string>
#include <tr1/unordered_map>

class cManagedMap {
public:
  typedef std::tr1::unordered_map<std::string, void *>::const_iterator const_iterator;

  cManagedMap(void (*cbFreeElem)(void *));
  virtual ~cManagedMap();

  void clear(void);
  void put(const char *key, void *value);
  void *get(const char *key);
  const void *get(const char *key) const;
  size_t size(void) { return internalMap.size(); }

  const_iterator begin() const { return internalMap.begin(); }
  const_iterator end() const { return internalMap.end(); }

private:
  std::tr1::unordered_map<std::string, void *> internalMap;
  void (*freeCallback)(void *);
  typedef std::tr1::unordered_map<std::string, void *>::iterator iterator;
};


#endif	/* MANAGEDMAP_H */


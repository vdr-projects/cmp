/**
 * ======================== legal notice ======================
 * 
 * File:      ManagedMap.cc
 * Created:   7. Juli 2012, 08
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
#include <ManagedMap.h>
#include <Logging.h>
#include <stdlib.h>

cManagedMap::cManagedMap(void (*cbFreeElem)(void *))
 : freeCallback(cbFreeElem)
{
}

cManagedMap::~cManagedMap()
{
  clear();
}

void cManagedMap::clear()
{
  iterator it = internalMap.begin();

  while (it != internalMap.end()) {
        if (freeCallback) {
           isyslog("gonna free %s", it->first.c_str());
           freeCallback(it->second);
           }
        ++it;
        }
  internalMap.clear();
}

void *cManagedMap::get(const char* key)
{
  const_iterator it = internalMap.find(key);

  if (it == internalMap.end()) return NULL;
  return it->second;
}

const void *cManagedMap::get(const char* key) const
{
  const_iterator it = internalMap.find(key);

  if (it == internalMap.end()) return NULL;
  return it->second;
}

void cManagedMap::put(const char* key, void* value)
{
  isyslog("cManagedMap::put[%s] => 0x%0X", key, value);
  internalMap[key] = value;
}
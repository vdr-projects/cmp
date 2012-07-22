/**
 * ======================== legal notice ======================
 * 
 * File:      ManagedVector.cc
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
#include <ManagedVector.h>
#include <vector>
#include <algorithm>

cManagedVector::cManagedVector(void (*cbFreeElem)(void *))
 : freeCallback(cbFreeElem)
{
}

cManagedVector::~cManagedVector()
{
  clear();
}

void cManagedVector::clear()
{
  for (size_t i=0; i < internalVector.size(); ++i) {
      freeCallback(internalVector[i]);
      }
  internalVector.clear();
}

void cManagedVector::sort(bool (*fnSort)(void *a, void *b))
{
  if (fnSort) std::sort(internalVector.begin(), internalVector.end(), fnSort);
  else std::sort(internalVector.begin(), internalVector.end());
}
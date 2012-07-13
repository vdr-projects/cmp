/**
 * ======================== legal notice ======================
 * 
 * File:      ManagedVector.h
 * Created:   6. Juli 2012, 19:07
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
#ifndef MANAGEDVECTOR_H
#define	MANAGEDVECTOR_H

#include <vector>
#include <stdlib.h>

class cManagedVector {
public:
  cManagedVector(void (*cbFreeElem)(void *));
  virtual ~cManagedVector();

  void clear(void);
  void push_back(void *p) { internalVector.push_back(p); }
  void *operator[](size_t n) { return internalVector[n]; }
  const void *operator[](size_t n) const { return internalVector[n]; }
  size_t size(void) const { return internalVector.size(); }
  void sort(bool (*fnSort)(void *a, void *b));

private:
  std::vector<void *> internalVector;
  void (*freeCallback)(void *);
  };

#endif	/* MANAGEDVECTOR_H */


/**
 * ======================== legal notice ======================
 * 
 * File:      AbstractListAssembler.cc
 * Created:   6. Juli 2012, 09
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
#include <AbstractListAssembler.h>
#include <ManagedVector.h>
#include <StringBuilder.h>
#include <Logging.h>

cAbstractListAssembler::cAbstractListAssembler()
{
}

cAbstractListAssembler::~cAbstractListAssembler()
{
}

bool cAbstractListAssembler::AssembleList(cStringBuilder& sb, cManagedVector &ElemVector, std::map<int, size_t> &Categories, size_t start, uint delta)
{
  isyslog("::AssembleList() with start=%lu, delta=%i", start, delta);
  int n = 0;
  size_t end = start + delta;

  if (end >= ElemVector.size()) {
     end = ElemVector.size();
     if (delta >= ElemVector.size()) start = 0;
     else start = ElemVector.size() - delta;
     }
  OpenList(sb, Categories, ElemVector.size(), start, delta);
  isyslog("now really assemble list with start=%lu, delta=%i", start, delta);
  for (size_t i=start; i < end; ++i) {
      AddElement(sb, ElemVector[i], ++n % 2);
      }
  CloseList(sb, ElemVector.size(), start, delta);

  return true;
}
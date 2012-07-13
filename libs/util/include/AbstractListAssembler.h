/**
 * ======================== legal notice ======================
 * 
 * File:      AbstractListAssembler.h
 * Created:   6. Juli 2012, 09:38
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
#ifndef ABSTRACTLISTASSEMBLER_H
#define	ABSTRACTLISTASSEMBLER_H

#include <sys/types.h>
#include <map>

class cStringBuilder;
class cManagedVector;
class cAbstractListAssembler {
public:
  cAbstractListAssembler();
  virtual ~cAbstractListAssembler();

  bool AssembleList(cStringBuilder &sb, cManagedVector &ElemVector, std::map<int, size_t> &Categories, size_t start = 0, uint delta = 40);

  virtual const char *MediaType(void) const = 0;

protected:
  virtual bool OpenList(cStringBuilder &sb, std::map<int, size_t> &Categories, size_t total, size_t start = 0, uint delta = 40) = 0;
  virtual bool AddElement(cStringBuilder &sb, void *, bool odd) = 0;
  virtual bool CloseList(cStringBuilder &sb, size_t total, size_t start = 0, uint delta = 40) = 0;
};

#endif	/* ABSTRACTLISTASSEMBLER_H */


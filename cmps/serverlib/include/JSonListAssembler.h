/**
 * ======================== legal notice ======================
 * 
 * File:      JSonListAssembler.h
 * Created:   6. Juli 2012, 09:53
 * Author:    <a href="mailto:geronimo013@gmx.de">Geronimo</a>
 * Project:   cmps - the backend (server) part of compound media player
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
#ifndef JSONLISTASSEMBLER_H
#define	JSONLISTASSEMBLER_H

#include <AbstractListAssembler.h>
#include <map>

class cStringBuilder;
class cJSonListAssembler : public cAbstractListAssembler {
public:
  cJSonListAssembler();
  virtual ~cJSonListAssembler();

  virtual const char *MediaType(void) const;

protected:
  virtual bool OpenList(cStringBuilder &sb, std::map<int, size_t> &Categories, size_t total, size_t start = 0, uint delta = 40);
  virtual bool AddElement(cStringBuilder &sb, void *ListElement, bool odd);
  virtual bool CloseList(cStringBuilder &sb, size_t total, size_t start = 0, uint delta = 40);
};

#endif	/* JSONLISTASSEMBLER_H */


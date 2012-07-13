/**
 * ======================== legal notice ======================
 * 
 * File:      HTMLListAssembler.h
 * Created:   6. Juli 2012, 09:55
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
#ifndef HTMLLISTASSEMBLER_H
#define	HTMLLISTASSEMBLER_H

#include <AbstractListAssembler.h>
#include <map>

class cStringBuilder;
class cHTMLListAssembler : public cAbstractListAssembler {
public:
  cHTMLListAssembler();
  virtual ~cHTMLListAssembler();

  virtual const char *MediaType(void) const;

protected:
  bool OpenList(cStringBuilder &sb, std::map<int, size_t> &Categories, size_t total, size_t start = 0, uint delta = 40);
  bool AddElement(cStringBuilder &sb, void *ListElement, bool odd);
  bool CloseList(cStringBuilder &sb, size_t total, size_t start = 0, uint delta = 40);

private:
  cStringBuilder &genHTMLPrefix(cStringBuilder &sb, const char *Title);
  cStringBuilder &genDelim(cStringBuilder &sb);
  cStringBuilder &genMediaLink(cStringBuilder &sb, void *ListElement, bool odd);
  cStringBuilder &genNextLink(cStringBuilder &sb, int n);
  cStringBuilder &genPreviousLink(cStringBuilder &sb, int n);
  cStringBuilder &genTypeMenu(cStringBuilder &sb, std::map<int, size_t> &Categories);
};

#endif	/* HTMLLISTASSEMBLER_H */


/**
 * ======================== legal notice ======================
 * 
 * File:      Persistable.h
 * Created:   29. Juli 2012, 13:08
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
#ifndef PERSISTABLE_H
#define	PERSISTABLE_H

class cPersistable {
public:
  virtual int Store(const char *FileName) = 0;
  virtual int Load(const char *FileName) = 0;
  };

#endif	/* PERSISTABLE_H */


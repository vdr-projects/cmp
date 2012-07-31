/**
 * ======================== legal notice ======================
 * 
 * File:      Picture.h
 * Created:   2. Juli 2012, 15
 * Author:    <a href="mailto:geronimo013@gmx.de">Geronimo</a>
 * Project:   libMediaScan: mediatypes and media scanning
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
#ifndef PICTURE_H
#define	PICTURE_H

#include <AbstractMedia.h>

class cPicture : public cAbstractMedia {
public:
  cPicture(const cFile &File, const char *Mime);
  virtual ~cPicture();

private:
  static const char *ContentType(const char *Extension);
  static SupportedExtension knownExtensions[];
  friend class cMediaFactory;
  friend class FScanTest;
  friend int check4Media(void *, cFile *, const char *);
  };

#endif	/* PICTURE_H */


/**
 * ======================== legal notice ======================
 * 
 * File:      DVDImage.h
 * Created:   3. Juli 2012, 08
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
#ifndef DVDIMAGE_H
#define	DVDIMAGE_H

#include <AbstractMultiFileMovie.h>

class cDVDImage : public cAbstractMultiFileMovie {
public:
  cDVDImage(const cFile &File);
  virtual ~cDVDImage();

  virtual const char *Name(void) const;
  virtual const char *FirstFile(void) const;
  virtual const char *NextFile(void);
  virtual void Refresh(void);
  virtual size_t Size(void) const;
  virtual bool NeedsFurtherScan(void) const;
  static void EnableDeepScan(bool DoScan);

private:
  int mainMovie;
  };

#endif	/* DVDIMAGE_H */


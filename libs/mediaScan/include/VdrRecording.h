/**
 * ======================== legal notice ======================
 * 
 * File:      VdrRecording.h
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
#ifndef VDRRECORDING_H
#define	VDRRECORDING_H

#include <AbstractMultiFileMovie.h>

class cVdrRecording : public cAbstractMultiFileMovie {
public:
  cVdrRecording(const cFile &File);
  virtual ~cVdrRecording();

  virtual const char *FirstFile(void) const;
  virtual const char *NextFile(void);
  virtual void Refresh(void);
  virtual bool NeedsFurtherScan(void) const;
  static void EnableDeepScan(bool DoScan);
  };

#endif	/* VDRRECORDING_H */


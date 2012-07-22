/**
 * ======================== legal notice ======================
 * 
 * File:      LegacyVdrRecording.h
 * Created:   3. Juli 2012, 08
 * Author:    <a href="mailto:geronimo013@gmx.de">Geronimo</a>
 * Project:   libfsScan: mediatypes and filesystem scanning
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
#ifndef LEGACYVDRRECORDING_H
#define	LEGACYVDRRECORDING_H

#include <AbstractMultiFileMovie.h>

class cLegacyVdrRecording : public cAbstractMultiFileMovie {
public:
  cLegacyVdrRecording(const char *Name, const char *Logical, const char *Path);
  virtual ~cLegacyVdrRecording();

  virtual void Refresh(void);

  virtual const char *FirstFile(void);
  virtual const char *NextFile(void);
  };

#endif	/* LEGACYVDRRECORDING_H */


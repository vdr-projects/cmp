/**
 * ======================== legal notice ======================
 * 
 * File:      MediaFactory.h
 * Created:   2. Juli 2012, 15
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
#ifndef MEDIAFACTORY_H
#define	MEDIAFACTORY_H

#include <sys/stat.h>
#include <sys/types.h>

class cAbstractMedia;
class cMediaFactory {
public:
  cMediaFactory(const char *BaseDirectory);
  virtual ~cMediaFactory();

  cAbstractMedia *CreateMedia(const char *FileOrDirname, struct stat *st);

  const char *BaseDirectory(void) const { return baseDirectory; }
  void SetBaseDirectory(const char *dir);

private:
  char *baseDirectory;
  char *scratch;
  size_t scratchSize;
  };

#endif	/* MEDIAFACTORY_H */


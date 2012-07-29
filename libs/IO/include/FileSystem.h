/**
 * ======================== legal notice ======================
 * 
 * File:      FileSystem.h
 * Created:   21. Juli 2012, 12
 * Author:    <a href="mailto:geronimo013@gmx.de">Geronimo</a>
 * Project:   libIO: classes for files, filesystem and input/output
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
#ifndef FILESYSTEM_H
#define	FILESYSTEM_H

#include <tr1/unordered_map>
#include <string>

class cFile;
class cFileRepresentation;
class cFileSystem {
public:
  cFileSystem();
  virtual ~cFileSystem();

  cFileRepresentation *representationOfFile(const char *Path);
  cFileRepresentation *representationOfFile(const cFile &Parent, const char *Path);

private:
  cFileRepresentation *cacheEntry(const char *Path);
  cFileRepresentation *representationOfFile(const cFileRepresentation *parentRep, const char* Path);
  std::tr1::unordered_map<std::string, cFileRepresentation *> fileCache;
  static char PathSeparator;
  static char RootPath[4];
  friend class cFileRepresentation;
  friend class cFile;
  };

#endif	/* FILESYSTEM_H */


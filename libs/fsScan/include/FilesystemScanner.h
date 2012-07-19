/**
 * ======================== legal notice ======================
 * 
 * File:      FilesystemScanner.h
 * Created:   2. Juli 2012, 13:58
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
#ifndef FILESYSTEMSCANNER_H
#define	FILESYSTEMSCANNER_H

#include <ManagedVector.h>
#include <MediaFactory.h>
#include <map>

class cAbstractMedia;
class cFilesystemScanner {
public:
  cFilesystemScanner();
  virtual ~cFilesystemScanner();

  cManagedVector &MediaPool(void) { return pool; }
  std::map<int, size_t> &Categories(void) { return categories; }
  cAbstractMedia *FindMedia(const char *LogicalPath);
  void Refresh(void);

  void SetBaseDirectory(const char *dir);
  void SetMediaFactory(cMediaFactory *factory);

protected:
  void parseDir(const char *dir, cManagedVector &result);

private:
  char *baseDirectory;
  size_t fileBufSize;
  struct dirent *dirEntryBuf;
  cManagedVector pool;
  std::map<int, size_t> categories;
  cMediaFactory *mediaFactory;
  };

#endif	/* FILESYSTEMSCANNER_H */

/**
 * ======================== legal notice ======================
 * 
 * File:      FileRepresentation.h
 * Created:   21. Juli 2012, 12:41
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
#ifndef FILEREPRESENTATION_H
#define FILEREPRESENTATION_H

#include <sys/types.h>

class cStringBuilder;
class cFileRepresentation
{
public:
  virtual ~cFileRepresentation();

  cStringBuilder *internalPath(void) const;
  const cFileRepresentation *getParent(void) const { return parent; };

private:
  cFileRepresentation(const char *Path);
  cFileRepresentation(const cFileRepresentation *Parent, const char *Path);
  bool exists;
  bool isRoot;
  mode_t mode;
  off64_t size;
  ulong lastModified;
  char *name;
  const cFileRepresentation *parent;
  friend class cFileSystem;
  friend class cFile;
};

#endif // FILEREPRESENTATION_H

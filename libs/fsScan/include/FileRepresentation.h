/**
 * ======================== legal notice ======================
 *
 * File:      FileRepresentation.h
 * Created:   21. Juli 2012, 12
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
class cFileRepresentation {
public:
  virtual ~cFileRepresentation();

  const char *Path(void) const;
  const cFileRepresentation *getParent(void) const { return parent; };
  void SetVirtualRoot(bool isRoot);

private:
  cFileRepresentation(const char *Name);
  cFileRepresentation(const cFileRepresentation *Parent, const char *Name);
  char *toURI(void) const;
  bool exists;
  bool isRoot;
  bool isVirtualRoot;
  mode_t mode;
  off64_t size;
  ulong lastModified;
  char *name;
  mutable char *path;
  const cFileRepresentation *parent;
  friend class cFileSystem;
  friend class cFile;
  };

#endif // FILEREPRESENTATION_H

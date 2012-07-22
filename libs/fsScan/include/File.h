/**
 * ======================== legal notice ======================
 * 
 * File:      File.h
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
#ifndef FILE_H
#define	FILE_H

#include <sys/types.h>

class cFileSystem;
class cFileRepresentation;
class cStringBuilder;
class cFile
{
public:
  cFile(const char *Path);
  cFile(const cFile &Parent, const char *RelativePath);
  virtual ~cFile();

  bool CanRead(void) const;
  bool CanWrite(void) const;
  bool CanExecute(void) const;
  bool Exists(void) const;
  bool IsDirectory(void) const;
  bool IsFile(void) const;
  bool IsSymbolic(void) const;
  off64_t Size(void) const;
  ulong LastModified(void) const;
  const char *Name(void) const;

  char *AbsolutePath(void) const;
  cFile *Parent(void) const;
  void VisitFiles(int (*cb)(cFile *, const char *));

  static void Cleanup(void);

private:
  cFile(const cFileRepresentation *);
  const cFileRepresentation *rep;
  static cFileSystem *fs;
  friend class cFileSystem;
};

#endif	/* FILE_H */


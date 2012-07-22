/**
 * ======================== legal notice ======================
 * 
 * File:      FileRepresentation.cc
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
#include <FileRepresentation.h>
#include <FileSystem.h>
#include <StringBuilder.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <stack>

cFileRepresentation::cFileRepresentation(const char *Path)
 : exists(false)
 , isRoot(true)
 , mode(0)
 , size(0)
 , lastModified(0)
 , name(NULL)
 , parent(NULL)
{
  struct stat st;

  if (!stat(Path, &st)) {
     name = strdup(Path);
     exists = true;
     mode = st.st_mode;
     size = st.st_size;
     lastModified = st.st_mtime;
     }
}

cFileRepresentation::cFileRepresentation(const cFileRepresentation *Parent, const char *Path)
 : exists(false)
 , isRoot(false)
 , mode(0)
 , size(0)
 , lastModified(0)
 , name(NULL)
 , parent(Parent)
{
  name = strdup(Path);
  cStringBuilder *sb = internalPath();
  char *tmp = sb->toString();
  struct stat st;

  std::cout << "real path is: " << tmp << std::endl;
  if (!stat(tmp, &st)) {
     exists = true;
     mode = st.st_mode;
     size = st.st_size;
     lastModified = st.st_mtime;
     }
  free(tmp);
  delete sb;
  std::cout << "should create file representation for " << Path << std::endl;
}

cFileRepresentation::~cFileRepresentation()
{
  free(name);
}

cStringBuilder *cFileRepresentation::internalPath(void) const
{
  cStringBuilder *sb = new cStringBuilder();
  const cFileRepresentation *f = this;
  std::stack<const cFileRepresentation *> rev;
  char *chk;

  while (!f->isRoot) {
        rev.push(f);
        f = f->parent;
        }

  for (;;) {
      sb->Append(f->name);
      if (rev.empty()) break;
      chk = f->name + strlen(f->name) - 1;
      if (*chk != cFileSystem::PathSeparator) sb->Append(cFileSystem::PathSeparator);
      f = rev.top();
      rev.pop();
      }

  return sb;
}


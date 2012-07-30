/**
 * ======================== legal notice ======================
 * 
 * File:      FileRepresentation.cc
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
#include <FileRepresentation.h>
#include <FileSystem.h>
#include <StringBuilder.h>
#include <Url.h>
#include <Codec.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <stack>

cFileRepresentation::cFileRepresentation(const char *Name)
 : exists(false)
 , isRoot(true)
 , isVirtualRoot(true)
 , mode(0)
 , size(0)
 , lastModified(0)
 , name(NULL)
 , path(NULL)
 , parent(NULL)
{
  struct stat st;

  if (!stat(Name, &st)) {
     name = strdup(Name);
     exists = true;
     mode = st.st_mode;
     size = st.st_size;
     lastModified = st.st_mtime;
     }
}

cFileRepresentation::cFileRepresentation(const cFileRepresentation *Parent, const char *Name)
 : exists(false)
 , isRoot(false)
 , isVirtualRoot(false)
 , mode(0)
 , size(0)
 , lastModified(0)
 , name(strdup(Name))
 , path(NULL)
 , parent(Parent)
{
  struct stat st;

  if (!stat(Path(), &st)) {
     exists = true;
     mode = st.st_mode;
     size = st.st_size;
     lastModified = st.st_mtime;
     }
}

cFileRepresentation::~cFileRepresentation()
{
  free(name);
  free(path);
}

const char *cFileRepresentation::Path() const
{
  if (!path) {
     cStringBuilder sb;

     if (parent) sb.Append(parent->Path());
     if (strcmp(cFileSystem::RootPath, name)) sb.Append(cFileSystem::PathSeparator).Append(name);
     path = sb.toString();
     }
  return path;
}

void cFileRepresentation::SetVirtualRoot(bool isRoot)
{
  isVirtualRoot = isRoot;
}

char *cFileRepresentation::toURI() const
{
  cStringBuilder *sb = new cStringBuilder();
  const cFileRepresentation *f = this;
  std::stack<const cFileRepresentation *> rev;
  cURLEncoder *enc = cUrl::Encoder();
  char *tmp, *chk, *rv;
  size_t stackSize;

  while (!f->isVirtualRoot) {
        rev.push(f);
        stackSize = rev.size();
        f = f->parent;
        }

  for (;;) {
      f = rev.top();
      rev.pop();
      chk = f->name + strlen(f->name) - 1;
      if (*chk != cFileSystem::PathSeparator) sb->Append(cFileSystem::PathSeparator);
      tmp = enc->Encode(f->name);
      sb->Append(tmp);
      free(tmp);
      if (rev.empty()) break;
      }
  rv = sb->toString();
  delete sb;

  return rv;
}

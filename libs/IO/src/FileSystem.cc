/**
 * ======================== legal notice ======================
 * 
 * File:      FileSystem.cc
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
#include <FileSystem.h>
#include <FileRepresentation.h>
#include <File.h>
#include <StringBuilder.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

char cFileSystem::PathSeparator = '/';
char cFileSystem::RootPath[4] = { PathSeparator, 0, 0, 0 };

cFileSystem::cFileSystem()
{
}

cFileSystem::~cFileSystem()
{
  std::tr1::unordered_map<std::string, cFileRepresentation *>::iterator it = fileCache.begin();

  while (it != fileCache.end()) {
        if (it->second) delete it->second;
        ++it;
        }
}

cFileRepresentation *cFileSystem::cacheEntry(const char* Path)
{
  if (fileCache.empty()) return NULL;
  std::tr1::unordered_map<std::string, cFileRepresentation *>::iterator it = fileCache.find(Path);

  if (it != fileCache.end()) return it->second;
  return NULL;
}

cFileRepresentation *cFileSystem::representationOfFile(const cFile &Parent, const char* Path)
{
  cFileRepresentation *parentRep = (cFileRepresentation *) Parent.rep;

  return representationOfFile(parentRep, Path);
}

cFileRepresentation *cFileSystem::representationOfFile(const cFileRepresentation *parentRep, const char* Path)
{
  cFileRepresentation *tmp = NULL;
  cStringBuilder *sb = new cStringBuilder(parentRep->Path());
  char *scratch = strdup(Path);
  char *last = scratch + strlen(Path);
  char *start = *scratch == PathSeparator ? scratch + 1 : scratch;
  char *end = strchr(scratch, PathSeparator);
  char *path;

  while (start < last) {
        end = strchr(start, PathSeparator);
        if (!end) end = start + strlen(start);
        *end = 0;
        sb->Append(PathSeparator).Append(start);
        path = sb->toString();
        tmp = cacheEntry(path);
        if (!tmp) {
           tmp = new cFileRepresentation(parentRep, start);
           fileCache[path] = tmp;
           }
        parentRep = tmp;
        free(path);
        start = end + 1;
        }
  free(scratch);
  delete sb;

  if (tmp) return tmp;
  return NULL;
}

cFileRepresentation *cFileSystem::representationOfFile(const char* Path)
{
  cFileRepresentation *rv = cacheEntry(Path);

  if (!rv) {
     cFileRepresentation *tmp = NULL;
     char *scratch = strdup(Path);
     char *p, *last = scratch + strlen(Path);

     for (p = strrchr(scratch, PathSeparator); !rv && p && p < last; p = strrchr(scratch, PathSeparator)) {
         if (p > scratch) *p = 0;
         else {
            *p = 0;
            if (!(rv = cacheEntry(RootPath))) {
               tmp = new cFileRepresentation(RootPath);
               fileCache[RootPath] = tmp;
               break;
               }
            }
         if ((tmp = cacheEntry(scratch))) break;
         }
     if (rv && strcmp(rv->Path(), Path)) {
        tmp = rv;
        rv = NULL;
        }
     if (tmp) {
        cFileRepresentation *parent = tmp;
        size_t poolSize = fileCache.size();
        const char *last = scratch + strlen(Path);

        for (p = scratch + strlen(scratch) + 1; p < last; p += strlen(p) + 1) {
            if (!*(p - 1)) *(p - 1) = PathSeparator;
            tmp = new cFileRepresentation(parent, p);
            fileCache[scratch] = tmp;
            poolSize = fileCache.size();
            parent = tmp;
            }
        rv = parent;
        }
     free(scratch);
     }
  return rv;
}


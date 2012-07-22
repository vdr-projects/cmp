/**
 * ======================== legal notice ======================
 * 
 * File:      FilesystemScanner.cc
 * Created:   2. Juli 2012, 13
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
#include <FilesystemScanner.h>
#include <AbstractMedia.h>
#include <Logging.h>
#include <stddef.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <util.h>

void freeMediaCallback(void *elem)
{
  delete (cAbstractMedia *)elem;
}

cFilesystemScanner::cFilesystemScanner()
 : baseDirectory(NULL)
 , fileBufSize(512)
 , dirEntryBuf(NULL)
 , pool(freeMediaCallback)
 , mediaFactory(NULL)
{
}

cFilesystemScanner::~cFilesystemScanner()
{
  FREE(dirEntryBuf);
  FREE(baseDirectory);
  pool.clear();
  if (mediaFactory) delete mediaFactory;
}

void cFilesystemScanner::SetBaseDirectory(const char* dir)
{
  FREE(baseDirectory);
  baseDirectory = strdup(dir);
  if (mediaFactory) mediaFactory->SetBaseDirectory(dir);
}

void cFilesystemScanner::SetMediaFactory(cMediaFactory* factory)
{
  if ((mediaFactory = factory)) {
     FREE(baseDirectory);
     baseDirectory = strdup(mediaFactory->BaseDirectory());
     }
}

// return true if a should be ordered before b
bool defaultMediaSortOrder(void *a, void *b)
{
  if (a == b) return false;
  if (!a) return false;
  if (!b) return true;
  cAbstractMedia *m0 = (cAbstractMedia *)a;
  cAbstractMedia *m1 = (cAbstractMedia *)b;
  bool rv = false;

  if (m0->MediaType() == m1->MediaType())
     rv = strcasecmp(m0->Name(), m1->Name()) < 0;
  else
     rv = (m0->MediaType() - m1->MediaType()) < 0;

  return rv;
}

void cFilesystemScanner::Refresh()
{
  if (!mediaFactory) return;
  pool.clear();
  categories.clear();
  dirEntryBuf = (struct dirent *)malloc(sizeof(struct dirent));
  if (!dirEntryBuf) {
     esyslog("ERROR: out of memory!");
     return;
     }
  parseDir(baseDirectory, pool);
  FREE(dirEntryBuf);
  cAbstractMedia::SupportedMediaType ot = cAbstractMedia::Invalid;
  cAbstractMedia *m;

  pool.sort(defaultMediaSortOrder);
  for (size_t i=0; i < pool.size(); ++i) {
      m = (cAbstractMedia *) pool[i];
      if (m->MediaType() != ot) {
         ot = m->MediaType();
         categories[ot] = i;
         }
      }
}

void cFilesystemScanner::parseDir(const char* dirName, cManagedVector &result)
{
  if (!mediaFactory) return;
  DIR *dir = opendir(dirName);
  cAbstractMedia *media;
  char *pathBuf = (char *)malloc(fileBufSize);
  struct dirent *dirEntry;
  struct stat statBuf;

  if (!dir) return;
  if (!pathBuf) {
     closedir(dir);
     return;
     }
  if (fileBufSize < strlen(dirName) + 128) {
     fileBufSize += 256;
     pathBuf = (char *)realloc(pathBuf, fileBufSize);
     }
  while (!readdir_r(dir, dirEntryBuf, &dirEntry) && dirEntry) {
        if (*dirEntry->d_name == '.') continue; // don't bother with hidden stuff
        strcpy(pathBuf, dirName);
        strcat(pathBuf, "/");
        strcat(pathBuf, dirEntry->d_name);
        if (stat(pathBuf, &statBuf) < 0) return;
        if ((media = mediaFactory->CreateMedia(pathBuf, &statBuf))) {
           result.push_back(media);
           isyslog("found media %s - %s", media->MimeType(), media->LogicalPath());
           continue;
           }
        if ((statBuf.st_mode & S_IFMT) == S_IFDIR) parseDir(pathBuf, result);
        }
  closedir(dir);
  FREE(pathBuf);
}

cAbstractMedia *cFilesystemScanner::FindMedia(const char* LogicalPath)
{
  cAbstractMedia *rv = NULL, *tmp;

  for (size_t i=0; i < pool.size(); ++i) {
      tmp = (cAbstractMedia *) pool[i];
      if (!strcmp(tmp->LogicalPath(), LogicalPath)) {
         rv = tmp;
         break;
         }
      }
  return rv;
}
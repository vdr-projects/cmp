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
 : fileBufSize(512)
 , pool(freeMediaCallback)
 , mediaFactory(NULL)
{
}

cFilesystemScanner::~cFilesystemScanner()
{
  pool.clear();
  if (mediaFactory) delete mediaFactory;
}

void cFilesystemScanner::SetMediaFactory(cMediaFactory* factory)
{
  mediaFactory = factory;
}

// return true if "a" should be ordered before "b"
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

  mediaFactory->Scan4Media(pool);
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

cAbstractMedia *cFilesystemScanner::FindMedia(const char* URI)
{
  cAbstractMedia *rv = NULL, *tmp;

  for (size_t i=0; i < pool.size(); ++i) {
      tmp = (cAbstractMedia *) pool[i];
      if (!strcmp(tmp->URI(), URI)) {
         rv = tmp;
         break;
         }
      }
  return rv;
}

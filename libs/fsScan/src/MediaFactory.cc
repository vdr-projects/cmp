/**
 * ======================== legal notice ======================
 * 
 * File:      MediaFactory.cc
 * Created:   2. Juli 2012, 15
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
#include <MediaFactory.h>
#include <Audio.h>
#include <Movie.h>
#include <Picture.h>
#include <LegacyVdrRecording.h>
#include <VdrRecording.h>
#include <DVDImage.h>
#include <ServerConfig.h>
#include <StringBuilder.h>
#include <Logging.h>
#include <File.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

cMediaFactory::cMediaFactory(const cServerConfig &sc)
 : config(sc)
 , baseDirectory(sc.DocumentRoot())
 , scratch(NULL)
 , scratchSize(1024)
{
  scratch = (char *)malloc(scratchSize);
}

cMediaFactory::~cMediaFactory()
{
  free(scratch);
}

void cMediaFactory::SetBaseDirectory(const cFile &dir)
{
  if (!dir.IsDirectory()) {
     esyslog("ERROR: attempt to set base directory to a file (%s)", dir.Name());
     return;
     }
  baseDirectory = dir;
}

int cMediaFactory::createMedia(void *opaque, cFile *Parent, const char *Name)
{
  if (!opaque) return -1;
  cMediaFactory *mf = (cMediaFactory *) opaque;

  return mf->CreateMedia(Parent, Name);
}

int cMediaFactory::CreateMedia(const cFile *Parent, const char *Name)
{
//  cManagedVector *pool = (cManagedVector *) opaque;
  cFile *curFile = new cFile(*Parent, Name);
  const char *mimeType = NULL;
  cAbstractMedia *rv = NULL;

  if (!curFile) {
     esyslog("ERROR: out of memory!");
     return -1;
     }
  if (!curFile->Exists()) {
     delete curFile;
     return -1;
     }
  if (curFile->IsDirectory()) {
     static const char *keyFiles[] = { "001.vdr", "00001.ts", "VIDEO_TS/VIDEO_TS.IFO", NULL };
     cFile *tmp;
     const char *check;
     int n=0;

     for (const char **kf = keyFiles; kf && *kf; ++kf, ++n) {
         tmp = new cFile(*curFile, *kf);
         check = tmp ? tmp->AbsolutePath() : NULL;

         if (tmp->Exists() && tmp->IsFile() && !tmp->IsDirectory()) {
            switch (n) {
              case 0:  rv = new cLegacyVdrRecording(*curFile); break;
              case 1:  rv = new cVdrRecording(*curFile); break;
              default: rv = new cDVDImage(*curFile); break;
              }
            }
         delete tmp;
         }
     if (!rv) curFile->VisitFiles(createMedia, this);
     }
  else {
     const char *extension = strrchr(Name, '.');

     if (!extension) {
        delete curFile;

        return -1;
        }
     ++extension;
     mimeType = cMovie::ContentType(extension);
     if (mimeType) rv = new cMovie(*curFile, mimeType);
     else {
        mimeType = cAudio::ContentType(extension);
        if (mimeType) rv = new cAudio(*curFile, mimeType);
        else {
           mimeType = cPicture::ContentType(extension);
           if (mimeType) rv = new cPicture(*curFile, mimeType);
           }
        }
     }
  delete curFile;
  if (rv) {
     if (config.WantExtendedScan() && rv->NeedsFurtherScan()) Scan4MetaData(rv);
     mediaPool->push_back(rv);
     return 0;
     }
  return -1;
}

void cMediaFactory::Scan4Media(cManagedVector& pool)
{
  if (!baseDirectory.Exists() || !baseDirectory.IsDirectory()) return;

  baseDirectory.SetVirtualRoot();
  mediaPool = &pool;
  baseDirectory.VisitFiles(createMedia, this);
}

void cMediaFactory::Scan4MetaData(cAbstractMedia* media)
{
  //TODO:
}

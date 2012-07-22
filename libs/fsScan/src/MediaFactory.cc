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
#include <stddef.h>
#include <stdlib.h>
#include <string.h>


cMediaFactory::cMediaFactory(const char *BaseDirectory)
 : baseDirectory(BaseDirectory ? strdup(BaseDirectory) : NULL)
 , scratch(NULL)
 , scratchSize(1024)
{
  if (baseDirectory && *(baseDirectory + strlen(baseDirectory) - 1) == '/')
     *(baseDirectory + strlen(baseDirectory) - 1) = 0;
  scratch = (char *)malloc(scratchSize);
}

cMediaFactory::~cMediaFactory()
{
  free(scratch);
  free(baseDirectory);
}

void cMediaFactory::SetBaseDirectory(const char* dir)
{
  if (baseDirectory == dir) return;
  char *tmp = baseDirectory;
  baseDirectory = NULL;
  free(tmp);
  if (dir) {
     baseDirectory = strdup(dir);
     if (*(baseDirectory + strlen(baseDirectory) - 1) == '/')
        *(baseDirectory + strlen(baseDirectory) - 1) = 0;
     }
}

cAbstractMedia *cMediaFactory::CreateMedia(const char* FileOrDirname, struct stat *st)
{
  const char *name = rindex(FileOrDirname, '/') + 1;
  const char *logical = FileOrDirname + strlen(baseDirectory);
  const char *mimeType = NULL;
  cAbstractMedia *rv = NULL;

//  printf("CreateMedia(%s) ... name=[%s], logical=[%s]\n", FileOrDirname, name, logical);
  if ((st->st_mode & S_IFMT) == S_IFDIR) {
     static const char *addons[] = { "/001.vdr", "/00001.ts", "/VIDEO_TS/VIDEO_TS.IFO", "/video_ts/VIDEO_TS.IFO", "/video_ts/video_ts.ifo", NULL };
     struct stat stBuf;
     int n=0;

     if (scratchSize < (strlen(FileOrDirname) + 32)) {
        scratchSize += 128;
        scratch = (char *)realloc(scratch, scratchSize);
        }
     if (!scratch) return NULL;

     for (const char **pa = addons; pa && *pa; ++pa, ++n) {
         strcpy(scratch, FileOrDirname);
         strcat(scratch, *pa);

         if (stat(scratch, &stBuf) < 0) continue;

         if ((stBuf.st_mode & S_IFMT) == S_IFREG) {
            if (n < 2) {
               char *tmp = rindex(scratch, '/'); // filename
               char *p = tmp;

               *p = ')';
               *(p + 2) = 0;
               tmp = rindex(scratch, '/'); // ts-directory

               for (; p > tmp; --p) *(p + 1) = *p; // shift it up one position
               *(p + 1) = '('; // start of ts-directory
               *tmp = ' '; // add separator
               tmp = rindex(scratch, '/'); // name of vdr recording
               if (tmp) name = tmp + 1;
               }
            switch (n) {
              case 0:  rv = new cLegacyVdrRecording(name, logical, FileOrDirname); break;
              case 1:  rv = new cVdrRecording(name, logical, FileOrDirname); break;
              default: rv = new cDVDImage(name, logical, FileOrDirname); break;
              }
            rv->SetLastModified(st->st_mtime);
            }
         }
     }
  else if ((st->st_mode & S_IFMT) == S_IFREG) {
     const char *extension = rindex(FileOrDirname, '.');

     if (!extension) return NULL;
     ++extension;

     mimeType = cMovie::ContentType(extension);
     if (mimeType) rv = new cMovie(name, logical, FileOrDirname, mimeType);
     else {
        mimeType = cAudio::ContentType(extension);
        if (mimeType) rv = new cAudio(name, logical, FileOrDirname, mimeType);
        else {
           mimeType = cPicture::ContentType(extension);
           if (mimeType) rv = new cPicture(name, logical, FileOrDirname, mimeType);
           }
        }
     if (rv) {
        rv->SetLastModified(st->st_mtime);
        rv->SetSize(st->st_size);
        }
     }
  return rv;
}
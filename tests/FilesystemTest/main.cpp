/*
 * File:   FileSystemTest.cc
 * Author: django
 *
 * Created on 21.07.2012, 12:40:48
 */

#include <stdlib.h>
#include <iostream>
#include <FileSystem.h>
#include <File.h>
#include <StringBuilder.h>
#include <LegacyVdrRecording.h>
#include <VdrRecording.h>
#include <DVDImage.h>
#include <Audio.h>
#include <Picture.h>
#include <Logging.h>
#include <TimeMs.h>
#include <Url.h>
#include <string.h>

int visitor(void *opaque, cFile *Parent, const char *Name)
{
  cFile *child = new cFile(*Parent, Name);

  std::cout << Parent->Name() << " - has child-entry: " << Name << std::endl;
  if (child->IsDirectory()) {
     child->VisitFiles(visitor, opaque);
     }
  char *uri = child->toURI();
  const char *path = child->AbsolutePath();

  std::cout << "child does ";
  if (!child->Exists()) std::cout << "NOT ";
  std::cout << "exists ..." << std::endl;
  std::cout << path << " - has URI: " << uri << std::endl << std::endl;
  free(uri);
  delete child;

  return 0;
}

void test1()
{
  std::cout << "FileSystemTest test 1" << std::endl;
//  cFile *lf = new cFile("/var/lib/video.00");
  cFile *lf = new cFile("/var/local/blah/fasel");
  const char *path = lf->AbsolutePath();

  std::cout << "got file: " << path << std::endl;

  lf->VisitFiles(visitor, NULL);

//  cFile *epgData = new cFile(*lf, "epg.data");
//
//  path = epgData->AbsolutePath();
//  std::cout << "got file: " << path << std::endl;

#ifndef REDNOSE
  cFile *f = new cFile("/media/xchange/");
  path = f->AbsolutePath();

  std::cout << "got file: " << path << std::endl;
  cFile *other = f->Parent();

  other->SetVirtualRoot(true);
  path = other->AbsolutePath();
  std::cout << "parent is file: " << path << std::endl;

  cFile *newOne = new cFile(*other, "/video/test/blah");

  path = newOne->AbsolutePath();
  std::cout << "assembled file: " << path << std::endl;

  cFile *again = new cFile("/media/audio/Collection/Rock/Idol, Billy");

  path = again->AbsolutePath();
  std::cout << "re-assembled file: " << path << std::endl;

  std::cout << path << " does ";
  if (!again->Exists()) std::cout << "NOT ";
  std::cout << "exists" << std::endl;

  again->VisitFiles(visitor, NULL);

  delete again;
  delete newOne;
  delete other;
  delete f;
//  delete epgData;
#endif
  delete lf;
  cUrl::Cleanup();
  cFile::Cleanup();
}

int check4Media(void *opaque, cFile *Parent, const char *Name)
{
  if (!opaque) return -1;
  std::vector<cAbstractMedia *> *pool = (std::vector<cAbstractMedia *> *) opaque;
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
     if (!rv) curFile->VisitFiles(check4Media, opaque);
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
     pool->push_back(rv);
     return 0;
     }
  else return -1;
}

void test2()
{
  std::cout << "FileSystemTest test 2" << std::endl;
  cFile relative("srclient.conf");
  const char *path = relative.AbsolutePath();

  std::cout << "relative path is now: " << path << std::endl;
  cUrl::Cleanup();
  cFile::Cleanup();
}

void test3()
{
  std::cout << "FileSystemTest test 3" << std::endl;
  cFile mediaRoot("/media");
  cFile &startScan = mediaRoot; //("/media/images");

  if (!mediaRoot.Exists() || !mediaRoot.IsDirectory())
     std::cout << "%TEST_FAILED% time=0 testname=test3 (FileSystemTest) message=error message sample" << std::endl;
  if (!startScan.Exists() || !startScan.IsDirectory())
     std::cout << "%TEST_FAILED% time=0 testname=test3 (FileSystemTest) message=error message sample" << std::endl;

  mediaRoot.SetVirtualRoot();
  std::vector<cAbstractMedia *> mediaPool;

  uint64_t start = cTimeMs::Now();
  startScan.VisitFiles(check4Media, &mediaPool);
  uint64_t end = cTimeMs::Now();

  for (size_t i=0; i < mediaPool.size(); ++i) {
      std::cout << "pool entry: " << mediaPool[i]->Name() << std::endl;
      }
  //19: got 9998 media in  8081ms.
  //    ==9779==   total heap usage: 637,920 allocs, 637,918 frees, 172,023,271 bytes allocated
  //01: got 5739 media in 88165ms.
  //    ==2605==   total heap usage: 924,253 allocs, 924,247 frees, 259,567,759 bytes allocated
  std::cout << "got " << mediaPool.size() << " media in " << (end - start) << "ms." << std::endl;
  for (size_t i=0; i < mediaPool.size(); ++i) {
      delete mediaPool[i];
      }
  cUrl::Cleanup();
  cFile::Cleanup();
}

int main(int argc, char** argv)
{
  uint64_t t0 = cTimeMs::Now();
  std::cout << "%SUITE_STARTING% FileSystemTest" << std::endl;
  std::cout << "%SUITE_STARTED%" << std::endl;

  std::cout << "%TEST_STARTED% test1 (FileSystemTest)" << std::endl;
  uint64_t start = cTimeMs::Now();
  test1();
  uint64_t end = cTimeMs::Now();
  std::cout << "%TEST_FINISHED% time=" << (double)(end - start) / 1000 << " test1 (FileSystemTest)" << std::endl;

  std::cout << "%TEST_STARTED% test2 (FileSystemTest)\n" << std::endl;
  start = cTimeMs::Now();
  test2();
  end = cTimeMs::Now();
  std::cout << "%TEST_FINISHED% time=" << (double)(end - start) / 1000 << " test2 (FileSystemTest)" << std::endl;

  std::cout << "%TEST_STARTED% test3 (FileSystemTest)\n" << std::endl;
  start = cTimeMs::Now();
  test3();
  end = cTimeMs::Now();
  std::cout << "%TEST_FINISHED% time=" << (double)(end - start) / 1000 << " test3 (FileSystemTest)" << std::endl;

  std::cout << "%SUITE_FINISHED% time=" << (double)(cTimeMs::Now() - t0) / 1000 << std::endl;

  return (EXIT_SUCCESS);
}

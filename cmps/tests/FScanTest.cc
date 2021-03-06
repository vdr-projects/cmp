/**
 * ======================== legal notice ======================
 * 
 * File:      FScanTest.cc
 * Created:   02.07.2012, 16
 * Author:    <a href="mailto:geronimo013@gmx.de">Geronimo</a>
 * Project:   cmps - the backend (server) part of compound media player
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
#include <Audio.h>
#include <Movie.h>
#include <Picture.h>
#include <FSMediaScanner.h>
#include <MediaFactory.h>
#include <MediaServerConfig.h>
#include <TimeMs.h>
#include <stdlib.h>
#include <iostream>

class FScanTest {
public:
  static void test1(void);
  static void test2(void);
  static void test3(void);
  static void test4(void);
};

void FScanTest::test1()
{
  std::cout << "FScanTest test 1" << std::endl;

  for (SupportedExtension *se = cAudio::knownExtensions; se && se->extension; ++se) {
      std::cout << "Audio: known extension \"" << se->extension << "\" has type: " << se->mimeType << std::endl;
      }
}

void FScanTest::test2()
{
  std::cout << "FScanTest test 2" << std::endl;

  for (SupportedExtension *se = cMovie::knownExtensions; se && se->extension; ++se) {
      std::cout << "Video: known extension \"" << se->extension << "\" has type: " << se->mimeType << std::endl;
      }
}

void FScanTest::test3()
{
  std::cout << "FScanTest test 3" << std::endl;

  for (SupportedExtension *se = cPicture::knownExtensions; se && se->extension; ++se) {
      std::cout << "Picture: known extension \"" << se->extension << "\" has type: " << se->mimeType << std::endl;
      }
}

void FScanTest::test4()
///< result from java pendant: FSScanner - scanning of 9970 media took      46 ms
///< own result:                                 found 9970 media,  in      58 ms.
///< file server (mostly recordings)             found 2828 media,  in   53525 ms.
///< file server (added 18G audio)               found 5698 media,  in   44653 ms.
///< file server (same files, fresh reboot)      found 5698 media,  in   54723 ms.
///< new own result using cFile                  found 10002 media, in     601 ms.  (first run)
///< new own result using cFile                  found 10002 media, in     177 ms.  (second run)
///< with mediascan                              found 10002 media, in   80570 ms.
///< with mediascan and saving values            found 10002 media, in   93675 ms.
///< with mediascan, scanning each media         found 10002 media, in  247096 ms.
///< java - mediascan for each media       scanning of  9312 media took 215037 ms. (with key file)
{
  cMediaServerConfig config("/var/lib/cmp");
  cFSMediaScanner scanner;
  cAbstractMedia *media;

  config.Load("srserver.conf");
  config.SetAuthorizationRequired(false);
  config.Dump();

  std::cout << "FScanTest test 4" << std::endl;
  scanner.SetMediaFactory(new cMediaFactory(config));

  uint64_t start = cTimeMs::Now();
  scanner.Refresh();
  uint64_t end = cTimeMs::Now();
  size_t grouped[cAbstractMedia::Unknown];
  int mx = sizeof(grouped) / sizeof(size_t);

  for (int i=0; i < mx; ++i) grouped[i] = 0;
  for (size_t i=0; i < scanner.MediaPool().size(); ++i) {
      media = (cAbstractMedia *) scanner.MediaPool()[i];

      ++grouped[media->MediaType()];
      media->Dump();
      }
  std::cout << std::endl << "found " << scanner.MediaPool().size() << " media, in " << end - start << " ms." << std::endl;

  const char *file2Search = "/pretty/unsupported/media/file/in/any/known.workstation";

  // search (worst case)
  start = cTimeMs::Now();
  media = scanner.FindMedia(file2Search);
  end = cTimeMs::Now();

  std::cout << "array search took " << end - start << " ms." << std::endl;

  for (int i=0; i < mx; ++i) {
      std::cout << cAbstractMedia::MediaType2Text(i) << " has " << grouped[i] << " members." << std::endl;
      }
  cFile::Cleanup();
}

int main(int argc, char** argv)
{
  int MaxPossibleFileDescriptors = getdtablesize();

  std::cout << "maximum of open files #" << MaxPossibleFileDescriptors << std::endl << std::endl;
  uint64_t t0 = cTimeMs::Now();
  std::cout << "%SUITE_STARTING% FScanTest" << std::endl;
  std::cout << "%SUITE_STARTED%" << std::endl;

  std::cout << "%TEST_STARTED% test1 (FScanTest)" << std::endl;
  uint64_t start = cTimeMs::Now();
  FScanTest::test1();
  uint64_t end = cTimeMs::Now();
  std::cout << "%TEST_FINISHED% time=" << (double)(end - start) / 1000 << " test1 (FScanTest)" << std::endl;

  std::cout << "%TEST_STARTED% test2 (FScanTest)" << std::endl;
  start = cTimeMs::Now();
  FScanTest::test2();
  end = cTimeMs::Now();
  std::cout << "%TEST_FINISHED% time=" << (double)(end - start) / 1000 << " test2 (FScanTest)" << std::endl;

  std::cout << "%TEST_STARTED% test3 (FScanTest)" << std::endl;
  start = cTimeMs::Now();
  FScanTest::test3();
  end = cTimeMs::Now();
  std::cout << "%TEST_FINISHED% time=" << (double)(end - start) / 1000 << " test3 (FScanTest)" << std::endl;

  std::cout << "%TEST_STARTED% test4 (FScanTest)" << std::endl;
  start = cTimeMs::Now();
  FScanTest::test4();
  end = cTimeMs::Now();
  std::cout << "%TEST_FINISHED% time=" << (double)(end - start) / 1000 << " test4 (FScanTest)" << std::endl;

  std::cout << "%SUITE_FINISHED% time=" << (double)(cTimeMs::Now() - t0) / 1000 << std::endl;

  return (EXIT_SUCCESS);
}


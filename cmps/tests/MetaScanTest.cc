/**
 * ======================== legal notice ======================
 * 
 * File:      MetaScanTest.cc
 * Created:   27.07.2012, 10:03
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
#include <File.h>
#include <FileReader.h>
#include <LineReader.h>
#include <ConfigReader.h>
#include <CommandReader.h>
#include <MediainfoReader.h>
#include <MediaInfo/MediaInfo.h>
#include <MediaServerConfig.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <tr1/tuple>

void parseConfig(const char *FileName)
{
#ifdef OLD_STUFF
  cConfigReader *cr = new cConfigReader(new cLineReader(new cFileReader(new cFile(FileName))));
  cConfigReader::ConfigEntry *ce;

  while ((ce = cr->ReadEntry())) {
        std::cout << "config entry [" << std::get<0>(*ce) << "] => " << std::get<1>(*ce) << std::endl;
        delete ce;
        }
  cr->Close();
  delete cr;
#else
  cMediaServerConfig msc("/var/lib/cmp");

  msc.Load("srserver.conf");
  msc.Dump();
#endif
}

void dumpTextfile(const char *FileName)
{
  cLineReader *lr = new cLineReader(new cFileReader(new cFile(FileName)));
  const char *line;

  while ((line = lr->ReadLine())) {
        std::cout << "line: " << line << std::endl;
        }
  delete lr;
}

void setupMediainfo(void)
{
  static const char *MetaKeys[] = {
  "Format"
  //Audio
, "Duration"
, "Album"
, "Track name"
, "Performer"
, "Bit rate"
  //Image
, "Width"
, "Height"
  //Video
, "Display aspect ratio"
, "Scan type"
, NULL
  };
  cMediainfoReader::Setup(MetaKeys);
}

void testMediaInfo(const char *FileName)
{
  cCommandReader *cr = new cCommandReader("/usr/bin/mediainfo");
  cMediainfoReader *mir = new cMediainfoReader(new cLineReader(cr));
  cMediainfoReader::InfoEntry *ie;

  cr->AddCommandParameter(FileName);
  while ((ie = mir->ReadEntry())) {
        std::cout << "media info - [" << std::get<0>(*ie) << "] ==> " << std::get<1>(*ie) << std::endl;
        delete ie;
        }
  mir->Close();
  delete mir;
}

void testMediaFiles(const char *FileName)
{
  cLineReader *lr = new cLineReader(new cFileReader(new cFile(FileName)));
  const char *line;

  setupMediainfo();
  while ((line = lr->ReadLine())) {
        std::cout << std::endl << "media-test-file: " << line << std::endl;
        testMediaInfo(line);
        }
  lr->Close();
  delete lr;
}

static const short BufferSize = 100;
enum PipeFileDescriptors {
  READ_FD = 0,
  WRITE_FD = 1
};

void testCommandReader()
{
  cCommandReader *cr = new cCommandReader("/bin/ls");
  cLineReader *lr = new cLineReader(cr);
  const char *line;

  cr->AddCommandParameter("-al");
  cr->AddCommandParameter("--color");

  while ((line = lr->ReadLine())) {
        std::cout << "from command: " << line << std::endl;
        }
  delete lr;
};

int main()
{
  char buf[256];

  std::cout << "working directory is: " << getcwd(buf, sizeof(buf)) << std::endl;
  dumpTextfile("srclient.conf");

  std::cout << std::endl << "===========================================" << std::endl << std::endl;
  parseConfig("srserver.conf");

  std::cout << std::endl << "===========================================" << std::endl << std::endl;
  testCommandReader();

//  std::cout << std::endl << "===========================================" << std::endl << std::endl;
//  testMediaFiles("testMedia.txt");

  cFile::Cleanup();
  return 0;
}

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
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <tr1/tuple>

static void parseConfig(const char *FileName)
{
  cConfigReader *cr = new cConfigReader(new cLineReader(new cFileReader(new cFile(FileName))));
  cConfigReader::ConfigEntry *ce;

  while ((ce = cr->ReadEntry())) {
        std::cout << "config entry [" << std::get<0>(*ce) << "] => " << std::get<1>(*ce) << std::endl;
        delete ce;
        }
  cr->Close();
  delete cr;
}

static void dumpTextfile(const char *FileName)
{
  cLineReader *lr = new cLineReader(new cFileReader(new cFile(FileName)));
  const char *line;

  while ((line = lr->ReadLine())) {
        std::cout << "line: " << line << std::endl;
        }
  delete lr;
}

static void setupMediainfoReader(cMediainfoReader *mir)
{
  mir->AddValuableKey("Format");
  //Audio
  mir->AddValuableKey("Duration");
  mir->AddValuableKey("Album");
  mir->AddValuableKey("Track name");
  mir->AddValuableKey("Performer");
  mir->AddValuableKey("Bit rate");
  //Image
  mir->AddValuableKey("Width");
  mir->AddValuableKey("Height");
  //Video
  mir->AddValuableKey("Display aspect ratio");
  mir->AddValuableKey("Scan type");
}

static void testMediaInfo(const char *FileName)
{
  cCommandReader *cr = new cCommandReader("/usr/bin/mediainfo");
//  cFileReader *fr = new cFileReader(new cFile("mi.output"));
  cMediainfoReader *mir = new cMediainfoReader(new cLineReader(cr));
  cMediainfoReader::InfoEntry *ie;

  cr->AddCommandParameter(FileName);
  setupMediainfoReader(mir);
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

static void testCommandReader()
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
//  testMediaInfo("blah");
  dumpTextfile("srclient.conf");

  std::cout << std::endl << "===========================================" << std::endl << std::endl;
  parseConfig("srserver.conf");

  std::cout << std::endl << "===========================================" << std::endl << std::endl;
  testCommandReader();

  std::cout << std::endl << "===========================================" << std::endl << std::endl;
  testMediaFiles("testMedia.files");

  cFile::Cleanup();
  return 0;
}

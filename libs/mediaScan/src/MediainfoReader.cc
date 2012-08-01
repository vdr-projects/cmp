/**
 * ======================== legal notice ======================
 * 
 * File:      MediainfoReader.cc
 * Created:   30. Juli 2012, 15:03
 * Author:    <a href="mailto:geronimo013@gmx.de">Geronimo</a>
 * Project:   libMediaScan: mediatypes and media scanning
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
#include <MediainfoReader.h>
#include <LineReader.h>
#include <stddef.h>
#include <pcrecpp.h>
#include <vector>

static pcrecpp::RE comment("^\\s*#.*$");
static pcrecpp::RE emptyLine("^\\s*$");
static pcrecpp::RE entry("^\\s*(.+?)\\s*:\\s*(.+?)\\s*$");
std::vector<std::string> cMediainfoReader::valuableKeys;


cMediainfoReader::cMediainfoReader(cLineReader *LineReader)
 : reader(LineReader)
{
}

cMediainfoReader::~cMediainfoReader()
{
  Close();
}

void cMediainfoReader::Close(void)
{
  if (reader) {
     delete reader;
     reader = NULL;
     }
}

bool cMediainfoReader::IsValuable(std::string &key)
{
  for (size_t i=0; i < valuableKeys.size(); ++i) {
      if (!strcmp(key.c_str(), valuableKeys[i].c_str()))
         return true;
      }
  return false;
}

cMediainfoReader::InfoEntry *cMediainfoReader::ReadEntry()
{
  if (!reader) return NULL;
  const char *line = reader->ReadLine();
  std::string name, value;
  InfoEntry *rv = NULL;

  do {
     if (line && entry.FullMatch(line, &name, &value)) {
        if (IsValuable(name)) {
           rv = new InfoEntry(name, value);
           break;
           }
        }
     line = reader->ReadLine();
     } while (line && !rv);

  return rv;
}

void cMediainfoReader::Setup(const char* keys[])
{
  valuableKeys.clear();
  for (const char **p = keys; p && *p; ++p) {
      valuableKeys.push_back(*p);
      }
}
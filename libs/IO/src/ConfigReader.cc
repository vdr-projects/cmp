/**
 * ======================== legal notice ======================
 * 
 * File:      ConfigReader.cc
 * Created:   28. Juli 2012, 18:41
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
#include <ConfigReader.h>
#include <LineReader.h>
#include <stddef.h>
#include <pcrecpp.h>

cConfigReader::cConfigReader(cLineReader *LineReader)
 : reader(LineReader)
{
}

cConfigReader::~cConfigReader()
{
  Close();
}

void cConfigReader::Close(void)
{
  if (reader) {
     delete reader;
     reader = NULL;
     }
}

cConfigReader::ConfigEntry *cConfigReader::ReadEntry()
{
  if (!reader) return NULL;
  const char *line = reader->ReadLine();
  static pcrecpp::RE comment("^\\s*#.*$");
  static pcrecpp::RE emptyLine("^\\s*$");
  static pcrecpp::RE entry("^\\s*(\\S+)\\s*=\\s*(.+)$");
  std::string name, value;
  ConfigEntry *rv = NULL;

  while (line && (comment.FullMatch(line) || emptyLine.FullMatch(line)))
        line = reader->ReadLine();
  if (line && entry.FullMatch(line, &name, &value)) {
     rv = new ConfigEntry(name, value);
     }
  return rv;
}

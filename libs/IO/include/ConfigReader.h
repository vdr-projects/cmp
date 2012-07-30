/**
 * ======================== legal notice ======================
 *
 * File:      ConfigReader.h
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
#ifndef CONFIGREADER_H
#define	CONFIGREADER_H

#include <tuple>
#include <string>

class cLineReader;
class cConfigReader {
public:
  typedef std::tuple <std::string, std::string> ConfigEntry;

  cConfigReader(cLineReader *LineReader);
  virtual ~cConfigReader();

  void Close(void);
  ConfigEntry *ReadEntry(void);

private:
  cLineReader *reader;
  };

#endif	/* CONFIGREADER_H */


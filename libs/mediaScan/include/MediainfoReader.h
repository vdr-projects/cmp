/**
 * ======================== legal notice ======================
 * 
 * File:      MediainfoReader.h
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
#ifndef MEDIAINFOREADER_H
#define	MEDIAINFOREADER_H

#include <tuple>
#include <string>
#include <vector>

class cLineReader;
class cMediainfoReader {
public:
  typedef std::tuple <std::string, std::string> InfoEntry;

  cMediainfoReader(cLineReader *LineReader);
  virtual ~cMediainfoReader();

  void Close(void);
  bool IsValuable(std::string &key);
  InfoEntry *ReadEntry(void);
  static void Setup(const char *keys[]);

private:
  cLineReader *reader;
  static std::vector<std::string> valuableKeys;
  };

#endif	/* MEDIAINFOREADER_H */


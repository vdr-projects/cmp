/**
 * ======================== legal notice ======================
 * 
 * File:      CommandReader.h
 * Created:   30. Juli 2012, 06:42
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
#ifndef COMMANDREADER_H
#define	COMMANDREADER_H

#include <Reader.h>
#include <vector>
#include <string>

class cCommandReader : public cReader {
public:
  cCommandReader(const char *cmd);
  virtual ~cCommandReader();

  void AddCommandParameter(const char *Param);

protected:
  virtual bool Open(void);
  virtual void Close(void);

private:
  pid_t pid;
  std::vector<std::string> args;
  static int fdMax;
  };

#endif	/* COMMANDREADER_H */


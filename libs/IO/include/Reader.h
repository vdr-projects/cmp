/**
 * ======================== legal notice ======================
 * 
 * File:      Reader.h
 * Created:   30. Juli 2012, 06:44
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
#ifndef READER_H
#define	READER_H

class cReader {
public:
  cReader();
  virtual ~cReader();
  virtual int Read(char *buf, int bufSize);

protected:
  virtual bool Open(void) = 0;
  virtual void Close(void) = 0;
  int fd;
  };

#endif	/* READER_H */


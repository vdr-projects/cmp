/**
 * ======================== legal notice ======================
 * 
 * File:      AbstractMultiFileMovie.h
 * Created:   3. Juli 2012, 07
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
#ifndef ABSTRACTMULTIFILEMOVIE_H
#define	ABSTRACTMULTIFILEMOVIE_H

#include <Movie.h>

class cAbstractMultiFileMovie : public cMovie {
public:
  virtual ~cAbstractMultiFileMovie();

  virtual size_t ReadChunk(char *buf, size_t bufSize);
  virtual const char *KeyFile(void) const;
  virtual const char *Name(void) const { return name; }
  virtual const char *FirstFile(void) const = 0;
  virtual const char *NextFile(void) = 0;
  virtual size_t Size(void) const { return size; }

protected:
  cAbstractMultiFileMovie(const cFile &File, const char *Mime, SupportedMediaType Type);
  virtual void Reset(void);
  void SetName(char *Name);
  void SetSize(size_t Size);
  bool checkBuffer(void) const;
  int movieFiles;
  int curFileNo;
  mutable char *buf;
  int bufSize;

private:
  char *name;   ///< name of multifile media may be different from any filesystem name, so handle a copy
  size_t size;
  };

#endif	/* ABSTRACTMULTIFILEMOVIE_H */


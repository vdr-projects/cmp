/**
 * ======================== legal notice ======================
 * 
 * File:      AbstractMedia.h
 * Created:   2. Juli 2012, 14
 * Author:    <a href="mailto:geronimo013@gmx.de">Geronimo</a>
 * Project:   libfsScan: mediatypes and filesystem scanning
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
#ifndef ABSTRACTMEDIA_H
#define	ABSTRACTMEDIA_H

#include <sys/types.h>
#include <sys/stat.h>
#include <vector>

typedef struct {
  const char *extension;
  const char *mimeType;
} SupportedExtension;

class cAbstractMedia {
public:
  typedef enum {
    Invalid,
    Audio,
    Movie,
    DVDImage,
    LegacyVdrRecording,
    VdrRecording,
    Picture,
    Unknown
    } SupportedMediaType;

  virtual ~cAbstractMedia();

  virtual void Refresh(void);
  ///< will be called right before start streaming, so this call is used to
  ///< determine the real size, number of files, etc.
  virtual size_t ReadChunk(char *buf, size_t bufSize);
  ///< used to hide the differences between single- and multi-file media.

  SupportedMediaType MediaType(void) const { return mediaType; }
  const char *LogicalPath(void) const { return logicalPath; }
  const char *RealPath(void) const { return realPath; }
  const char *Name(void) const { return name; }
  const char *MimeType(void) const { return mimeType; }
  time_t LastModified(void) const { return lastModified; }
  void SetLastModified(time_t when) { lastModified = when; }
  size_t Size(void) const { return size; }
  void SetSize(size_t Size) { size = Size; }
  static const char *MediaType2Text(int Type);

protected:
  cAbstractMedia(SupportedMediaType Type, const char *Name, const char *Logical, const char *Path, const char *Mime);
  int fd;

private:
  SupportedMediaType mediaType;
  char *logicalPath;
  char *realPath;
  char *name;
  char *mimeType;
  time_t lastModified;
  size_t size;
  };

#endif	/* ABSTRACTMEDIA_H */


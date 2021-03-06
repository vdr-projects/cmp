/**
 * ======================== legal notice ======================
 * 
 * File:      AbstractMedia.h
 * Created:   2. Juli 2012, 14
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
#ifndef ABSTRACTMEDIA_H
#define	ABSTRACTMEDIA_H

#include <File.h>
#include <MediainfoReader.h>
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
    IMovie,
    DVDImage,
    IDVDImage,
    LegacyVdrRecording,
    ILegacyVdrRecording,
    VdrRecording,
    IVdrRecording,
    Picture,
    Unknown
    } SupportedMediaType;

  virtual ~cAbstractMedia();

  virtual void AddMeta(cMediainfoReader::InfoEntry *Entry);
  SupportedMediaType MediaType(void) const { return mediaType; }
  const char *MimeType(void) const { return mimeType; }
  const char *AbsolutePath(void) const;
  const char *Format(void) const { return format; }
  virtual const char *KeyFile(void) const;
  ulong LastModified(void) const;
  const char *LogicalPath(void) const { return logicalPath; }
  virtual const char *Name(void) const;
  virtual bool NeedsFurtherScan(void) const;
  virtual size_t Size(void) const;
  virtual const char *URI(void) const { return uri; }
  virtual void Refresh(void);
      ///< will be called right before start streaming, so this call is used to
      ///< determine the real size, number of files, etc.
  virtual size_t ReadChunk(char *buf, size_t bufSize);
      ///< used to hide the differences between single- and multi-file media.
  virtual void Reset(void);
  int Width(void) const { return width; }
  int Height(void) const { return height; }
  void Dump(void) const;
  static const char *MediaType2Text(int Type);

protected:
  cAbstractMedia(const cFile &File, const char *Mime, SupportedMediaType Type);
  virtual void SetFormat(const char *Format);
  void SetMediaType(int NewType);
  void SetMimeType(const char *MimeType);
  const cFile &KeyPath(void) const { return keyPath; }
  std::vector<cMediainfoReader::InfoEntry *> meta;
  int fd;
  char *format;
  short width;
  short height;
  double aspect;

private:
  SupportedMediaType mediaType;
  char *mimeType;
  char *uri;
  char *logicalPath;
  cFile keyPath;
  };

#endif	/* ABSTRACTMEDIA_H */


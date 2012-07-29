/**
 * ======================== legal notice ======================
 * 
 * File:      Url.h
 * Created:   4. Juli 2012, 05
 * Author:    <a href="mailto:geronimo013@gmx.de">Geronimo</a>
 * Project:   libutil - base classes used by other libraries
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
#ifndef URL_H
#define	URL_H

#include <stddef.h>
#include <string>
#include <tr1/unordered_map>
class cURLEncoder;
class cURLDecoder;

class cUrl {
///< splits an url into machine readable parts:
///< from top-level sight, an url consists of url and querystring. Looking bit closer,
///< the url consists of toplevel and path, where as the querystring is a list of
///< name/value tuples with value being an optional part.
public:
  cUrl(const char *RawURL);
  virtual ~cUrl();
  const char *Parameter(const char *Name);
  void SetParameter(const char* Name, const char* Value = NULL);
  size_t EstimatedSize(void) const; ///< is a rough guess about the size of the final encoded url
  void ParseURL(const char *URL);
  char *ToString(void) const; ///< writes the url to a newly allocated buffer
  int WriteBuf(char *buf, size_t bufSize) const; ///< writes the url to preexisting buffer
  ///< returns the characters written. -1 as return value indicates a buffer overrun.
  const char * Path() const { return path; }
#ifdef DEBUG
  void Dump(void);
#endif
  static void Cleanup(void);
  static cURLEncoder *Encoder(void);
  static cURLDecoder *Decoder(void);

protected:
  void ParseQueryString(const char *QueryString);

private:
  typedef std::tr1::unordered_map<std::string, std::string> ParameterMap;
  char *path;
  ParameterMap parameters;
  };

#endif	/* URL_H */


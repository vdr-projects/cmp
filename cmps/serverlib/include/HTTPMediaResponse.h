/**
 * ======================== legal notice ======================
 * 
 * File:      HTTPMediaResponse.h
 * Created:   6. Juli 2012, 07
 * Author:    <a href="mailto:geronimo013@gmx.de">Geronimo</a>
 * Project:   cmps - the backend (server) part of compound media player
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
#ifndef HTTPMEDIARESPONSE_H
#define	HTTPMEDIARESPONSE_H

#include <HTTPFileResponse.h>
#include <AbstractMedia.h>

class cHTTPMediaResponse : public cHTTPFileResponse {
public:
  cHTTPMediaResponse(cAbstractMedia *Media);
  virtual ~cHTTPMediaResponse();

  virtual size_t ReadContentChunk(char *Buf, size_t bufSize);

private:
  cAbstractMedia *media;
};

#endif	/* HTTPMEDIARESPONSE_H */


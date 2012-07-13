/**
 * ======================== legal notice ======================
 * 
 * File:      MediaFileHandler.h
 * Created:   5. Juli 2012, 08:06
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
#ifndef MEDIAFILEHANDLER_H
#define	MEDIAFILEHANDLER_H

#include <AbstractMediaRequestHandler.h>

class cHTTPRequest;
class cHTTPResponse;
class cStringBuilder;
class cMediaFileHandler : public cAbstractMediaRequestHandler {
public:
  cMediaFileHandler();
  virtual ~cMediaFileHandler();

  virtual cHTTPResponse *ProcessRequest(cHTTPRequest &Request);
  virtual void Usage(cStringBuilder &sb);
  };

#endif	/* MEDIAFILEHANDLER_H */


/**
 * ======================== legal notice ======================
 * 
 * File:      AbstractMediaRequestHandler.cc
 * Created:   5. Juli 2012, 07
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
#include <AbstractMediaRequestHandler.h>
#include <FSMediaScanner.h>

static cFSMediaScanner *scanner = NULL;

cAbstractMediaRequestHandler::cAbstractMediaRequestHandler()
{
}

cAbstractMediaRequestHandler::~cAbstractMediaRequestHandler()
{
}

cFSMediaScanner *cAbstractMediaRequestHandler::FSMediaScanner(void)
{
  return scanner;
}

void cAbstractMediaRequestHandler::SetFSMediaScanner(cFSMediaScanner* Scanner)
{
  scanner = Scanner;
}
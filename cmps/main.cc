/**
 * ======================== legal notice ======================
 * 
 * File:      main.cc
 * Created:   2. Juli 2012, 16:51
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
#include <HTTPServer.h>
#include <HTTPRequest.h>
#include <HTTPResponse.h>
#include <FilesystemScanner.h>
#include <MediaFactory.h>
#include <MediaListHandler.h>
#include <MediaFileHandler.h>
#include <ConnectionHandler.h>
#include <CommandHandler.h>
#include <JSonListAssembler.h>
#include <HTMLListAssembler.h>
#include <Url.h>
#include <stdio.h>


static int refreshScanner(void *opaque, cHTTPRequest &Request)
{
  cFilesystemScanner *fsc = (cFilesystemScanner *)opaque;

  if (fsc) {
     fsc->Refresh();
     return 0;
     }
  return -1;
}

/*
 *
 */
int main(int argc, char** argv)
{
  cServerConfig config(12345);

  config.SetAuthorizationRequired(false);
  config.SetDocumentRoot("/media");
  config.SetAppIcon("/media/favicon.ico");

  //TODO: parse commandline, read config

  cFilesystemScanner *scanner = new cFilesystemScanner();
  if (!scanner) {
     fprintf(stderr, "could not initialize application! (1)");
     exit(-1);
     }
  scanner->SetMediaFactory(new cMediaFactory(config.DocumentRoot()));

  cAbstractMediaRequestHandler::SetFilesystemScanner(scanner);
  /*
   * register request handlers with their uri-prefix
   */
  cConnectionHandler::RegisterRequestHandler("/cmd", new cCommandHandler());
  cMediaListHandler *listHandler = new cMediaListHandler();

  listHandler->SetListAssembler("json", new cJSonListAssembler());
  listHandler->SetDefaultListAssembler(new cHTMLListAssembler());
  cConnectionHandler::RegisterRequestHandler("/", listHandler);
  cConnectionHandler::RegisterDefaultHandler(new cMediaFileHandler());

  /*
   * create the real server
   */
  cHTTPServer *server = new cHTTPServer(config);
  if (!server) {
     fprintf(stderr, "could not initialize application! (2)");
     exit(-2);
     }

  /*
   * register/enable internal commands
   */
  cCommandHandler::RegisterCallback("refresh", refreshScanner, scanner);
  scanner->Refresh();

  /*
   * now start the server
   */
  if (!server->Start()) {
     fprintf(stderr, "failed to start application (3)");
     exit(-3);
     }

  //Cleanup:
  cCommandHandler::Cleanup();
  free((void *)cHTTPResponse::ServerID());
  cUrl::Cleanup();
  delete scanner;
  delete server;

  return 0;
}


/**
 * ======================== legal notice ======================
 *
 * File:      main.cc
 * Created:   2. Juli 2012, 16
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
#include <String.h>
#include <stdio.h>
#include <getopt.h>

static struct option longOptions[] = {
  { "port",      required_argument, NULL, 'p' }
, { "mediaRoot", required_argument, NULL, 'r' }
, { "favicon",   required_argument, NULL, 'i' }
, { NULL, no_argument, NULL, 0 }
};

static int refreshScanner(void *opaque, cHTTPRequest &Request)
{
  cFilesystemScanner *fsc = (cFilesystemScanner *)opaque;

  if (fsc) {
     fsc->Refresh();
     return 0;
     }
  return -1;
}

static void parseCommandline(int argc, char *argv[], cServerConfig &config)
{
  int c;

  // set defaults first
  config.SetAuthorizationRequired(false);
  config.SetDocumentRoot("/media");
  config.SetAppIcon("/media/favicon.ico");

  while ((c = getopt_long(argc, argv, "p:r:i:", longOptions, NULL)) != -1) {
        switch (c) {
          case 'p': {
               if (isnumber(optarg)) {
                  int n = atoi(optarg);

                  if (n > 0) config.SetPort(n);
                  }
               } break;

          case 'r': {
               struct stat st;

               if (!stat(optarg, &st)) {
                  if ((st.st_mode & S_IFMT) == S_IFDIR && (st.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))) {
                     config.SetDocumentRoot(optarg);
                     }
                  }
               } break;

          case 'i': {
               struct stat st;

               if (!stat(optarg, &st)) {
                  if ((st.st_mode & S_IFMT) == S_IFREG && (st.st_mode & (S_IRUSR | S_IRGRP | S_IROTH))) {
                     config.SetAppIcon(optarg);
                     }
                  }
               } break;
          }
        }
}

int main(int argc, char** argv)
{
  cServerConfig config(12345);

  parseCommandline(argc, argv, config);

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
  cFile::Cleanup();
  delete scanner;
  delete server;

  return 0;
}


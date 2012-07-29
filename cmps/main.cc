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
#include <FSMediaScanner.h>
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
  { "appDir", required_argument, NULL, 'd' }
, { "realm",  required_argument, NULL, 'r' }
, { "help",   no_argument,       NULL, 'h' }
, { NULL, no_argument, NULL, 0 }
};

static int refreshScanner(void *opaque, cHTTPRequest &Request)
{
  cFSMediaScanner *fsc = (cFSMediaScanner *)opaque;

  if (fsc) {
     fsc->Refresh();
     return 0;
     }
  return -1;
}

static void usage(void)
{
  fprintf(stderr, "cmps - the backend of CMP (compound media player)\n");
  fprintf(stderr, "  is streaming- and HTTP-server and accepts these commandline options:\n");
  fprintf(stderr, "-h, --help            the help, you are reading\n");
  fprintf(stderr, "-d, --appDir <path>   the directory, where the server may write config files\n");
  fprintf(stderr, "                       (default is /var/lib/cmp)\n");
  fprintf(stderr, "-r, --realm <path>    absolute path to credential file. That file must be\n");
  fprintf(stderr, "                      writable to enable remote administration of principals)\n");
  fprintf(stderr, "                       (default is no file / no authorization required)\n");

  exit(0);
}

static void setup(int argc, char *argv[], cServerConfig &config)
{
  int c;

  // set defaults first
  config.SetAuthorizationRequired(false);
  config.SetDocumentRoot("/media");
  config.SetAppIcon("/media/favicon.ico");

  while ((c = getopt_long(argc, argv, "hp:r:i:", longOptions, NULL)) != -1) {
        switch (c) {
          case 'd': {
               cFile appDir(optarg);

               if (appDir.Exists() && appDir.IsDirectory() && appDir.CanWrite()) {
                  config.SetConfigBaseDir(appDir.AbsolutePath());
                  }
               } break;

          case 'r': {
               cFile credentials(optarg);

               if (credentials.Exists() && credentials.CanRead()) {
                  config.SetCredentialsFile(credentials.AbsolutePath());
                  }
               } break;

          case 'h': usage(); break;
          }
        }
  config.Load("srserver.conf");
  if (!config.CredentialsFile() && config.AuthorizationRequired()) config.SetAuthorizationRequired(false);
  config.Dump();
}

int main(int argc, char** argv)
{
  cServerConfig config("/var/lib/cmp");

  setup(argc, argv, config);
  cFSMediaScanner *scanner = new cFSMediaScanner();
  if (!scanner) {
     fprintf(stderr, "could not initialize application! (1)");
     exit(-1);
     }
  scanner->SetMediaFactory(new cMediaFactory(config));

  cAbstractMediaRequestHandler::SetFSMediaScanner(scanner);
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


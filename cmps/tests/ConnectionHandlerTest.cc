/**
 * ======================== legal notice ======================
 * 
 * File:      ConnectionHandlerTest.cc
 * Created:   10.07.2012, 05:48:23
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
#include <ConnectionHandler.h>
#include <ServerConfig.h>
#include <FilesystemScanner.h>
#include <MediaFactory.h>
#include <MediaListHandler.h>
#include <MediaFileHandler.h>
#include <CommandHandler.h>
#include <JSonListAssembler.h>
#include <HTMLListAssembler.h>
#include <HTTPRequest.h>
#include <HTTPResponse.h>
#include <TimeMs.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>

class cTestUnit {
public:
  cTestUnit(const char *Name, cConnectionPoint &cp);
  ~cTestUnit();

  void test1(void);
  void test2(void);

  const char *Name(void) const { return name; }
  void SetUp(void);

private:
  cServerConfig config;
  cConnectionHandler ch;
  const char *name;
  cFilesystemScanner *scanner;
};

cTestUnit::cTestUnit(const char* Name, cConnectionPoint &cp)
 : config(12345)
 , ch(cp, config)
 , name(Name)
 , scanner(NULL)
{
  config.SetAuthorizationRequired(false);
  config.SetDocumentRoot("/media/video");
  config.SetAppIcon("/media/favicon.ico");

  scanner = new cFilesystemScanner();
  if (!scanner) {
     fprintf(stderr, "could not initialize application! (1)");
     exit(-1);
     }
  scanner->SetMediaFactory(new cMediaFactory(config.DocumentRoot()));

  cAbstractMediaRequestHandler::SetFilesystemScanner(scanner);
  cConnectionHandler::RegisterRequestHandler("/cmd", new cCommandHandler());
  cMediaListHandler *listHandler = new cMediaListHandler();

  listHandler->SetListAssembler("json", new cJSonListAssembler());
  listHandler->SetDefaultListAssembler(new cHTMLListAssembler());
  cConnectionHandler::RegisterRequestHandler("/", listHandler);
  cConnectionHandler::RegisterDefaultHandler(new cMediaFileHandler());
}

cTestUnit::~cTestUnit()
{
  cCommandHandler::Cleanup();
  delete scanner;
}

void cTestUnit::SetUp()
{
  if (scanner) scanner->Refresh();
}

void cTestUnit::test1()
{
  std::cout << "ConnectionHandlerTest test 1" << std::endl;

  cHTTPRequest rq(cHTTPRequest::GET, "/");

  rq.SetHeader("Host", "localhost:43567");
  rq.SetHeader("User-Agent", "TestUnit");
  rq.SetHeader("Accept", "image/png,image/*;q=0.8,*/*;q=0.5");
  rq.SetHeader("Accept-Language", "de-de,de;q=0.8,en-us;q=0.5,en;q=0.3");
  rq.SetHeader("Accept-Encoding", "gzip,deflate");
  rq.SetHeader("Accept-Charset", "ISO-8859-1,utf-8;q=0.7,*;q=0.7");
  rq.SetHeader("Keep-Alive", "300");
  rq.SetHeader("Connection", "keep-alive");

  rq.Dump();
  cHTTPResponse *res = ch.ProcessRequest(rq);

  std::cout << "response looks like ..." << std::endl;
  res->Dump();
  delete res;
}

void cTestUnit::test2()
{
  std::cout << "ConnectionHandlerTest test 2" << std::endl;
  std::cout << "%TEST_FAILED% time=0 testname=test2 (ConnectionHandlerTest) message=error message sample" << std::endl;
}

int main(int argc, char** argv)
{
  uint64_t t0 = cTimeMs::Now();
  cConnectionPoint localHost("localhost", 40902);
  cTestUnit unit("ConnectionHandlerTest", localHost);

  unit.SetUp();
  std::cout << "%SUITE_STARTING% " << unit.Name() << std::endl;
  std::cout << "%SUITE_STARTED%" << std::endl;

  std::cout << "%TEST_STARTED% test1 (" << unit.Name() << ")" << std::endl;
  uint64_t start = cTimeMs::Now();
  unit.test1();
  uint64_t end = cTimeMs::Now();
  std::cout << "%TEST_FINISHED% time=" << (double)(end - start) / 1000 << " test1 (" << unit.Name() << ")" << std::endl;

  std::cout << "%TEST_STARTED% test2 (" << unit.Name() << ")\n" << std::endl;
  start = cTimeMs::Now();
  unit.test2();
  end = cTimeMs::Now();
  std::cout << "%TEST_FINISHED% time=" << (double)(end - start) / 1000 << " test2 (" << unit.Name() << ")" << std::endl;

  std::cout << "%SUITE_FINISHED% time=" << (double)(cTimeMs::Now() - t0) / 1000 << std::endl;

  return (EXIT_SUCCESS);
}


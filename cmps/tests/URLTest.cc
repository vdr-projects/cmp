/**
 * ======================== legal notice ======================
 * 
 * File:      URLTest.cc
 * Created:   04.07.2012, 09:25:57
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
#include <Url.h>
#include <Codec.h>
#include <stdlib.h>
//#include <string>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <tr1/unordered_map>

void test1()
{
  std::cout << "URLTest test 1" << std::endl;
  cUrl url("/blah/fasel.html");

  url.AddParameter("Übergewicht", "ja&nein");
  url.AddParameter("test");
  url.AddParameter("mir ist", "(ü)bel");
  url.AddParameter("Ahnung", "keine < nennenswert");
  url.AddParameter("sonst", "fällt mir =nix= \"mehr\" ein");
  char *p = url.ToString();

  url.Dump();
  std::cout << std::endl << "url0 is [" << p << "]" << std::endl;
  std::cout << "path....: " << url.Path() << std::endl << std::endl;

  cUrl revURL(p);

  revURL.Dump();
  char *p1 = revURL.ToString();

  std::cout << "url0 is [" << p << "]" << std::endl;
  std::cout << "path....: " << url.Path() << std::endl;
  std::cout << std::endl;
  std::cout << "url1 is [" << p1 << "]" << std::endl;
  std::cout << "path....: " << revURL.Path() << std::endl;

  if (strcmp(p, p1))
      std::cout << "%TEST_FAILED% time=0 testname=test1 (URLTest) message=initial url and reverse url did not match." << std::endl;

  free(p1);
  free(p);
  cUrl::CleanUp();
}

void test2()
{
  std::cout << "URLTest test 2" << std::endl;
  std::tr1::unordered_map<std::string, std::string>     pool;

  pool["blah"] = "fasel";
  pool["blub"] = "oups";
  pool["nase"] = "wasser";

  std::string res = pool["fasel"];

  if (res.empty())
    std::cout << "lookup of not existing key returned empty string" << std::endl;
  std::cout << "nase ist " << pool["nase"] << std::endl;
  std::cout << "fasel ist " << res << std::endl;

//  std::cout << "%TEST_FAILED% time=0 testname=test2 (URLTest) message=error message sample" << std::endl;
}

int main(int argc, char** argv)
{
  std::cout << "%SUITE_STARTING% URLTest" << std::endl;
  std::cout << "%SUITE_STARTED%" << std::endl;

  std::cout << "%TEST_STARTED% test1 (URLTest)" << std::endl;
  test1();
  std::cout << "%TEST_FINISHED% time=0 test1 (URLTest)" << std::endl;

  std::cout << "%TEST_STARTED% test2 (URLTest)\n" << std::endl;
  test2();
  std::cout << "%TEST_FINISHED% time=0 test2 (URLTest)" << std::endl;

  std::cout << "%SUITE_FINISHED% time=0" << std::endl;

  return (EXIT_SUCCESS);
}


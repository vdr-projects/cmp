/**
 * ======================== legal notice ======================
 * 
 * File:      UTF8Test.cc
 * Created:   05.07.2012, 15:19:07
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
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

static const char *testFile = "/usr/local/share/UTF8.Sample";

void test1()
{
  char buf[128];
  char *start, *end, *check0, *check1;
  FILE *fp;
  int bytesRead, bytes2Read, rest, i;

  std::cout << "UTF8Test test 1" << std::endl;

  if (fp = fopen(testFile, "r")) {
     check0 = buf;
     check1 = buf + sizeof(buf);
     start = buf;
     bytes2Read = sizeof(buf);
     while (bytesRead = fread(start, sizeof(char), bytes2Read, fp)) {
           start = buf;
           while (start && start < (buf + sizeof(buf))) {
                 end = strchr(start, '\n');
                 if (!end) {
                    if (start > buf) {
                       rest = buf + sizeof(buf) - start;

                       for (i=0; i < rest; ++i) {
                           buf[i] = start[i];
                           }
                       start = buf + rest;
                       bytes2Read = sizeof(buf) - rest;
                       break;
                       }
                    else break;
                    }
                 *end = 0;
                 printf("line looks like: >%s<\n", start);
                 start = end + 1;
                 }
           }
     fclose(fp);
     }
  else std::cout << "%TEST_FAILED% time=0 testname=test1 (UTF8Test) message=could not open file" << std::endl;
}

void test2()
{
  std::cout << "UTF8Test test 2" << std::endl;
  std::cout << "%TEST_FAILED% time=0 testname=test2 (UTF8Test) message=error message sample" << std::endl;
}

int main(int argc, char** argv)
{
  std::cout << "%SUITE_STARTING% UTF8Test" << std::endl;
  std::cout << "%SUITE_STARTED%" << std::endl;

  std::cout << "%TEST_STARTED% test1 (UTF8Test)" << std::endl;
  test1();
  std::cout << "%TEST_FINISHED% time=0 test1 (UTF8Test)" << std::endl;

  std::cout << "%TEST_STARTED% test2 (UTF8Test)\n" << std::endl;
  test2();
  std::cout << "%TEST_FINISHED% time=0 test2 (UTF8Test)" << std::endl;

  std::cout << "%SUITE_FINISHED% time=0" << std::endl;

  return (EXIT_SUCCESS);
}


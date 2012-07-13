/**
 * ======================== legal notice ======================
 * 
 * File:      DirTest.cc
 * Created:   02.07.2012, 18:07:18
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
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>

/*
 * Simple C++ Test Suite
 */

void test1()
{
  struct direct *dirEntry;
  DIR *dir = opendir("/media");

  std::cout << "DirTest test 1" << std::endl;
  if (!dir)
     std::cout << "%TEST_FAILED% time=0 testname=test1 (DirTest) message=failed to open directory" << std::endl;

  while ((dirEntry = readdir(dir))) {
        if (*dirEntry->d_name == '.') continue;
        std::cout << "dir-entry: " << dirEntry->d_name << std::endl;
        }
  closedir(dir);
}

void test2()
{
  std::cout << "DirTest test 2" << std::endl;
  std::cout << "%TEST_FAILED% time=0 testname=test2 (DirTest) message=error message sample" << std::endl;
}

int main(int argc, char** argv)
{
  std::cout << "%SUITE_STARTING% DirTest" << std::endl;
  std::cout << "%SUITE_STARTED%" << std::endl;

  std::cout << "%TEST_STARTED% test1 (DirTest)" << std::endl;
  test1();
  std::cout << "%TEST_FINISHED% time=0 test1 (DirTest)" << std::endl;

  std::cout << "%TEST_STARTED% test2 (DirTest)\n" << std::endl;
  test2();
  std::cout << "%TEST_FINISHED% time=0 test2 (DirTest)" << std::endl;

  std::cout << "%SUITE_FINISHED% time=0" << std::endl;

  return (EXIT_SUCCESS);
}


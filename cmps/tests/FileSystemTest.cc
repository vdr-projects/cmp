/**
 * ======================== legal notice ======================
 * 
 * File:      FileSystemTest.cc
 * Created:   21.07.2012, 12:40:48
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
#include <FileSystem.h>
#include <File.h>

/*
 * Simple C++ Test Suite
 */

void test1()
{
  std::cout << "FileSystemTest test 1" << std::endl;
  cFile *f = new cFile("/media/xchange/");

  std::cout << "got file: " << f->AbsolutePath() << std::endl;

  cFile *other = f->Parent();

  std::cout << "parent is file: " << other->AbsolutePath() << std::endl;

  cFile *newOne = new cFile(*other, "/video/test/blah");

  std::cout << "assembled file: " << newOne->AbsolutePath() << std::endl;

  delete newOne;
  delete other;
  delete f;
}

void test2()
{
  std::cout << "FileSystemTest test 2" << std::endl;
  std::cout << "%TEST_FAILED% time=0 testname=test2 (FileSystemTest) message=error message sample" << std::endl;
}

int main(int argc, char** argv)
{
  std::cout << "%SUITE_STARTING% FileSystemTest" << std::endl;
  std::cout << "%SUITE_STARTED%" << std::endl;

  std::cout << "%TEST_STARTED% test1 (FileSystemTest)" << std::endl;
  test1();
  std::cout << "%TEST_FINISHED% time=0 test1 (FileSystemTest)" << std::endl;

  std::cout << "%TEST_STARTED% test2 (FileSystemTest)\n" << std::endl;
  test2();
  std::cout << "%TEST_FINISHED% time=0 test2 (FileSystemTest)" << std::endl;

  std::cout << "%SUITE_FINISHED% time=0" << std::endl;

  return (EXIT_SUCCESS);
}


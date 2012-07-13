/**
 * ======================== legal notice ======================
 * 
 * File:      CodecTest.cc
 * Created:   09.07.2012, 05:44:50
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
#include <Codec.h>
#include <stdlib.h>
#include <iostream>

static const char *TT[] = {
  "130-H Karadayi featuring Fresh B. - Betüll Demir - Na Nay (2009).mp3"
, " 36 130 - R.I.O. ft Jerry Ropero vs. Mendonca - Do Rio-De Janeiro Berinbau (Bootleg Edit).mp3"
, "Das_Vermächtnis_der_Tempelritter (2012-07-02.22.10.36-0.rec)"
, NULL
, "http://localhost:12345/test/Mukke/130-H%20Karadayi%20featuring%20Fresh%20B.%20-%20Bet%C3%BCll%20Demir%20-%20Na%20Nay%20(2009).mp3"
, "http://localhost:12345/test/Mukke/36%20%20%20130%20-%20R.I.O.%20ft%20Jerry%20Ropero%20vs.%20Mendonca%20-%20Do%20Rio-De%20Janeiro%20Berinbau%20(Bootleg%20Edit).mp3"
, "http://localhost:12345/import/Das_Verm%C3%A4chtnis_der_Tempelritter/2012-07-02.22.10.36-0.rec"
, NULL
};

void test1()
{
  std::cout << "CodecTest test 1" << std::endl;
  cURLEncoder *ue = new cURLEncoder();
  const char **p;
  char *newText;

  for (p = TT; p && *p; ++p) {
      newText = ue->Encode(*p);
      std::cout << "original: " << *p << std::endl;
      std::cout << "encoded.: " << newText << std::endl << std::endl;
      }
}

void test2()
{
  std::cout << "CodecTest test 2" << std::endl;
  std::cout << "%TEST_FAILED% time=0 testname=test2 (CodecTest) message=error message sample" << std::endl;
}

int main(int argc, char** argv)
{
  std::cout << "%SUITE_STARTING% CodecTest" << std::endl;
  std::cout << "%SUITE_STARTED%" << std::endl;

  std::cout << "%TEST_STARTED% test1 (CodecTest)" << std::endl;
  test1();
  std::cout << "%TEST_FINISHED% time=0 test1 (CodecTest)" << std::endl;

//  std::cout << "%TEST_STARTED% test2 (CodecTest)\n" << std::endl;
//  test2();
//  std::cout << "%TEST_FINISHED% time=0 test2 (CodecTest)" << std::endl;

  std::cout << "%SUITE_FINISHED% time=0" << std::endl;

  return (EXIT_SUCCESS);
}


/**
 * ======================== legal notice ======================
 * 
 * File:      StringBuilderTest.cc
 * Created:   06.07.2012, 18:28:08
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
#include <StringBuilder.h>

/*
 * Simple C++ Test Suite
 */

void test1()
{
  cStringBuilder sb(16);
  char buf[256] = {0};
  int blah = 0;

  std::cout << "StringBuilderTest test 1" << std::endl;

  sb.Append("Alle ma herhören!\n").Append("Jetzt jibbet wat uff de Ohren!\n");
  sb.Append("Ausgewählt: ").Append(true, "Ja", "Nein").Append("\n");
  sb.Append("Dezimal: ").Append(3.1478910).Append("\n");
  sb.Append("Integer: ").Append(127).Append("\n");
  sb.Append("große Zahl: ").Append(98765432123456789l).Append("\n");

  std::cout << "size of StringBuilder: " << sb.Size() << " bytes" << std::endl;
  size_t bytesWritten = sb.Copy(buf, sizeof(buf));

  if (bytesWritten != sb.Size())
     std::cout << "%TEST_FAILED% time=0 testname=test1 (StringBuilderTest) message=length after copy differ." << std::endl;
  else std::cout << "OK" << std::endl << "=====================" << std::endl << buf << "===================" << std::endl;
}

void test2()
{
  cStringBuilder sb;
  char buf[512] = {0};
  int blah=0;
  std::cout << "StringBuilderTest test 2" << std::endl;
//  std::cout << "%TEST_FAILED% time=0 testname=test2 (StringBuilderTest) message=error message sample" << std::endl;

  sb.Append("Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore "
            "et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. "
            "Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit "
            "amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna "
            "aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd "
            "gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur "
            "sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam "
            "voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea "
            "takimata sanctus est Lorem ipsum dolor sit amet. ");
  sb.Append("На берегу пустынных волн\n").Append("Стоял он, дум великих полн,\n");
  sb.Append("И вдаль глядел. Пред ним широко\n").Append("Река неслася; бедный чёлн\n");
  sb.Append("По ней стремился одиноко.\n").Append("По мшистым, топким берегам\n");
  sb.Append("Чернели избы здесь и там,\n").Append("Приют убогого чухонца;\n");
  sb.Append("И лес, неведомый лучам\n").Append("В тумане спрятанного солнца,\n");
  sb.Append("Кругом шумел.\n");
  sb.Append("Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore "
            "eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum "
            "zzril delenit augue duis dolore te feugait nulla facilisi. Lorem ipsum dolor sit amet, consectetuer "
            "adipiscing elit, sed diam nonummy nibh euismod tincidunt ut laoreet dolore magna aliquam erat volutpat. ");
  sb.Append("Ut wisi enim ad minim veniam, quis nostrud exerci tation ullamcorper suscipit lobortis nisl ut aliquip ex "
            "ea commodo consequat. Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie "
            "consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim "
            "qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi. ");
  sb.Append("Nam liber tempor cum soluta nobis eleifend option congue nihil imperdiet doming id quod mazim placerat "
            "facer possim assum. Lorem ipsum dolor sit amet, consectetuer adipiscing elit, sed diam nonummy nibh "
            "euismod tincidunt ut laoreet dolore magna aliquam erat volutpat. Ut wisi enim ad minim veniam, quis "
            "nostrud exerci tation ullamcorper suscipit lobortis nisl ut aliquip ex ea commodo consequat. ");
  sb.Append("Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore "
            "eu feugiat nulla facilisis. ");

  std::cout << "size of StringBuilder: " << sb.Size() << " bytes" << std::endl;
  size_t bytesWritten = 0;
  int chunkWritten = 0;

  while ((chunkWritten = sb.Copy(buf, sizeof(buf))) > 0) {
        bytesWritten += chunkWritten;
        std::cout << "==========================================" << std::endl << buf;
        std::cout << "==========================================" << std::endl;
        }
  if (bytesWritten != sb.Size())
     std::cout << "%TEST_FAILED% time=0 testname=test2 (StringBuilderTest) message=size mismatch after write" << std::endl;
  else std::cout << "OK" << std::endl;
}

int main(int argc, char** argv)
{
  std::cout << "%SUITE_STARTING% StringBuilderTest" << std::endl;
  std::cout << "%SUITE_STARTED%" << std::endl;

  std::cout << "%TEST_STARTED% test1 (StringBuilderTest)" << std::endl;
  test1();
  std::cout << "%TEST_FINISHED% time=0 test1 (StringBuilderTest)" << std::endl;

  std::cout << "%TEST_STARTED% test2 (StringBuilderTest)\n" << std::endl;
  test2();
  std::cout << "%TEST_FINISHED% time=0 test2 (StringBuilderTest)" << std::endl;

  std::cout << "%SUITE_FINISHED% time=0" << std::endl;

  return (EXIT_SUCCESS);
}


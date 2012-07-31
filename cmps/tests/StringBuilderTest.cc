/**
 * ======================== legal notice ======================
 * 
 * File:      StringBuilderTest.cc
 * Created:   06.07.2012, 18
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
#include <StringBuilder.h>
#include <FileReader.h>
#include <LineReader.h>
#include <File.h>
#include <string.h>
#include <iostream>

#define NEW_LINE '\n'

void rangeTests()
{                           // 12345678901
  static const char *sample = "Hello World";
  cStringBuilder *sb;
  int chunkSize = strlen(sample) - 4;
  char *result;

  std::cout << sample << " has length: " << strlen(sample) << std::endl;

  for (int i=0; i < 6; ++i) {
      std::cout << "check chunkSize of " << chunkSize + i << std::endl;
      sb = new cStringBuilder(chunkSize + i);

      sb->Append(sample).Append(NEW_LINE);
      result = sb->toString();

      std::cout << "assembled text looks like: " << std::endl << result;
      free(result);
      delete sb;
      }
}

void basicTests()
{
  cStringBuilder sb(179);

  sb.Append("hello World").Append(NEW_LINE);
  sb.Append("logical default true: ").Append(true).Append(NEW_LINE);
  sb.Append("logical default false: ").Append(false).Append(NEW_LINE);
  sb.Append("logical true value: ").Append(true, "true", "false").Append(NEW_LINE);
  sb.Append("logical false value: ").Append(false, "true", "false").Append(NEW_LINE);
  sb.Append("double: ").Append(3.1456789).Append(NEW_LINE);
  sb.Append("unsigned long: ").Append((size_t) 91237485l).Append(NEW_LINE);
  sb.Append("long: ").Append(1234567890l).Append(NEW_LINE);
  sb.Append("int: ").Append(512).Append(NEW_LINE);

  char *result = sb.toString();

  std::cout << "sizeof assembled text: " << sb.Size() << std::endl;
  std::cout << "assembled text looks like:" << std::endl << result;

  free(result);
}

void lineReaderTest()
{
  cLineReader lr(new cFileReader(new cFile("srclient.conf")));
  const char *line = NULL;

  while ((line = lr.ReadLine())) {
        std::cout << "line: " << line << std::endl;
        }
  lr.Close();
  cFile::Cleanup();
}

int main()
{
  lineReaderTest();
  basicTests();
  rangeTests();

  return 0;
}

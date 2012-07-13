/*
 * File:   JSonTest.cc
 * Author: django
 *
 * Created on 12.07.2012, 07:31:46
 */

#include <StringBuilder.h>
#include <JSonWriter.h>
#include <stdlib.h>
#include <iostream>

/*
 * Simple C++ Test Suite
 */

void test1()
{
  char buf[512] = {0};
  cStringBuilder sb;
  cJSonWriter jw(sb);

  std::cout << "JSonTest test 1" << std::endl;

  jw.Object().Key("total").Value(123);
  jw.Key("errorCode").Value(-1);
  jw.Key("testmode").Value(true);
  jw.Key("results").Array();

  for (int i=0; i < 3; ++i) {
    jw.Object().Key("counter").Value(i);
    jw.Key("nase").Value("bär");
    jw.EndObject();
  }
  jw.EndArray();
  jw.Key("fasel").Value("blub");
  jw.EndObject();

  std::cout << "size of json-Object: " << sb.Size() << std::endl;
  sb.Copy(buf, sizeof(buf));

  std::cout << "json object looks like" << std::endl << buf << std::endl;
}

void test2()
{
  std::cout << "JSonTest test 2" << std::endl;
  std::cout << "%TEST_FAILED% time=0 testname=test2 (JSonTest) message=error message sample" << std::endl;
}

int main(int argc, char** argv)
{
  std::cout << "%SUITE_STARTING% JSonTest" << std::endl;
  std::cout << "%SUITE_STARTED%" << std::endl;

  std::cout << "%TEST_STARTED% test1 (JSonTest)" << std::endl;
  test1();
  std::cout << "%TEST_FINISHED% time=0 test1 (JSonTest)" << std::endl;

//  std::cout << "%TEST_STARTED% test2 (JSonTest)\n" << std::endl;
//  test2();
//  std::cout << "%TEST_FINISHED% time=0 test2 (JSonTest)" << std::endl;

  std::cout << "%SUITE_FINISHED% time=0" << std::endl;

  return (EXIT_SUCCESS);
}


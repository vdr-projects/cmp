/**
 * ======================== legal notice ======================
 * 
 * File:      CredentialPersistence.cc
 * Created:   03.07.2012, 14:16:35
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
#include <Principal.h>
#include <Credentials.h>
#include <stdlib.h>
#include <iostream>

/*
 * Simple C++ Test Suite
 */
static void setupTestCredentials() {
  Credentials.SetApplicationRealm("supportedUsers@myTestApp");
  cPrincipal *p = new cPrincipal("Nasenbär", Credentials.ApplicationRealm());

  p->CreateHash("Nasenwasser");
  Credentials.Put(p->Name(), p);

  p = new cPrincipal("Admin", Credentials.ApplicationRealm());
  p->CreateHash("very secret");
  Credentials.Put(p->Name(), p);

  p = new cPrincipal("Sepp", Credentials.ApplicationRealm());
  p->CreateHash("keine Ahnung");
  Credentials.Put(p->Name(), p);
}

static void dumpCredentials() {
  cCredentials::const_iterator principals = Credentials.begin();

  while (principals != Credentials.end()) {
        principals->second->Dump();
        ++principals;
        }

}

void test1()
{
  setupTestCredentials();
  std::cout << "CredentialPersistence test 1" << std::endl;

  int rv = Credentials.Store("/tmp/testCredentials.x9");

  if (!rv) std::cout << "%TEST_FAILED% time=0 testname=test1 (CredentialPersistence) message=failed to write credentials" << std::endl;
  else std::cout << "saved " << rv << " principals." << std::endl;

  dumpCredentials();
}

void test2()
{
  std::cout << "CredentialPersistence test 2" << std::endl;

  Credentials.Clear();

  int rv = Credentials.Load("/tmp/testCredentials.x9");

  if (!rv) std::cout << "%TEST_FAILED% time=0 testname=test2 (CredentialPersistence) message=failed to load credentials" << std::endl;
  else std::cout << "loaded " << rv << " principals." << std::endl;

  dumpCredentials();
}

int main(int argc, char** argv)
{
  std::cout << "%SUITE_STARTING% CredentialPersistence" << std::endl;
  std::cout << "%SUITE_STARTED%" << std::endl;

  std::cout << "%TEST_STARTED% test1 (CredentialPersistence)" << std::endl;
  test1();
  std::cout << "%TEST_FINISHED% time=0 test1 (CredentialPersistence)" << std::endl;

  std::cout << "%TEST_STARTED% test2 (CredentialPersistence)\n" << std::endl;
  test2();
  std::cout << "%TEST_FINISHED% time=0 test2 (CredentialPersistence)" << std::endl;

  std::cout << "%SUITE_FINISHED% time=0" << std::endl;

  return (EXIT_SUCCESS);
}


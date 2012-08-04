/**
 * ======================== legal notice ======================
 * 
 * File:      HTTPServer.cc
 * Created:   4. Juli 2012, 12
 * Author:    <a href="mailto:geronimo013@gmx.de">Geronimo</a>
 * Project:   libnetworking: classes for tcp/ip sockets and http-protocol handling
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
#include <HTTPServer.h>
#include <HTTPResponse.h>
#include <ConnectionHandler.h>
#include <CondWait.h>
#include <Mutex.h>
#include <Logging.h>
#include <util.h>
#include <stdio.h>

static volatile bool running = true;
cHTTPServer::cHTTPServer(cServerConfig &Config)
 : config(Config)
#ifdef LIVE_CLEANUP
 , cleaner(NULL)
#endif
{
  threads = new std::vector<cThread *>();
#ifdef LIVE_CLEANUP
  cleaner = new cThread(cleanerThread, NULL, "cleanup thread stubs");
#endif
}

cHTTPServer::~cHTTPServer()
{
#ifdef LIVE_CLEANUP
  cleaner->Cancel(0);
  delete cleaner;
#else
  Cleanup();
#endif
  delete threads;
}

void cHTTPServer::Action()
{
#ifdef LIVE_CLEANUP
  if (cleaner) {
     fprintf(stderr, "check size of thread pool ...\n");
     if (!threads->empty()) fprintf(stderr, "thread pool has size of %lu\n", threads->size());
     fprintf(stderr, "start cleaner thread\n");
     cleaner->Start();
     }
#endif
  ServerSocket().Open();
  while (Running()) {
        cConnectionPoint *cp = ServerSocket().Accept();

        if (cp) {
           // this has to come after accept, as the hostnames can not be determined before an established connection.
           if (!cHTTPResponse::ServerID()) {
              char *id;

              asprintf(&id, "HTTPServer %s:%d", ServerSocket().ThisSide()->RealName(), ServerSocket().Port());
              cHTTPResponse::SetServerID(id);
              }
           cConnectionHandler *ch = new cConnectionHandler(*cp, config);

           ch->Start();

#ifdef LIVE_CLEANUP
           cMutexLock poolSync(&poolMutex);
#endif
           threads->push_back(ch);
           }
        }
}

bool cHTTPServer::Running()
{
  return ServerSocket().Active();
}

#ifdef LIVE_CLEANUP
int cHTTPServer::cleanerThread(void *opaque, cThread *ThreadContext)
{
  cHTTPServer *server = (cHTTPServer *)opaque;

  server->Cleanup(ThreadContext);
  return 0;
}

void cHTTPServer::Cleanup(cThread *ThreadContext)
{
  if (!ThreadContext) return;
  cThread *p;

  fprintf(stderr, "cleanup-Thread - gonna start loop ...\n");
  while (ThreadContext->Running()) {
        fprintf(stderr, "check list of possible threads ...\n");
        if (!threads->empty()) {
           fprintf(stderr, "thread pool is not empty ...\n");
           for (size_t i=0; i < threads->size(); ++i) {
               fprintf(stderr, "ok, got first entry to check ...\n");
               p = (*threads)[i];
               if (p->Active()) continue;

               fprintf(stderr, "thread %lu looks dead ...\n", i);
               isyslog("thread %lu is not active, so just clean it up", i);
               p->Cancel();
               delete p;
               cMutexLock poolSync(&poolMutex);
               threads->erase(threads->begin() + i);
               break;
               }
           }
        cCondWait::SleepMs(200);
        }
  ThreadContext->Cancel();
}
#else
void cHTTPServer::Cleanup()
{
  cThread *t;

  for (size_t i=0; i < threads->size(); ++i) {
      t = (*threads)[i];
      t->Cancel();
      delete t;
      }
}
#endif

bool cHTTPServer::Start()
{
  Action();
  return true;
}

void cHTTPServer::Stop()
{
  ServerSocket().SetActive(false);
}
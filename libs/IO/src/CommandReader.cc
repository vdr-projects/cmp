/**
 * ======================== legal notice ======================
 * 
 * File:      CommandReader.cc
 * Created:   30. Juli 2012, 06:42
 * Author:    <a href="mailto:geronimo013@gmx.de">Geronimo</a>
 * Project:   libIO: classes for files, filesystem and input/output
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
#include <CommandReader.h>
#include <Logging.h>
#include <stdarg.h>
#include <errno.h>
#include <wait.h>

int cCommandReader::fdMax = 0;

cCommandReader::cCommandReader(const char *cmd)
 : pid(-1)
{
  args.push_back(cmd);
}

cCommandReader::~cCommandReader()
{
  Close();
}

void cCommandReader::AddCommandParameter(const char* Param)
{
  args.push_back(Param);
}

void cCommandReader::Close(void)
{
  int status = 0;

  if (!fdMax) fdMax = getdtablesize();
  if (fd > 0 && fd < fdMax) close(fd);
  fd = -1;
  if (pid != waitpid(pid, &status, 0))
     esyslog("ERROR: failed to wait for child #%d - error #%d", pid, errno);
  pid = -1;
}

bool cCommandReader::Open(void)
{
  enum { FDRead, FDWrite };
  int child2Parent[2] = {0};

  if (pipe(child2Parent)) {
     esyslog("ERROR: failed to create child2Parent-pipe #%d", errno);
     return false;
     }
  switch ((pid = fork())) {
    case -1:
         esyslog("fork failed");
         close(child2Parent[0]);
         close(child2Parent[1]);
         return false;

    case 0: { /* child */
         const char *cmdArgs[args.size() + 1];

         for (size_t i=0; i < args.size(); ++i) {
             cmdArgs[i] = args[i].c_str();
             }
         cmdArgs[args.size()] = 0;
         if (dup2(child2Parent[FDWrite], STDOUT_FILENO) < 0) {
            esyslog("ERROR: failed to create childs stdout #%d", errno);
            exit(-1);
            }
         if (dup2(child2Parent[FDWrite], STDERR_FILENO) < 0) {
            esyslog("ERROR: failed to create childs stderr #%d", errno);
            exit(-1);
            }
         if (close(child2Parent[FDRead])) {
            esyslog("ERROR: failed to close childs read-end of the pipe #%d", errno);
            exit(-1);
            }
         execv(args[0].c_str(), (char *const*) cmdArgs);
         esyslog("should never be reached! #1");
         exit(-1);
         } break;

    default: { /* parent */
         if (close(child2Parent[FDWrite])) {
            esyslog("ERROR: failed to close write end from parent side!");
            exit(-1);
            }
         fd = child2Parent[FDRead];
         return true;
         }
  }
  esyslog("should never be reached! #2");
  close(child2Parent[0]);
  close(child2Parent[1]);
  return false;
}

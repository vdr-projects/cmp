/**
 * File:      Thread.cc
 * Project:   libvdr - classes taken from vdr-project
 * 
 * from "Video Disk Recorder":
 * 
 * Copyright (C) 2000, 2003, 2006, 2008 Klaus Schmidinger
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 * Or, point your browser to http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * 
 * The original author can be reached at kls@tvdr.de
 * 
 * The vdr project's page is at http://www.tvdr.de
 * 
 */
#include <Thread.h>
#include <TimeMs.h>
#include <CondWait.h>
#include <Logging.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/resource.h>
tThreadId cThread::mainThreadId = 0;

cThread::cThread(const char *Description)
 : active(false)
 , running(false)
 , childTid(0)
 , childThreadId(0)
 , description(NULL)
 , threadCallback(NULL)
 , opaque(NULL)
{
  if (Description) SetDescription("%s", Description);
}

cThread::cThread(int (*ThreadCallback)(void *, cThread *), void *Opaque, const char *Description)
 : active(false)
 , running(false)
 , childTid(0)
 , childThreadId(0)
 , description(NULL)
 , threadCallback(ThreadCallback)
 , opaque(Opaque)
{
  if (Description) SetDescription("%s", Description);
}

cThread::~cThread()
{
  Cancel(); // just in case the derived class didn't call it
  free(description);
}

void cThread::SetPriority(int Priority)
{
  if (setpriority(PRIO_PROCESS, 0, Priority) < 0)
     LOG_ERROR;
}

void cThread::SetIOPriority(int Priority)
{
  if (syscall(SYS_ioprio_set, 1, 0, (Priority & 0xff) | (2 << 13)) < 0) // best effort class
     LOG_ERROR;
}

void cThread::SetDescription(const char *Description, ...)
{
  free(description);
  description = NULL;
  if (Description) {
     va_list ap;
     va_start(ap, Description);
     vasprintf(&description, Description, ap);
     va_end(ap);
     }
}

void *cThread::StartThread(cThread *Thread)
{
  Thread->childThreadId = ThreadId();
  if (Thread->description) {
     dsyslog("%s thread started (pid=%d, tid=%d)", Thread->description, getpid(), Thread->childThreadId);
#ifdef PR_SET_NAME
     if (prctl(PR_SET_NAME, Thread->description, 0, 0, 0) < 0)
        esyslog("%s thread naming failed (pid=%d, tid=%d)", Thread->description, getpid(), Thread->childThreadId);
#endif
     }
  Thread->Action();
  if (Thread->description)
     dsyslog("%s thread ended (pid=%d, tid=%d)", Thread->description, getpid(), Thread->childThreadId);
  Thread->running = false;
  Thread->active = false;

  return NULL;
}

#define THREAD_STOP_TIMEOUT  3000 // ms to wait for a thread to stop before newly starting it
#define THREAD_STOP_SLEEP      30 // ms to sleep while waiting for a thread to stop

bool cThread::Start(void)
{
  if (!running) {
     if (active) {
        // Wait until the previous incarnation of this thread has completely ended
        // before starting it newly:
        cTimeMs RestartTimeout;
        while (!running && active && RestartTimeout.Elapsed() < THREAD_STOP_TIMEOUT)
              cCondWait::SleepMs(THREAD_STOP_SLEEP);
        }
     if (!active) {
        active = running = true;
        if (pthread_create(&childTid, NULL, (void *(*) (void *))&StartThread, (void *)this) == 0) {
           pthread_detach(childTid); // auto-reap
           }
        else {
           LOG_ERROR;
           active = running = false;
           return false;
           }
        }
     }
  return true;
}

void cThread::Action()
{
  if (!threadCallback) *((char *)0) = 0;
  ///< if not used the callback constructor, cThread must be subclassed, so stop application here!

  threadCallback(opaque, this); // passing this as parameter allows the callback
                                // use the public interface of this instance.
}

bool cThread::Active(void)
{
  if (active) {
     //
     // Single UNIX Spec v2 says:
     //
     // The pthread_kill() function is used to request
     // that a signal be delivered to the specified thread.
     //
     // As in kill(), if sig is zero, error checking is
     // performed but no signal is actually sent.
     //
     int err;
     if ((err = pthread_kill(childTid, 0)) != 0) {
        if (err != ESRCH)
           LOG_ERROR;
        childTid = 0;
        active = running = false;
        }
     else
        return true;
     }
  return false;
}

void cThread::Cancel(int WaitSeconds)
{
  running = false;
  if (active && WaitSeconds > -1) {
     if (WaitSeconds > 0) {
        for (time_t t0 = time(NULL) + WaitSeconds; time(NULL) < t0; ) {
            if (!Active())
               return;
            cCondWait::SleepMs(10);
            }
        esyslog("ERROR: %s thread %d won't end (waited %d seconds) - canceling it...", description ? description : "", childThreadId, WaitSeconds);
        }
     pthread_cancel(childTid);
     childTid = 0;
     active = false;
     }
}

tThreadId cThread::ThreadId(void)
{
  return syscall(__NR_gettid);
}

void cThread::SetMainThreadId(void)
{
  if (mainThreadId == 0)
     mainThreadId = ThreadId();
  else
     esyslog("ERROR: attempt to set main thread id to %d while it already is %d", ThreadId(), mainThreadId);
}

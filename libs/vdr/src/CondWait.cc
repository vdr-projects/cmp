/**
 * File:      CondWait.cc
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
#include <CondWait.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/prctl.h>
#include <errno.h>
#include <tools.h>

static bool GetAbsTime(struct timespec *Abstime, int MillisecondsFromNow)
{
  struct timeval now;
  if (gettimeofday(&now, NULL) == 0) {           // get current time
     now.tv_sec  += MillisecondsFromNow / 1000;  // add full seconds
     now.tv_usec += (MillisecondsFromNow % 1000) * 1000;  // add microseconds
     if (now.tv_usec >= 1000000) {               // take care of an overflow
        now.tv_sec++;
        now.tv_usec -= 1000000;
        }
     Abstime->tv_sec = now.tv_sec;          // seconds
     Abstime->tv_nsec = now.tv_usec * 1000; // nano seconds
     return true;
     }
  return false;
}

cCondWait::cCondWait(void)
{
  signaled = false;
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond, NULL);
}

cCondWait::~cCondWait()
{
  pthread_cond_broadcast(&cond); // wake up any sleepers
  pthread_cond_destroy(&cond);
  pthread_mutex_destroy(&mutex);
}

void cCondWait::SleepMs(int TimeoutMs)
{
  cCondWait w;
  w.Wait(max(TimeoutMs, 3)); // making sure the time is >2ms to avoid a possible busy wait
}

bool cCondWait::Wait(int TimeoutMs)
{
  pthread_mutex_lock(&mutex);
  if (!signaled) {
     if (TimeoutMs) {
        struct timespec abstime;
        if (GetAbsTime(&abstime, TimeoutMs)) {
           while (!signaled) {
                 if (pthread_cond_timedwait(&cond, &mutex, &abstime) == ETIMEDOUT)
                    break;
                 }
           }
        }
     else
        pthread_cond_wait(&cond, &mutex);
     }
  bool r = signaled;
  signaled = false;
  pthread_mutex_unlock(&mutex);
  return r;
}

void cCondWait::Signal(void)
{
  pthread_mutex_lock(&mutex);
  signaled = true;
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&mutex);
}

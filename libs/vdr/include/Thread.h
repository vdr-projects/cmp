/**
 * File:      Thread.h
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
 * ++2012-07-04(rma):
 * As I don't like the necessity to subclass what should work in a thread,
 * I extended the original sources, so that an arbitrary function can be
 * a thread kernel.
 */
#ifndef THREAD_H
#define	THREAD_H

#include <Mutex.h>
#include <stddef.h>
#include <pthread.h>
typedef pid_t tThreadId;

class cThread {
public:
  cThread(const char *Description = NULL);
       ///< Creates a new thread.
       ///< If Description is present, a log file entry will be made when
       ///< the thread starts and stops. The Start() function must be called
       ///< to actually start the thread.
  cThread(int (*ThreadCallback)(void *opaque, cThread *instance), void *opaque, const char *Description = NULL);
  virtual ~cThread();

  void SetDescription(const char *Description, ...) __attribute__ ((format (printf, 2, 3)));
  bool Start(void);
       ///< Actually starts the thread.
       ///< If the thread is already running, nothing happens.
  virtual void Cancel(int WaitSeconds = 0);
       ///< Cancels the thread by first setting 'running' to false, so that
       ///< the Action() loop can finish in an orderly fashion and then waiting
       ///< up to WaitSeconds seconds for the thread to actually end. If the
       ///< thread doesn't end by itself, it is killed.
       ///< If WaitSeconds is -1, only 'running' is set to false and Cancel()
       ///< returns immediately, without killing the thread.
  bool Active(void);
       ///< used from outside to check whether the thread is still alive.
  bool Running(void) { return running; }
       ///< used from inside the thread to check whether it may keep on running.
       ///< Returns false if a derived cThread object shall leave its Action()
       ///< function. Should be public and so available for callback thread kernels

  static tThreadId ThreadId(void);
  static tThreadId IsMainThread(void) { return ThreadId() == mainThreadId; }
  static void SetMainThreadId(void);

protected:
  void SetPriority(int Priority);
  void SetIOPriority(int Priority);
  void Lock(void) { mutex.Lock(); }
  void Unlock(void) { mutex.Unlock(); }
  virtual void Action(void);
       ///< A derived cThread class must implement the code it wants to
       ///< execute as a separate thread in this function. If this is
       ///< a loop, it must check Running() repeatedly to see whether
       ///< it's time to stop.
       ///< To support callbacks as thread kernels, default implementation now
       ///< starts the callback

private:
  bool active;
  bool running;
  pthread_t childTid;
  tThreadId childThreadId;
  cMutex mutex;
  char *description;
  int (*threadCallback)(void *, cThread *);
  void *opaque;
  static tThreadId mainThreadId;
  static void *StartThread(cThread *Thread);
  friend class cThreadLock;
  };

#endif	/* THREAD_H */


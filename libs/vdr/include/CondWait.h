/**
 * File:      CondWait.h
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
#ifndef CONDWAIT_H
#define	CONDWAIT_H

#include <pthread.h>

class cCondWait {
public:
  cCondWait(void);
  ~cCondWait();
  
  bool Wait(int TimeoutMs = 0);
       ///< Waits at most TimeoutMs milliseconds for a call to Signal(), or
       ///< forever if TimeoutMs is 0.
       ///< \return Returns true if Signal() has been called, false it the given
       ///< timeout has expired.
  void Signal(void);
       ///< Signals a caller of Wait() that the condition it is waiting for is met.

  static void SleepMs(int TimeoutMs);
       ///< Creates a cCondWait object and uses it to sleep for TimeoutMs
       ///< milliseconds, immediately giving up the calling thread's time
       ///< slice and thus avoiding a "busy wait".
       ///< In order to avoid a possible busy wait, TimeoutMs will be automatically
       ///< limited to values >2.

private:
  pthread_mutex_t mutex;
  pthread_cond_t cond;
  bool signaled;
  };

#endif	/* CONDWAIT_H */


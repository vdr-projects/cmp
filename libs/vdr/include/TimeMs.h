/**
 * File:      TimeMs.h
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
#ifndef TIMEMS_H
#define	TIMEMS_H

#include <inttypes.h>

class cTimeMs {
public:
  cTimeMs(int Ms = 0);
       ///< Creates a timer with ms resolution and an initial timeout of Ms.
       ///< If Ms is negative the timer is not initialized with the current
       ///< time.
  void Set(int Ms = 0);
  bool TimedOut(void);
  uint64_t Elapsed(void);
  static uint64_t Now(void);

private:
  uint64_t begin;
  };

#endif	/* TIMEMS_H */


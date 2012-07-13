/**
 * File:      tools.h
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
#ifndef TOOLS_H
#define	TOOLS_H

#include <stddef.h>

#define MALLOC(type, size)  (type *)malloc(sizeof(type) * (size))

template<class T> inline void DELETENULL(T *&p) { T *q = p; p = NULL; delete q; }

#define CHECK(s) { if ((s) < 0) LOG_ERROR; } // used for 'ioctl()' calls
#define FATALERRNO (errno && errno != EAGAIN && errno != EINTR)

#ifndef __STL_CONFIG_H // in case some plugin needs to use the STL
template<class T> inline T min(T a, T b) { return a <= b ? a : b; }
template<class T> inline T max(T a, T b) { return a >= b ? a : b; }
template<class T> inline int sgn(T a) { return a < 0 ? -1 : a > 0 ? 1 : 0; }
template<class T> inline void swap(T &a, T &b) { T t = a; a = b; b = t; }
#endif

#endif	/* TOOLS_H */


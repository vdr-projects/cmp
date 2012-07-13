/**
 * File:      StringList.h
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
#ifndef STRINGLIST_H
#define	STRINGLIST_H

#include <Vector.h>
#include <string.h>

inline int CompareStrings(const void *a, const void *b)
{
  return strcmp(*(const char **)a, *(const char **)b);
}

inline int CompareStringsIgnoreCase(const void *a, const void *b)
{
  return strcasecmp(*(const char **)a, *(const char **)b);
}

class cStringList : public cVector<char *> {
public:
  cStringList(int Allocated = 10): cVector<char *>(Allocated) {}
  virtual ~cStringList();
  int Find(const char *s) const;
  void Sort(bool IgnoreCase = false)
  {
    if (IgnoreCase)
       cVector<char *>::Sort(CompareStringsIgnoreCase);
    else
       cVector<char *>::Sort(CompareStrings);
  }
  virtual void Clear(void);
  };

#endif	/* STRINGLIST_H */


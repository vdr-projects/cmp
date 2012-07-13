/**
 * File:      FileNameList.cc
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
#include <FileNameList.h>
#include <ReadDir.h>
#include <String.h>
#include <sys/stat.h>


cString AddDirectory(const char *DirName, const char *FileName)
{
  return cString::sprintf("%s/%s", DirName && *DirName ? DirName : ".", FileName);
}

// TODO better GetFileNames(const char *Directory, cStringList *List)?
cFileNameList::cFileNameList(const char *Directory, bool DirsOnly)
{
  Load(Directory, DirsOnly);
}

bool cFileNameList::Load(const char *Directory, bool DirsOnly)
{
  Clear();
  if (Directory) {
     cReadDir d(Directory);
     struct dirent *e;
     if (d.Ok()) {
        while ((e = d.Next()) != NULL) {
              if (DirsOnly) {
                 struct stat ds;
                 if (stat(AddDirectory(Directory, e->d_name), &ds) == 0) {
                    if (!S_ISDIR(ds.st_mode))
                       continue;
                    }
                 }
              Append(strdup(e->d_name));
              }
        Sort();
        return true;
        }
     else
        LOG_ERROR_STR(Directory);
     }
  return false;
}

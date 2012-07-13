/**
 * File:      Vector.h
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
#ifndef VECTOR_H
#define	VECTOR_H

#include <stddef.h>
#include <Logging.h>
#include <stdlib.h>

template<class T> class cVector {
  ///< cVector may only be used for *simple* types, like int or pointers - not for class objects that allocate additional memory!
public:
  cVector(int Allocated = 10)
  {
    allocated = 0;
    size = 0;
    data = NULL;
    Realloc(Allocated);
  }
  virtual ~cVector() { free(data); }
  T& At(int Index) const
  {
    Realloc(Index);
    if (Index >= size)
       size = Index + 1;
    return data[Index];
  }
  const T& operator[](int Index) const
  {
    return At(Index);
  }
  T& operator[](int Index)
  {
    return At(Index);
  }
  int Size(void) const { return size; }
  virtual void Insert(T Data, int Before = 0)
  {
    if (Before < size) {
       Realloc(size);
       memmove(&data[Before + 1], &data[Before], (size - Before) * sizeof(T));
       size++;
       data[Before] = Data;
       }
    else
       Append(Data);
  }
  virtual void Append(T Data)
  {
    if (size >= allocated)
       Realloc(allocated * 3 / 2); // increase size by 50%
    data[size++] = Data;
  }
  virtual void Remove(int Index)
  {
    if (Index < size - 1)
       memmove(&data[Index], &data[Index + 1], (size - Index) * sizeof(T));
    size--;
  }
  virtual void Clear(void)
  {
    for (int i = 0; i < size; i++)
        data[i] = T(0);
    size = 0;
  }
  void Sort(__compar_fn_t Compare)
  {
    qsort(data, size, sizeof(T), Compare);
  }

private:
  mutable int allocated;
  mutable int size;
  mutable T *data;
  cVector(const cVector &Vector) {} // don't copy...
  cVector &operator=(const cVector &Vector) { return *this; } // ...or assign this!
  void Realloc(int Index) const
  {
    if (++Index > allocated) {
       data = (T *)realloc(data, Index * sizeof(T));
       if (!data) {
          esyslog("ERROR: out of memory - abort!");
          abort();
          }
       for (int i = allocated; i < Index; i++)
           data[i] = T(0);
       allocated = Index;
       }
  }
  };

#endif	/* VECTOR_H */


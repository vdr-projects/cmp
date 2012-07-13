/**
 * File:      String.h
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
#ifndef STRING_H
#define	STRING_H

#include <CharsetConv.h>
#include <stddef.h>
#include <stdarg.h>

class cString {
public:
  cString(const char *S = NULL, bool TakePointer = false);
  cString(const cString &String);
  virtual ~cString();
  operator const void * () const { return s; } // to catch cases where operator*() should be used
  operator const char * () const { return s; } // for use in (const char *) context
  const char * operator*() const { return s; } // for use in (const void *) context (printf() etc.)
  cString &operator=(const cString &String);
  cString &operator=(const char *String);
  cString &Truncate(int Index); ///< Truncate the string at the given Index (if Index is < 0 it is counted from the end of the string).
  static cString sprintf(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
  static cString vsprintf(const char *fmt, va_list &ap);

private:
  char *s;
  };

char *strcpyrealloc(char *dest, const char *src);
char *strn0cpy(char *dest, const char *src, size_t n);
char *strreplace(char *s, char c1, char c2);
char *strreplace(char *s, const char *s1, const char *s2); ///< re-allocates 's' and deletes the original string if necessary!
inline char *skipspace(const char *s)
{
  if ((uchar)*s > ' ') // most strings don't have any leading space, so handle this case as fast as possible
     return (char *)s;
  while (*s && (uchar)*s <= ' ') // avoiding isspace() here, because it is much slower
        s++;
  return (char *)s;
}
char *stripspace(char *s);
char *compactspace(char *s);
cString strescape(const char *s, const char *chars);
bool startswith(const char *s, const char *p);
bool endswith(const char *s, const char *p);
bool isempty(const char *s);
int numdigits(int n);
bool isnumber(const char *s);
int64_t StrToNum(const char *s);
    ///< Converts the given string to a number.
    ///< The numerical part of the string may be followed by one of the letters
    ///< K, M, G or T to abbreviate Kilo-, Mega-, Giga- or Terabyte, respectively
    ///< (based on 1024). Everything after the first non-numeric character is
    ///< silently ignored, as are any characters other than the ones mentioned here.
cString itoa(int n);



#endif	/* STRING_H */


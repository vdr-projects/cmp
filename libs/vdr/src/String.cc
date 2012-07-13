/**
 * File:      String.cc
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
#include <String.h>
#include <Logging.h>
#include <i18n.h>
#include <tools.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <ctype.h>

char *strcpyrealloc(char *dest, const char *src)
{
  if (src) {
     int l = max(dest ? strlen(dest) : 0, strlen(src)) + 1; // don't let the block get smaller!
     dest = (char *)realloc(dest, l);
     if (dest)
        strcpy(dest, src);
     else
        esyslog("ERROR: out of memory");
     }
  else {
     free(dest);
     dest = NULL;
     }
  return dest;
}

char *strn0cpy(char *dest, const char *src, size_t n)
{
  char *s = dest;
  for ( ; --n && (*dest = *src) != 0; dest++, src++) ;
  *dest = 0;
  return s;
}

char *strreplace(char *s, char c1, char c2)
{
  if (s) {
     char *p = s;
     while (*p) {
           if (*p == c1)
              *p = c2;
           p++;
           }
     }
  return s;
}

char *strreplace(char *s, const char *s1, const char *s2)
{
  char *p = strstr(s, s1);
  if (p) {
     int of = p - s;
     int l  = strlen(s);
     int l1 = strlen(s1);
     int l2 = strlen(s2);
     if (l2 > l1) {
        if (char *NewBuffer = (char *)realloc(s, l + l2 - l1 + 1))
           s = NewBuffer;
        else {
           esyslog("ERROR: out of memory");
           return s;
           }
        }
     char *sof = s + of;
     if (l2 != l1)
        memmove(sof + l2, sof + l1, l - of - l1 + 1);
     strncpy(sof, s2, l2);
     }
  return s;
}

char *stripspace(char *s)
{
  if (s && *s) {
     for (char *p = s + strlen(s) - 1; p >= s; p--) {
         if (!isspace(*p))
            break;
         *p = 0;
         }
     }
  return s;
}

char *compactspace(char *s)
{
  if (s && *s) {
     char *t = stripspace(skipspace(s));
     char *p = t;
     while (p && *p) {
           char *q = skipspace(p);
           if (q - p > 1)
              memmove(p + 1, q, strlen(q) + 1);
           p++;
           }
     if (t != s)
        memmove(s, t, strlen(t) + 1);
     }
  return s;
}

cString strescape(const char *s, const char *chars)
{
  char *buffer;
  const char *p = s;
  char *t = NULL;
  while (*p) {
        if (strchr(chars, *p)) {
           if (!t) {
              buffer = MALLOC(char, 2 * strlen(s) + 1);
              t = buffer + (p - s);
              s = strcpy(buffer, s);
              }
           *t++ = '\\';
           }
        if (t)
           *t++ = *p;
        p++;
        }
  if (t)
     *t = 0;
  return cString(s, t != NULL);
}

bool startswith(const char *s, const char *p)
{
  while (*p) {
        if (*p++ != *s++)
           return false;
        }
  return true;
}

bool endswith(const char *s, const char *p)
{
  const char *se = s + strlen(s) - 1;
  const char *pe = p + strlen(p) - 1;
  while (pe >= p) {
        if (*pe-- != *se-- || (se < s && pe >= p))
           return false;
        }
  return true;
}

bool isempty(const char *s)
{
  return !(s && *skipspace(s));
}

int numdigits(int n)
{
  int res = 1;
  while (n >= 10) {
        n /= 10;
        res++;
        }
  return res;
}

bool isnumber(const char *s)
{
  if (!s || !*s)
     return false;
  do {
     if (!isdigit(*s))
        return false;
     } while (*++s);
  return true;
}

int64_t StrToNum(const char *s)
{
  char *t = NULL;
  int64_t n = strtoll(s, &t, 10);
  if (t) {
     switch (*t) {
       case 'T': n *= 1024;
       case 'G': n *= 1024;
       case 'M': n *= 1024;
       case 'K': n *= 1024;
       }
     }
  return n;
}

cString itoa(int n)
{
  char buf[16];
  snprintf(buf, sizeof(buf), "%d", n);
  return buf;
}

// --- cString ---------------------------------------------------------------

cString::cString(const char *S, bool TakePointer)
{
  s = TakePointer ? (char *)S : S ? strdup(S) : NULL;
}

cString::cString(const cString &String)
{
  s = String.s ? strdup(String.s) : NULL;
}

cString::~cString()
{
  free(s);
}

cString &cString::operator=(const cString &String)
{
  if (this == &String)
     return *this;
  free(s);
  s = String.s ? strdup(String.s) : NULL;
  return *this;
}

cString &cString::operator=(const char *String)
{
  if (s == String)
    return *this;
  free(s);
  s = String ? strdup(String) : NULL;
  return *this;
}

cString &cString::Truncate(int Index)
{
  int l = strlen(s);
  if (Index < 0)
     Index = l + Index;
  if (Index >= 0 && Index < l)
     s[Index] = 0;
  return *this;
}

cString cString::sprintf(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  char *buffer;
  if (!fmt || vasprintf(&buffer, fmt, ap) < 0) {
     esyslog("error in vasprintf('%s', ...)", fmt);
     buffer = strdup("???");
     }
  va_end(ap);
  return cString(buffer, true);
}

cString cString::vsprintf(const char *fmt, va_list &ap)
{
  char *buffer;
  if (!fmt || vasprintf(&buffer, fmt, ap) < 0) {
     esyslog("error in vasprintf('%s', ...)", fmt);
     buffer = strdup("???");
     }
  return cString(buffer, true);
}

cString WeekDayName(int WeekDay)
{
  char buffer[16];
  WeekDay = WeekDay == 0 ? 6 : WeekDay - 1; // we start with Monday==0!
  if (0 <= WeekDay && WeekDay <= 6) {
     // TRANSLATORS: abbreviated weekdays, beginning with monday (must all be 3 letters!)
     const char *day = tr("MonTueWedThuFriSatSun");
     day += Utf8SymChars(day, WeekDay * 3);
     strn0cpy(buffer, day, min(Utf8SymChars(day, 3) + 1, int(sizeof(buffer))));
     return buffer;
     }
  else
     return "???";
}

cString WeekDayName(time_t t)
{
  struct tm tm_r;
  return WeekDayName(localtime_r(&t, &tm_r)->tm_wday);
}

cString WeekDayNameFull(int WeekDay)
{
  WeekDay = WeekDay == 0 ? 6 : WeekDay - 1; // we start with Monday==0!
  switch (WeekDay) {
    case 0: return tr("Monday");
    case 1: return tr("Tuesday");
    case 2: return tr("Wednesday");
    case 3: return tr("Thursday");
    case 4: return tr("Friday");
    case 5: return tr("Saturday");
    case 6: return tr("Sunday");
    default: return "???";
    }
}

cString WeekDayNameFull(time_t t)
{
  struct tm tm_r;
  return WeekDayNameFull(localtime_r(&t, &tm_r)->tm_wday);
}

cString DayDateTime(time_t t)
{
  char buffer[32];
  if (t == 0)
     time(&t);
  struct tm tm_r;
  tm *tm = localtime_r(&t, &tm_r);
  snprintf(buffer, sizeof(buffer), "%s %02d.%02d. %02d:%02d", *WeekDayName(tm->tm_wday), tm->tm_mday, tm->tm_mon + 1, tm->tm_hour, tm->tm_min);
  return buffer;
}

cString TimeToString(time_t t)
{
  char buffer[32];
  if (ctime_r(&t, buffer)) {
     buffer[strlen(buffer) - 1] = 0; // strip trailing newline
     return buffer;
     }
  return "???";
}

cString DateString(time_t t)
{
  char buf[32];
  struct tm tm_r;
  tm *tm = localtime_r(&t, &tm_r);
  char *p = stpcpy(buf, WeekDayName(tm->tm_wday));
  *p++ = ' ';
  strftime(p, sizeof(buf) - (p - buf), "%d.%m.%Y", tm);
  return buf;
}

cString ShortDateString(time_t t)
{
  char buf[32];
  struct tm tm_r;
  tm *tm = localtime_r(&t, &tm_r);
  strftime(buf, sizeof(buf), "%d.%m.%y", tm);
  return buf;
}

cString TimeString(time_t t)
{
  char buf[25];
  struct tm tm_r;
  strftime(buf, sizeof(buf), "%R", localtime_r(&t, &tm_r));
  return buf;
}

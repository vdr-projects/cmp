/**
 * ======================== legal notice ======================
 * 
 * File:      util.h
 * Created:   3. Juli 2012, 13:00
 * Author:    <a href="mailto:geronimo013@gmx.de">Geronimo</a>
 * Project:   libutil - base classes used by other libraries
 * 
 * CMP - compound media player
 * 
 * is a client/server mediaplayer intended to play any media from any workstation
 * without the need to export or mount shares. cmps is an easy to use backend
 * with a (ready to use) HTML-interface. Additionally the backend supports
 * authentication via HTTP-digest authorization.
 * cmpc is a client with vdr-like osd-menues.
 * 
 * Copyright (c) 2012 Reinhard Mantey, some rights reserved!
 * published under Creative Commons by-sa
 * For details see http://creativecommons.org/licenses/by-sa/3.0/
 * 
 * The cmp project's homepage is at http://projects.vdr-developer.org/projects/cmp
 * 
 * --------------------------------------------------------------
 */
#ifndef UTIL_H
#define	UTIL_H

#include <stdlib.h>
#define FREE(m)        { void *_tmp_ = m; m = NULL; free(_tmp_); }
#define TO_STRING(s)    #s
#define EVER           ;;

extern const char * skipWhitespace(const char *Buffer);
extern const char *getWord(char *buf, int bufSize, const char *src);
extern const char *restOfLine(char *buf, int bufSize, const char *src);

#endif	/* UTIL_H */


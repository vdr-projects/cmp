/**
 * ======================== legal notice ======================
 * 
 * File:      NamedValue.h
 * Created:   3. Juli 2012, 17
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
#ifndef NAMEDVALUE_H
#define	NAMEDVALUE_H

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <vector>

class cNamedValue {
public:
  cNamedValue(char *Name, char *Value = NULL, bool takePointers = false);
  cNamedValue(const char *Name, const char *Value = NULL);
  cNamedValue(const cNamedValue &other);
  virtual ~cNamedValue();
  
  cNamedValue &operator =(const cNamedValue &other);
  const char *Name() const { return name; }
  const char *Value() const { return value; }
  void SetValue(const char *Value) { free(value); value = strdup(Value); }

private:
  char *name;
  char *value;
  };

#endif	/* NAMEDVALUE_H */


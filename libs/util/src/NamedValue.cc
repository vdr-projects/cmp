/**
 * ======================== legal notice ======================
 * 
 * File:      NamedValue.cc
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
#include <NamedValue.h>
#include <util.h>
#include <stdlib.h>
#include <stdio.h>


cNamedValue::cNamedValue(char *Name, char *Value, bool takePointers)
 : name(takePointers ? Name : strdup(Name))
 , value(takePointers ? Value : Value ? strdup(Value) : NULL)
{
}

cNamedValue::cNamedValue(const char *Name, const char *Value)
 : name(strdup(Name))
 , value(Value ? strdup(Value) : NULL)
{
}

cNamedValue::cNamedValue(const cNamedValue &other)
 : name(strdup(other.name))
 , value(other.value ? strdup(other.value) : NULL)
{
  printf(">>> OUPS - just cloned a named value with name<%s> and value<%s>\n", name, value);
}

cNamedValue::~cNamedValue()
{
  FREE(name);
  FREE(value);
}

cNamedValue &cNamedValue::operator=(const cNamedValue &other)
{
  printf(">>> OUPS - I'm inside of operator = !!!\n");
  if (&other == this) return *this;
  FREE(name);
  FREE(value);
  name = strdup(other.Name());
  if (other.value) value = strdup(other.Value());
  else value = NULL;

  return *this;
}
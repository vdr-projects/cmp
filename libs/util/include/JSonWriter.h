/**
 * ======================== legal notice ======================
 * 
 * File:      JSonWriter.h
 * Created:   6. Juli 2012, 12
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
#ifndef JSONWRITER_H
#define	JSONWRITER_H

#include <stack>
#include <StringBuilder.h>

class cJSonWriter {
public:
  cJSonWriter(cStringBuilder &StringBuilder);
  virtual ~cJSonWriter();

  cJSonWriter &Object(void);
  cJSonWriter &EndObject(void);
  cJSonWriter &Array(void);
  cJSonWriter &EndArray(void);
  cJSonWriter &Key(const char *Name);
  cJSonWriter &Value(const char *Text);
  cJSonWriter &Value(int v);
  cJSonWriter &Value(long v);
  cJSonWriter &Value(size_t v);
  cJSonWriter &Value(bool v);
  cJSonWriter &Value(double v);

private:
  typedef enum {
    JS_Unknown,
    JS_Object,
    JS_Array,
    JS_Key
  } JSonState;
  cJSonWriter::JSonState State(void);
  void PushState(JSonState State);
  cJSonWriter::JSonState PopState(void);
  std::stack<JSonState> state;
  JSonState lastState;
  cStringBuilder &sb;
  };

#endif	/* JSONWRITER_H */


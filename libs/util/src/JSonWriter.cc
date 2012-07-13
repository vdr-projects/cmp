/**
 * ======================== legal notice ======================
 *
 * File:      JSonWriter.cc
 * Created:   6. Juli 2012, 12:47
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
#include <JSonWriter.h>
#include <StringBuilder.h>
#include <Logging.h>
#include <stdio.h>

cJSonWriter::cJSonWriter(cStringBuilder &StringBuilder)
 : lastState(JS_Unknown)
 , sb(StringBuilder)
{
}

cJSonWriter::~cJSonWriter()
{
}

cJSonWriter::JSonState cJSonWriter::State()
{
  if (state.empty()) return JS_Unknown;
  return state.top();
}

void cJSonWriter::PushState(JSonState State)
{
  state.push(State);
}

cJSonWriter::JSonState cJSonWriter::PopState(void)
{
  lastState = State();
  state.pop();

  return lastState;
}

cJSonWriter &cJSonWriter::Object(void) {
  if (lastState == JS_Object) sb.Append(",");
  sb.Append("{");
  PushState(JS_Object);
  lastState = JS_Unknown;
  return *this;
}

cJSonWriter &cJSonWriter::EndObject(void) {
  if (State() != JS_Object) {
     esyslog("JSonWriter::EndObject(): invalid status %d - should be %d", State(), JS_Object);
     }
  else {
     PopState();
     sb.Append("}");
     }
  return *this;
}

cJSonWriter &cJSonWriter::Array(void) {
  if (State() != JS_Key) {
     esyslog("JSonWriter::Array(): invalid status %d - should be %d", State(), JS_Key);
     }
  else {
     sb.Append("[");
     PushState(JS_Array);
     lastState = JS_Unknown;
     }
  return *this;
}

cJSonWriter &cJSonWriter::EndArray(void) {
  if (State() != JS_Array) {
     esyslog("JSonWriter::EndArray(): invalid status %d - should be %d", State(), JS_Array);
     }
  else {
     sb.Append("]");
     PopState();
     if (State() == JS_Key) PopState(); // array is a value, so pop the key
     }
  return *this;
}

cJSonWriter &cJSonWriter::Key(const char *Name) {
  if (State() != JS_Object) {
     esyslog("JSonWriter::Key(): invalid status %d - should be %d", State(), JS_Object);
     }
  else {
     if (lastState == JS_Key) sb.Append(", ");
     sb.Append("\"").Append(Name).Append("\": ");
     PushState(JS_Key);
     }
  return *this;
}

cJSonWriter &cJSonWriter::Value(const char *Text) {
  if (State() != JS_Key) {
     esyslog("JSonWriter::Value(): invalid status %d - should be %d", State(), JS_Key);
     }
  else {
     PopState();
     sb.Append("\"").Append(Text).Append("\"");
     }
  return *this;
}

cJSonWriter &cJSonWriter::Value(int v) {
  if (State() != JS_Key) {
     esyslog("JSonWriter::Value(): invalid status %d - should be %d", State(), JS_Key);
     }
  else {
     PopState();
     sb.Append(v);
     }
  return *this;
}

cJSonWriter &cJSonWriter::Value(long v) {
  if (State() != JS_Key) {
     esyslog("JSonWriter::Value(): invalid status %d - should be %d", State(), JS_Key);
     }
  else {
     PopState();
     sb.Append(v);
     }
  return *this;
}

cJSonWriter &cJSonWriter::Value(size_t v) {
  if (State() != JS_Key) {
     esyslog("JSonWriter::Value(): invalid status %d - should be %d", State(), JS_Key);
     }
  else {
     PopState();
     sb.Append(v);
     }
  return *this;
}

cJSonWriter &cJSonWriter::Value(double v) {
  if (State() != JS_Key) {
     esyslog("JSonWriter::Value(): invalid status %d - should be %d", State(), JS_Key);
     }
  else {
     PopState();
     sb.Append(v);
     }
  return *this;
}

cJSonWriter &cJSonWriter::Value(bool v) {
  if (State() != JS_Key) {
     esyslog("JSonWriter::Value(): invalid status %d - should be %d", State(), JS_Key);
     }
  else {
     PopState();
     sb.Append(v, "true", "false");
     }
  return *this;
}

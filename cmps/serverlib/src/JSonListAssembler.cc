/**
 * ======================== legal notice ======================
 *
 * File:      JSonListAssembler.cc
 * Created:   6. Juli 2012, 09:53
 * Author:    <a href="mailto:geronimo013@gmx.de">Geronimo</a>
 * Project:   cmps - the backend (server) part of compound media player
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
#include <JSonListAssembler.h>
#include <AbstractMedia.h>
#include <JSonWriter.h>

cJSonListAssembler::cJSonListAssembler()
{
}

cJSonListAssembler::~cJSonListAssembler()
{
  if (writer) delete writer;
  writer = NULL;
}

bool cJSonListAssembler::OpenList(cStringBuilder &sb, std::map<int, size_t> &Categories, size_t total, size_t start, uint delta)
{
  writer = new cJSonWriter(sb);

  writer->Object().Key("total").Value(total);
  writer->Key("types").Array();
  std::map<int, size_t>::iterator it = Categories.begin();

  while (it != Categories.end()) {
        writer->Object().Key("name").Value(cAbstractMedia::MediaType2Text(it->first));
        writer->Key("start").Value(it->second).EndObject();
        ++it;
        }
  writer->EndArray().Key("results").Array();

  return true;
}

bool cJSonListAssembler::AddElement(cStringBuilder &sb, void *ListElement, bool odd)
{
  cAbstractMedia *m = (cAbstractMedia *)ListElement;

  writer->Object();
  writer->Key("name").Value(m->Name());
  writer->Key("type").Value(m->MediaType());
  writer->Key("path").Value(m->LogicalPath());
  writer->EndObject();

  return true;
}

bool cJSonListAssembler::CloseList(cStringBuilder &sb, size_t total, size_t start, uint delta)
{
  writer->EndArray().EndObject();

  return true;
}

const char *cJSonListAssembler::MediaType(void) const
{
  return "application/json";
}
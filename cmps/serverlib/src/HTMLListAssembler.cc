/**
 * ======================== legal notice ======================
 *
 * File:      HTMLListAssembler.cc
 * Created:   6. Juli 2012, 09
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
#include <HTMLListAssembler.h>
#include <AbstractMedia.h>
#include <StringBuilder.h>
#include <Url.h>
#include <tools.h>

cHTMLListAssembler::cHTMLListAssembler()
{
}

cHTMLListAssembler::~cHTMLListAssembler()
{
}

bool cHTMLListAssembler::OpenList(cStringBuilder &sb, std::map<int, size_t> &Categories, size_t total, size_t start, uint delta)
{
  genHTMLPrefix(sb, "Medien-Liste");

  genPreviousLink(sb, !start ? -1 : max<size_t>(0, start - delta));
  genNextLink(sb, start + delta >= total ? -1 : min(start + delta, total));
  genDelim(sb);
  genTypeMenu(sb, Categories);
  genDelim(sb);

  return true;
}

bool cHTMLListAssembler::AddElement(cStringBuilder &sb, void *ListElement, bool odd)
{
  genMediaLink(sb, ListElement, odd);

  return true;
}

bool cHTMLListAssembler::CloseList(cStringBuilder &sb, size_t total, size_t start, uint delta)
{
  genDelim(sb);
  genPreviousLink(sb, !start ? -1 : max<size_t>(0, start - delta));
  genNextLink(sb, start + delta >= total ? -1 : min(start + delta, total));

  return true;
}

cStringBuilder &cHTMLListAssembler::genHTMLPrefix(cStringBuilder& sb, const char *Title)
{
  sb.Append("<html><head><title>").Append(Title).Append("</title>");

  sb.Append("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">");
  sb.Append("<style type=\"text/css\"><!--\n");
  sb.Append("body { background: #eef; } ");
  sb.Append("h1 { margin: 0; margin-top: 20px; padding: 0; text-align: center; } ");
  sb.Append(".left { text-align: left; } ");
  sb.Append(".right { margin-top: -1em; text-align: right; } ");
  sb.Append(".center { text-align: center; } ");
  sb.Append(".hmenu { padding: 1em; margin-left: 1em; } ");
  sb.Append(".odd { display: block; background: #DDF; margin-left: 1em; margin-right: 1em; padding: 5px; padding-left: 1em; } ");
  sb.Append(".even { display: block; background: #EEF; margin-left: 1em; margin-right: 1em; padding: 5px; padding-left: 1em; } ");
  sb.Append("\n--></style>");
  sb.Append("</head><body><h1>").Append(Title).Append("</h1>");

  return sb;
}

const char *cHTMLListAssembler::MediaType() const
{
  return "text/html";
}

cStringBuilder &cHTMLListAssembler::genDelim(cStringBuilder &sb)
{
  return sb.Append("<div class=\"break\"><hr/></div>");
}

cStringBuilder &cHTMLListAssembler::genMediaLink(cStringBuilder &sb, void *Element, bool odd)
{
  cAbstractMedia *m = (cAbstractMedia *)Element;

  if (m) {
     sb.Append("<a class=\"");
     sb.Append(odd ? "odd" : "even");
     sb.Append("\" href=\"");
     sb.Append(m->URI());
     sb.Append("\">");
     switch (m->MediaType()) {
       case cAbstractMedia::Audio:              sb.Append("[A] "); break;
       case cAbstractMedia::Movie:              sb.Append("[M] "); break;
       case cAbstractMedia::DVDImage:           sb.Append("[D] "); break;
       case cAbstractMedia::LegacyVdrRecording: sb.Append("[L] "); break;
       case cAbstractMedia::VdrRecording:       sb.Append("[V] "); break;
       case cAbstractMedia::Picture:            sb.Append("[P] "); break;
       default: ;
       }
     sb.Append(m->Name());
     sb.Append("</a>");
     }
  return sb;
}

cStringBuilder &cHTMLListAssembler::genNextLink(cStringBuilder &sb, int n)
{
  sb.Append("<div class=\"right\">");
  if (n < 0)
      sb.Append("next");
  else {
      sb.Append("<a href=\"/?start=");
      sb.Append(n);
      sb.Append("\">");
      sb.Append("next");
      sb.Append("</a>");
  }
  sb.Append("</div>");

  return sb;
}

cStringBuilder &cHTMLListAssembler::genPreviousLink(cStringBuilder &sb, int n)
{
  sb.Append("<div class=\"left\">");
  if (n < 0)
      sb.Append("previous");
  else {
      sb.Append("<a href=\"/?start=");
      sb.Append(n);
      sb.Append("\">");
      sb.Append("previous");
      sb.Append("</a>");
  }
  sb.Append("</div>");

  return sb;
}

cStringBuilder &cHTMLListAssembler::genTypeMenu(cStringBuilder &sb, std::map<int, size_t> &Categories)
{
  sb.Append("<div class=\"topmenu\">");
  std::map<int, size_t>::iterator it = Categories.begin();

  while (it != Categories.end()) {
        sb.Append("<a class=\"hmenu\" href=\"/?start=");
        sb.Append(it->second);
        sb.Append("\">");
        sb.Append(cAbstractMedia::MediaType2Text(it->first));
        sb.Append("</a>");
        ++it;
        }
  sb.Append("</div>");

  return sb;
}
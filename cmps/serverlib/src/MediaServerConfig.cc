/**
 * ======================== legal notice ======================
 * 
 * File:      MediaServerConfig.cc
 * Created:   1. August 2012, 10:58
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
#include <MediaServerConfig.h>
#include <AbstractMedia.h>
#include <Audio.h>
#include <DVDImage.h>
#include <Movie.h>
#include <Picture.h>
#include <LegacyVdrRecording.h>
#include <VdrRecording.h>
#include <pcrecpp.h>

static pcrecpp::RE sequence("\\s*(\\S+)\\s*,\\s*(.+)");
static pcrecpp::RE sequenceLast("(\\S+)\\s*");

cMediaServerConfig::cMediaServerConfig(const char *ConfigBaseDir)
 : cServerConfig(ConfigBaseDir)
{
}

cMediaServerConfig::~cMediaServerConfig()
{
}

bool cMediaServerConfig::Eval(cConfigReader::ConfigEntry* Entry)
{
  std::string name = std::get<0>(*Entry);

  if (!strcmp("no-deep-scan", name.c_str())) {
     int es[cAbstractMedia::Unknown] = {1};
     int mx = sizeof(es) / sizeof(int);
     const char *rawValue = std::get<1>(*Entry).c_str();
     SetWantExtendedScan(true);
     std::string cur, rest;

     for (int i=0; i < mx; ++i) es[i] = 1;
     while (sequence.FullMatch(rawValue, &cur, &rest)) {
           if (!strcmp("Audio", cur.c_str())) es[cAbstractMedia::Audio] = 0;
           else if (!strcmp("Movie", cur.c_str())) es[cAbstractMedia::Movie] = 0;
           else if (!strcmp("DVDImage", cur.c_str())) es[cAbstractMedia::DVDImage] = 0;
           else if (!strcmp("LegacyVdrRecording", cur.c_str())) es[cAbstractMedia::LegacyVdrRecording] = 0;
           else if (!strcmp("VdrRecording", cur.c_str())) es[cAbstractMedia::VdrRecording] = 0;
           else if (!strcmp("Picture", cur.c_str())) es[cAbstractMedia::Picture] = 0;
           rawValue = rest.c_str();
           }
     cur = rawValue;
     if (!strcmp("Audio", cur.c_str())) es[cAbstractMedia::Audio] = 0;
     else if (!strcmp("Movie", cur.c_str())) es[cAbstractMedia::Movie] = 0;
     else if (!strcmp("DVDImage", cur.c_str())) es[cAbstractMedia::DVDImage] = 0;
     else if (!strcmp("LegacyVdrRecording", cur.c_str())) es[cAbstractMedia::LegacyVdrRecording] = 0;
     else if (!strcmp("VdrRecording", cur.c_str())) es[cAbstractMedia::VdrRecording] = 0;
     else if (!strcmp("Picture", cur.c_str())) es[cAbstractMedia::Picture] = 0;

     for (int i=0; i < mx; ++i) {
         switch ((cAbstractMedia::SupportedMediaType) i) {
           case cAbstractMedia::Audio:              cAudio::EnableDeepScan(es[i]); break;
           case cAbstractMedia::DVDImage:           cDVDImage::EnableDeepScan(es[i]); break;
           case cAbstractMedia::LegacyVdrRecording: cLegacyVdrRecording::EnableDeepScan(es[i]); break;
           case cAbstractMedia::Movie:              cMovie::EnableDeepScan(es[i]); break;
           case cAbstractMedia::Picture:            cPicture::EnableDeepScan(es[i]); break;
           case cAbstractMedia::VdrRecording:       cVdrRecording::EnableDeepScan(es[i]); break;
           default: break;
           }
         }
     return true;
     }
  else if (!strcmp("deep-scan", name.c_str())) {
     int es[cAbstractMedia::Unknown] = {0};
     int mx = sizeof(es) / sizeof(int);
     const char *rawValue = std::get<1>(*Entry).c_str();
     SetWantExtendedScan(true);
     std::string cur, rest;

     for (int i=0; i < mx; ++i) es[i] = 0;
     while (sequence.FullMatch(rawValue, &cur, &rest)) {
           if (!strcmp("Audio", cur.c_str())) es[cAbstractMedia::Audio] = 1;
           else if (!strcmp("Movie", cur.c_str())) es[cAbstractMedia::Movie] = 1;
           else if (!strcmp("DVDImage", cur.c_str())) es[cAbstractMedia::DVDImage] = 1;
           else if (!strcmp("LegacyVdrRecording", cur.c_str())) es[cAbstractMedia::LegacyVdrRecording] = 1;
           else if (!strcmp("VdrRecording", cur.c_str())) es[cAbstractMedia::VdrRecording] = 1;
           else if (!strcmp("Picture", cur.c_str())) es[cAbstractMedia::Picture] = 1;
           rawValue = rest.c_str();
           }
     cur = rawValue;
     if (!strcmp("Audio", cur.c_str())) es[cAbstractMedia::Audio] = 1;
     else if (!strcmp("Movie", cur.c_str())) es[cAbstractMedia::Movie] = 1;
     else if (!strcmp("DVDImage", cur.c_str())) es[cAbstractMedia::DVDImage] = 1;
     else if (!strcmp("LegacyVdrRecording", cur.c_str())) es[cAbstractMedia::LegacyVdrRecording] = 1;
     else if (!strcmp("VdrRecording", cur.c_str())) es[cAbstractMedia::VdrRecording] = 1;
     else if (!strcmp("Picture", cur.c_str())) es[cAbstractMedia::Picture] = 1;

     for (int i=0; i < mx; ++i) {
         switch ((cAbstractMedia::SupportedMediaType) i) {
           case cAbstractMedia::Audio:              cAudio::EnableDeepScan(es[i]); break;
           case cAbstractMedia::DVDImage:           cDVDImage::EnableDeepScan(es[i]); break;
           case cAbstractMedia::LegacyVdrRecording: cLegacyVdrRecording::EnableDeepScan(es[i]); break;
           case cAbstractMedia::Movie:              cMovie::EnableDeepScan(es[i]); break;
           case cAbstractMedia::Picture:            cPicture::EnableDeepScan(es[i]); break;
           case cAbstractMedia::VdrRecording:       cVdrRecording::EnableDeepScan(es[i]); break;
           default: break;
           }
         }
     return true;
     }
  else return cServerConfig::Eval(Entry);
}
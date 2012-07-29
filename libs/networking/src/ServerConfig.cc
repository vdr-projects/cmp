/**
 * ======================== legal notice ======================
 *
 * File:      ServerConfig.cc
 * Created:   8. Juli 2012, 06
 * Author:    <a href="mailto:geronimo013@gmx.de">Geronimo</a>
 * Project:   libnetworking: classes for tcp/ip sockets and http-protocol handling
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
#include <ServerConfig.h>
#include <ConfigReader.h>
#include <LineReader.h>
#include <FileReader.h>
#include <File.h>
#include <Logging.h>
#include <util.h>
#include <sys/stat.h>
#include <sys/types.h>

cServerConfig::cServerConfig(const char *ConfigBaseDir)
 : server(12345, 5)
 , authorizationRequired(false)
 , wantExtendedScan(false)
 , configBaseDir(ConfigBaseDir ? strdup(ConfigBaseDir) : NULL)
 , credentialsFile(NULL)
 , documentRoot(NULL)
 , appIconPath(NULL)
 , mediaInfo(NULL)
 , ffmpeg(NULL)
{
}

cServerConfig::~cServerConfig()
{
  FREE(configBaseDir);
  FREE(documentRoot);
  FREE(appIconPath);
  FREE(mediaInfo);
  FREE(ffmpeg);
}

void cServerConfig::SetAppIcon(const char *AppIcon)
{
  struct stat st;

  if (!AppIcon) return;
  if (!stat(AppIcon, &st)) {
     FREE(appIconPath);
     appIconPath = strdup(AppIcon);
     }
  else esyslog("ERROR: failed to stat application icon! %s", AppIcon);
}

void cServerConfig::SetConfigBaseDir(const char *ConfigBaseDir)
{
  free(configBaseDir);
  configBaseDir = ConfigBaseDir ? strdup(ConfigBaseDir) : NULL;
}

void cServerConfig::SetCredentialsFile(const char *FileName)
{
  free(credentialsFile);
  credentialsFile = FileName ? strdup(FileName) : NULL;
}

void cServerConfig::SetDocumentRoot(const char *DocumentRoot)
{
  free(documentRoot);
  documentRoot = DocumentRoot ? strdup(DocumentRoot) : NULL;
}

void cServerConfig::SetMediaInfo(const char *MediaInfo)
{
  free(mediaInfo);
  mediaInfo = MediaInfo ? strdup(MediaInfo) : NULL;
}

void cServerConfig::SetFFMpeg(const char* FFMpeg)
{
  free(ffmpeg);
  ffmpeg = FFMpeg ? strdup(FFMpeg) : NULL;
}

void cServerConfig::SetPort(int port)
{
  server.SetPort(port);
}

void cServerConfig::Dump(void)
{
  isyslog("server-config - socket #%d", server.Port());
  isyslog("server-config - authorization required: %s", authorizationRequired ? "yes" : "no");
  isyslog("server-config - do extended scan: %s", wantExtendedScan ? "yes" : "no");
  isyslog("server-config - application dir: %s", configBaseDir);
  isyslog("server-config - credentials file: %s", credentialsFile);
  isyslog("server-config - media root: %s", documentRoot);
  isyslog("server-config - app icon: %s", appIconPath);
  isyslog("server-config - mediainfo: %s", mediaInfo);
  isyslog("server-config - ffmpeg: %s", ffmpeg);
}

int cServerConfig::Load(const char* FileName)
{
  cConfigReader *cr = new cConfigReader(new cLineReader(new cFileReader(new cFile(configBaseDir, FileName))));
  cConfigReader::ConfigEntry *ce;
  int numberOfEntries = 0;

  while ((ce = cr->ReadValue())) {
        std::string name = std::get<0>(*ce);

        if (!strcmp("media-root", name.c_str())) {
           SetDocumentRoot(std::get<1>(*ce).c_str());
           ++numberOfEntries;
           }
        else if (!strcmp("favicon", name.c_str())) {
           SetAppIcon(std::get<1>(*ce).c_str());
           ++numberOfEntries;
           }
        else if (!strcmp("cmps-port", name.c_str())) {
           SetPort(atoi(std::get<1>(*ce).c_str()));
           ++numberOfEntries;
           }
#ifdef NOT_YET
        else if (!strcmp("want-auth", name.c_str())) {
           SetAuthorizationRequired(!strcasecmp("true", std::get<1>(*ce).c_str()));
           ++numberOfEntries;
           }
#endif
        else if (!strcmp("want-meta", name.c_str())) {
           SetWantExtendedScan(!strcasecmp("true", std::get<1>(*ce).c_str()));
           ++numberOfEntries;
           }
        else if (!strcmp("mediainfo", name.c_str())) {
           SetMediaInfo(std::get<1>(*ce).c_str());
           ++numberOfEntries;
           }
        else if (!strcmp("ffmpeg", name.c_str())) {
           SetFFMpeg(std::get<1>(*ce).c_str());
           ++numberOfEntries;
           }
        delete ce;
        }
  cr->Close();
  delete cr;

  return numberOfEntries > 0;
}

int cServerConfig::Store(const char* FileName)
{
  //TODO:
  return 0;
}

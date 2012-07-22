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
#include <Logging.h>
#include <util.h>
#include <sys/stat.h>
#include <sys/types.h>

cServerConfig::cServerConfig(int Port)
 : server(Port, 5)
 , documentRoot(NULL)
 , appIconPath(NULL)
{
}

cServerConfig::~cServerConfig()
{
  FREE(appIconPath);
  FREE(documentRoot);
}

void cServerConfig::SetAppIcon(const char* AppIcon)
{
  struct stat st;

  if (!AppIcon) return;
  if (!stat(AppIcon, &st)) {
     FREE(appIconPath);
     appIconPath = strdup(AppIcon);
     }
  else esyslog("ERROR: failed to stat application icon! %s", AppIcon);
}

void cServerConfig::SetDocumentRoot(const char* DocumentRoot)
{
  free(documentRoot);
  documentRoot = DocumentRoot ? strdup(DocumentRoot) : NULL;
}

void cServerConfig::SetPort(int port)
{
  server.SetPort(port);
}
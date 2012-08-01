/**
 * ======================== legal notice ======================
 * 
 * File:      ServerConfig.h
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
#ifndef SERVERCONFIG_H
#define	SERVERCONFIG_H

#include <Persistable.h>
#include <ServerSocket.h>
#include <Authorization.h>
#include <ConfigReader.h>

class cServerConfig : public cPersistable {
public:
  cServerConfig(const char *ConfigBaseDir);
  virtual ~cServerConfig();

  bool AuthorizationRequired(void) { return authorizationRequired; }
  const char *AppIconPath(void) const { return appIconPath; }
  const char *DocumentRoot(void) const { return documentRoot; }
  bool WantExtendedScan(void) const { return wantExtendedScan; }
  const char *CredentialsFile(void) const { return credentialsFile; }
  const char *MediaInfo(void) const { return mediaInfo; }
  const char *FFMpeg(void) const { return ffmpeg; }
  void Dump(void);
  virtual bool Eval(cConfigReader::ConfigEntry *Entry);
  virtual int Load(const char *FileName);
  virtual int Store(const char *FileName);
  void SetAppIcon(const char *AppIcon);
  void SetAuthorizationRequired(bool Authorize) { authorizationRequired = Authorize; }
  void SetConfigBaseDir(const char *ConfigBaseDir);
  void SetCredentialsFile(const char *FileName);
  void SetDocumentRoot(const char *DocumentRoot);
  void SetMediaInfo(const char *MediaInfo);
  void SetFFMpeg(const char *FFMpeg);
  void SetPort(int port);
  void SetWantExtendedScan(bool wantScan) { wantExtendedScan = wantScan; }

private:
  cServerSocket server;
  cAuthorizations authorizations;
  bool authorizationRequired;
  bool wantExtendedScan;
  char *configBaseDir;
  char *credentialsFile;
  char *documentRoot;
  char *appIconPath;
  char *mediaInfo;
  char *ffmpeg;
  friend class cHTTPServer;
  friend class cConnectionHandler;
  };

#endif	/* SERVERCONFIG_H */


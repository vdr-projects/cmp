/**
 * ======================== legal notice ======================
 * 
 * File:      ConnectionPoint.cc
 * Created:   4. Juli 2012, 06
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
#include <ConnectionPoint.h>
#include <util.h>
#include <poll.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

cConnectionPoint::cConnectionPoint(const char *NameOrIP, int Port, const char *RealName)
 : nameOrIP(strdup(NameOrIP))
 , realName(RealName ? strdup(RealName): NULL)
 , combined(NULL)
 , port(Port)
 , sock(-1)
{
}

cConnectionPoint::~cConnectionPoint()
{
  Close();
}

void cConnectionPoint::Close()
{
  if (sock > 0) {
     close(sock);
     sock = -1;
     }
  FREE(nameOrIP);
  FREE(realName);
  FREE(combined);
}

void cConnectionPoint::SetRealName(const char *Name)
{
  FREE(realName);
  realName = Name ? strdup(Name) : NULL;
}

int cConnectionPoint::IOWait(long MilliSeconds)
{
  struct pollfd fds;

  fds.fd = sock;
  fds.events = POLLIN | POLLPRI;

  int rv = poll(&fds, 1, MilliSeconds);

  if (rv > 0) return fds.revents; // so app can ask for priority events
  return rv;
}

const char *cConnectionPoint::AssembleCombined() const
{
  FREE(combined);
  size_t len = strlen(nameOrIP) + 16;

  if (realName) len += strlen(realName);
  char *p = (char *)malloc(len);

  if (realName) snprintf(p, len, "%s:%d (%s)", nameOrIP, port, realName);
  else snprintf(p, len, "%s:%d", nameOrIP, port);
  if (p) ((cConnectionPoint *)this)->combined = p;

  return combined;
}

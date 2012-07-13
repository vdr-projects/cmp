/**
 * ======================== legal notice ======================
 * 
 * File:      HTTPFileResponse.cc
 * Created:   4. Juli 2012, 07:50
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
#include <HTTPFileResponse.h>
#include <Logging.h>
#include <util.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

cHTTPFileResponse::cHTTPFileResponse(const char *RealPath)
 : cHTTPResponse(HTTP_OK)
 , realPath(RealPath)
 , fd(0)
{
  DetermineTypeAndSize(realPath);
}

cHTTPFileResponse::cHTTPFileResponse()
 : cHTTPResponse(HTTP_OK)
 , realPath(NULL)
 , fd(0)
{
}

cHTTPFileResponse::~cHTTPFileResponse()
{
}

void cHTTPFileResponse::DetermineTypeAndSize(const char* Path)
{
  struct stat st;
  const char *xt;

  if (!Path) return;
  if (stat(Path, &st) < 0) {
     esyslog("invalid path given - %d", errno);
     return;
     }
  SetContentSize(st.st_size);
  xt = strrchr(Path, '.');
  if (!xt) SetContentType(MT_Unknown);
  ++xt;

  // File response serves only simple files, like tiny webservers
  if (!strcasecmp("html", xt)) SetContentType(MT_Html);
  else if (!strcasecmp("css", xt)) SetContentType(MT_CSS);
  else if (!strcasecmp("js", xt)) SetContentType(MT_JavaScript);
  else if (!strcasecmp("ico", xt)) SetContentType(MT_Ico);
  else if (!strcasecmp("gif", xt)) SetContentType(MT_Gif);
  else if (!strcasecmp("png", xt)) SetContentType(MT_Png);
  else if (!strcasecmp("jpg", xt)) SetContentType(MT_Jpg);
  else if (!strcasecmp("jpeg", xt)) SetContentType(MT_Jpg);
  else if (!strcasecmp("dtd", xt)) SetContentType(MT_XmlDtd);
  else if (!strcasecmp("xml", xt)) SetContentType(MT_Xml);
}

size_t cHTTPFileResponse::ReadContentChunk(char* Buf, size_t bufSize)
{
  long rv = 0;

  if (fd < 1) {
     fd = open(RealPath(), O_RDONLY | O_LARGEFILE);
     if (fd < 1) {
        esyslog("could not open requested path %s - Error #%d", RealPath(), errno);
        return 0;
        }
     }
  isyslog("have filehandle #%d (%s)", fd, RealPath());
  if ((rv = read(fd, Buf, bufSize)) < 0)
     esyslog("ERROR: failed to read from file %s #%d", RealPath(), errno);
  else
     isyslog("read %u bytes from file", rv);
  if (rv < (long) bufSize) { // most probabely end of file
     close(fd);
     }
  return rv;
}

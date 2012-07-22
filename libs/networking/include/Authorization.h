/**
 * ======================== legal notice ======================
 * 
 * File:      Authorization.h
 * Created:   3. Juli 2012, 17
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
#ifndef AUTHORIZATION_H
#define	AUTHORIZATION_H

#include <HTTPRequest.h>
#include <Principal.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <ManagedVector.h>

class cAuthorization {
public:
  cAuthorization(const cHTTPRequest &OriginalRequest, char *NOnceFromHeap);
  cAuthorization(cHTTPRequest::HTTPRequestMethod Method, const char *Raw);
  cAuthorization(const cAuthorization &other);
  cAuthorization(const cPrincipal *Principal, cHTTPRequest::HTTPRequestMethod Method, const cAuthorization &other);
  virtual ~cAuthorization();
  cAuthorization &operator =(const cAuthorization &other);
  size_t Write(char *Buffer, size_t BufSize);
  const char *CalculateResponse(const char *Uri = NULL, const char *Username = NULL, const char *Password = NULL);
  void Dump(void) const;
  const char *Uri(void) const { return uri; }
  const char *Response(void) const { return response; }
  const char *CNOnce(void) const { return cnonce; }
  const char *NOnce(void) const { return nonce; }
  const char *Opaque(void) const { return opaque; }
  const char *UserID(void) const {
    if (principal) return principal->Name();
    else if (tmp) return tmp->Name();
    return NULL;
  }
  const char *UserCredential(void) const {
    if (principal) return principal->Hash();
    else if (tmp) return tmp->Hash();
    return NULL;
  }
  const char *Realm(void) const {
    if (principal) return principal->Realm();
    else if (tmp) return tmp->Realm();
    return NULL;
  }
  void SetUser(const char *UserID, const char *Password);
  char *CalculateA1(const char *Username = NULL, const char *Password = NULL);
  char *CalculateA2(const char *Uri);

protected:
  virtual void ParseRawBuffer(const char *Raw);
  virtual void CreateClientHash();
  const cPrincipal *Principal(void) const { return principal; }
  void SetAttribute(char *Name, const char *Value);
  void SetOpaque(char *Value);
  void SetPrincipal(const cPrincipal *Principal) { principal = Principal; }

private:
  void SetServerID(const char *ServerID) { free(serverID); serverID = ServerID ? strdup(ServerID) : NULL; }
  void SetUri(const char *Uri) { free(uri); uri = Uri ? strdup(Uri) : NULL; }
  cPrincipal *tmp;
  const cPrincipal *principal;
  cHTTPRequest::HTTPRequestMethod method;
  char *serverID;
  bool sessAlgo;
  char *nonce;
  char *uri;
  char *response;
  char *opaque;
  char *cnonce;
  char *qop;
  int counter;
  time_t authTime;
  friend class cHTTPResponse;
  friend class cHTTPRequest;
  friend class cAuthorizations;
  friend class cConnectionHandler;
  };

class cConnectionPoint;
class cAuthorizations : public cManagedVector {
public:
  cAuthorizations();
  virtual ~cAuthorizations();

  cAuthorization *FindAuthorization(const char *SessionID);
  void Del(cAuthorization *Auth2Invalidate);
  const cAuthorization &CreateAuthorization(const cHTTPRequest &OriginalRequest, const cConnectionPoint &client, unsigned long connectionNumber);
  static char *CreateNOnce(const cConnectionPoint &client, unsigned long connectionNumber);
  static char *CreateSessionID(const cHTTPRequest &OriginalRequest, time_t AuthTime);
  };

#endif	/* AUTHORIZATION_H */


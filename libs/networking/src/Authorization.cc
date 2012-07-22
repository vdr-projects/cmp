/**
 * ======================== legal notice ======================
 * 
 * File:      Authorization.cc
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
#include <Authorization.h>
#include <Credentials.h>
#include <MD5Calculator.h>
#include <Principal.h>
#include <ConnectionPoint.h>
#include <Logging.h>
#include <stdio.h>
#include <util.h>

static bool useSessionHash = true;

cAuthorization::cAuthorization(const cHTTPRequest &OriginalRequest, char *NOnceFromHeap)
///< use this constructor to create an authorization request for responses to
///< clients without valid authorization headers.
 : tmp(NULL)
 , principal(NULL)
 , method(OriginalRequest.Method())
 , serverID(NULL)
 , sessAlgo(useSessionHash)
 , nonce(NOnceFromHeap)
 , uri(OriginalRequest.Url().ToString())
 , response(NULL)
 , opaque(NULL)
 , cnonce(NULL)
 , qop(NULL)
 , counter(0)
 , authTime(time(NULL))
{
  tmp = new cPrincipal("unset", Credentials.ApplicationRealm());
  opaque = cAuthorizations::CreateSessionID(OriginalRequest, authTime);
}

cAuthorization::cAuthorization(cHTTPRequest::HTTPRequestMethod Method, const char *Raw)
///< use this constructor to create an authorization from clients request message
 : tmp(NULL)
 , principal(NULL)
 , method(Method)
 , serverID(NULL)
 , sessAlgo(false)
 , nonce(NULL)
 , uri(NULL)
 , response(NULL)
 , opaque(NULL)
 , cnonce(NULL)
 , qop(NULL)
 , counter(0)
{
  ParseRawBuffer(Raw);
}

cAuthorization::cAuthorization(const cPrincipal *Principal, cHTTPRequest::HTTPRequestMethod Method, const cAuthorization &other)
 : tmp(other.tmp ? new cPrincipal(*other.tmp) : NULL)
 , principal(Principal)
 , method(Method)
 , serverID(other.serverID ? strdup(other.serverID) : NULL)
 , sessAlgo(other.sessAlgo)
 , nonce(other.nonce ? strdup(other.nonce) : NULL)
 , uri(other.uri ? strdup(other.uri) : NULL)
 , response(other.response ? strdup(other.response) : NULL)
 , opaque(other.opaque ? strdup(other.opaque) : NULL)
 , cnonce(other.cnonce ? strdup(other.cnonce) : NULL)
 , qop(other.qop ? strdup(other.qop) : NULL)
 , counter(other.counter)
{
}

cAuthorization::cAuthorization(const cAuthorization& other)
 : tmp(other.tmp ? new cPrincipal(*other.tmp) : NULL)
 , principal(other.principal)
 , method(other.method)
 , serverID(other.serverID ? strdup(other.serverID) : NULL)
 , sessAlgo(other.sessAlgo)
 , nonce(other.nonce ? strdup(other.nonce) : NULL)
 , uri(other.uri ? strdup(other.uri) : NULL)
 , response(other.response ? strdup(other.response) : NULL)
 , opaque(other.opaque ? strdup(other.opaque) : NULL)
 , cnonce(other.cnonce ? strdup(other.cnonce) : NULL)
 , qop(other.qop ? strdup(other.qop) : NULL)
 , counter(other.counter + 1)
{
}

cAuthorization::~cAuthorization()
{
  if (tmp) delete tmp;
  FREE(nonce);
  FREE(uri);
  FREE(serverID);
  FREE(response);
  FREE(opaque);
  FREE(cnonce);
  FREE(qop);
}

cAuthorization& cAuthorization::operator=(const cAuthorization& other)
{
  if (&other == this) return *this;
  if (tmp) delete tmp;
  FREE(nonce);
  FREE(uri);
  FREE(serverID);
  FREE(response);
  FREE(opaque);
  FREE(cnonce);

  principal = other.principal;
  sessAlgo = other.sessAlgo;
  method = other.method;
  serverID = other.serverID ? strdup(other.serverID) : NULL;
  nonce = other.nonce ? strdup(other.nonce) : NULL;
  uri = other.uri ? strdup(other.uri) : NULL;
  response = other.response ? strdup(other.response) : NULL;
  opaque = other.opaque ? strdup(other.opaque) : NULL;
  cnonce = other.cnonce ? strdup(other.cnonce) : NULL;
  counter = other.counter;
  qop = other.qop ? strdup(other.qop) : NULL;
  tmp = other.tmp ? new cPrincipal(*other.tmp) : NULL;

  return *this;
}

void cAuthorization::CreateClientHash()
{
  cMD5Calculator hc;
  char buf[40];

  snprintf(buf, sizeof(buf), "%lu", random());

  hc.AddContent(serverID);
  hc.AddContent(":");
  hc.AddContent(buf);

  cnonce = hc.Hash();
}

static const char *getAttrName(char *buf, int bufSize, const char *src)
{
  const char *s = src;
  char *d = buf;

  while (*s && isspace(*s)) ++s;
  while (*s && ((d - buf) < bufSize) && *s != '=' && !isspace(*s)) *d++ = *s++;
  *d = 0;

  return *s ? s : NULL;
}

static const char *getValue(char *buf, int bufSize, const char *src)
{
  const char *s = src;
  char *d = buf;

  if (*s == '"') {
     ++s;
     while (*s && ((d - buf) < bufSize) && *s != '"') *d++ = *s++;
     if (*s != '"') return NULL;
     ++s;
     }
  else {
     while (*s && ((d - buf) < bufSize) && *s != ',') *d++ = *s++;
     }
  *d = 0;

  return *s ? s : NULL;
}

size_t cAuthorization::Write(char* Buffer, size_t BufSize)
{
  static const char *UnAuthorizedMask = "WWW-Authenticate: Digest realm=\"%s\", "
    "nonce=\"%s\", opaque=\"%s\", algorithm=\"MD5%s\", qop=\"auth\"\n";
  static const char *AuthorizedMask = "Authorization: Digest username=\"%s\", "
    "realm=\"%s\", nonce=\"%s\", uri=\"%s\", response=\"%s\", opaque=\"%s\", qop=\"auth\", nc=%08X, algorithm=\"MD5%s\", cnonce=\"%s\"";
  static const char *AuthenticationMaskDef = "Authentication-Info: qop=auth, nc=%08X, rspauth=\"%s\", cnonce=\"%s\"";
  static const char *AuthenticationMaskNew = "Authentication-Info: nextnounce=\"%s\", qop=auth, nc=%08X, rspauth=\"%s\", cnonce=\"%s\"";
  size_t n=0;

  if (principal && strcmp(principal->Name(), "unset")) {
     static bool timeout = 0;
     //TODO: authorization info, should be sent after certain timeout
     if (timeout) n = snprintf(Buffer, BufSize, AuthenticationMaskNew, nonce, counter, response, cnonce);
     else n = snprintf(Buffer, BufSize, AuthenticationMaskDef, counter, response, cnonce);
     }
  else if (!principal && tmp && tmp->Name() && tmp->Hash()) {
     n = snprintf(Buffer, BufSize, AuthorizedMask, tmp->Name(), tmp->Realm(), nonce, uri, response, opaque,
                  counter, sessAlgo ? "-sess" : "", cnonce);
     }
  else {
     n = snprintf(Buffer, BufSize, UnAuthorizedMask, Credentials.ApplicationRealm(), nonce, opaque, sessAlgo ? "-sess" : "");
     }
  return n;
}


// authorization is one line, so conforms to header value. Digest has been broken for readability
// Digest username="ich oder",
//    realm="Schnarcher@my.box",
//    nonce="59F980BB771C1CC31EE7360C7B06F15D",
//    uri="/favicon.ico",
//    response="7d060b3de37d132e2f4e4b014b127818",
//    opaque="33B9703065AD7E1A1DED1DFE07AA357C",
//    qop=auth,
//    nc=00000001,
//    cnonce="4dd872a6c6debac8"
void cAuthorization::ParseRawBuffer(const char* Raw)
{
  static const char *eyecatch = "Digest";

  if (strncmp(Raw, eyecatch, strlen(eyecatch))) {
//     esyslog("Authentication is not of type Digest! - not supported!");

     return;
     }
  char nameBuf[30];
  char scratch[128];
  const char *p = Raw + strlen(eyecatch);
  bool done=false;

  if (tmp) {
     delete tmp;
     tmp = NULL;
     }
  while (!done) {
        p = getAttrName(nameBuf, sizeof(nameBuf), p);
        if (*p != '=') {
           esyslog("invalid digest format! Expected '=' and found %C (%02X)", *p, *p);
           return;
           }
        p = getValue(scratch, sizeof(scratch), ++p);
        SetAttribute(nameBuf, scratch);

        if (!p) break;
        if (*p != ',') break;
        else ++p;
        }
}

void cAuthorization::SetUser(const char *UserID, const char *Password)
{
  if (principal) {
     //TODO: do we really want to support change of user/password on existing principal?
     }
  else if (tmp) {
     tmp->SetName(UserID);
     tmp->CreateHash(Password);
     CreateClientHash();
     }
}

void cAuthorization::SetAttribute(char* Name, const char* Value)
{
  char **p = NULL;

//  isyslog("cAuthorization::SetAttribute(\"%s\") => [%s]", Name, Value);
  if (!strcasecmp(Name, "username")) {
     if (!tmp) tmp = new cPrincipal(Value, "unset");
     else tmp->SetName(Value);
     }
  else if (!strcasecmp(Name, "realm")) {
     if (!tmp) tmp = new cPrincipal("unset", Value);
     else tmp->SetRealm(Value);
     }
  else if (!strcasecmp(Name, "algorithm")) {
     if (!strcmp("MD5-sess", Value)) sessAlgo = true;
     }
  else if (!strcasecmp(Name, "nonce")) p = &nonce;
  else if (!strcasecmp(Name, "uri")) p = &uri;
  else if (!strcasecmp(Name, "response")) p = &response;
  else if (!strcasecmp(Name, "opaque")) p = &opaque;
  else if (!strcasecmp(Name, "cnonce")) p = &cnonce;
  else if (!strcasecmp(Name, "qop")) {
     if (!strncmp(Value, "auth", 4)) p = &qop;
     else esyslog("invalid/unsupported auth method! - only \"auth\" supported!");
     }
  else if (!strcasecmp(Name, "nc")) {
     counter = strtol(Value, NULL, 16);
     }
  if (p) {
     free(*p);
     *p = strdup(Value);
     }
  if (tmp) {
     principal = Credentials.FindPrincipal(tmp->Name(), tmp->Realm());
     if (principal) {
        delete tmp;
        tmp = NULL;
        }
     }
}

char * cAuthorization::CalculateA1(const char *Username, const char *Password)
{
  if (Username && Password) SetUser(Username, Password);
  char *principalHash = (char *) (principal ? principal->Hash() : tmp->Hash());

  if (sessAlgo) {
     cMD5Calculator hc;

     hc.AddContent(principalHash);
     hc.AddContent(":");
     hc.AddContent(nonce);
     hc.AddContent(":");
     hc.AddContent(cnonce);

     return hc.Hash();
     }
  return strdup(principalHash);
}

char * cAuthorization::CalculateA2(const char *Uri)
{
  cMD5Calculator hc;

  // don't send method on authorized response
  if (!principal || strcmp(principal->Name(), "unset")) hc.AddContent(requestMethod2String(method));
  hc.AddContent(":");
  hc.AddContent(Uri);

  return hc.Hash();
}

const char * cAuthorization::CalculateResponse(const char *Uri, const char *Username, const char *Password)
{
  free(response);
  char *a1 = CalculateA1(Username, Password);
  char *a2 = CalculateA2(Uri ? Uri : uri);
  cMD5Calculator hc;
  char buf[12];

  snprintf(buf, sizeof(buf), "%08x", counter);
  hc.AddContent(a1);
  hc.AddContent(":");
  hc.AddContent(nonce);
  if (qop) {
     hc.AddContent(":");
     hc.AddContent(buf);
     hc.AddContent(":");
     hc.AddContent(cnonce);
     hc.AddContent(":");
     hc.AddContent(qop);
     }
  hc.AddContent(":");
  hc.AddContent(a2);

  response = hc.Hash();

//  printf("CalculateResponse: Realm-Digest (A1) =>%s<\n", a1);
//  printf("CalculateResponse: URL-Digest   (A2) =>%s<\n", a2);
//  printf("CalculateResponse: Request-Digest    =>%s<\n", response);

  free(a1);
  free(a2);

  return response;
}

void cAuthorization::Dump(void) const
{
  printf(">>>---------- Authorization ------------------\n");
  if (principal) principal->Dump();
  else if (tmp) tmp->Dump();
  else printf("principal is NULL\n");
  printf("nonce ...: >%s<\n", nonce);
  printf("method ..: >%s<\n", requestMethod2String(method));
  printf("uri .....: >%s<\n", uri);
  printf("response : >%s<\n", response);
  printf("opaque ..: >%s<\n", opaque);
  printf("cnonce ..: >%s<\n", cnonce);
  printf("counter .: >%d<\n", counter);
  printf("============= Authorization ===============<<<\n");
}

// --- Authorizations ---------------------------------------------------------

static void freeAuthorizationCallback(void *elem)
{
  delete (cAuthorization *)elem;
}

cAuthorizations::cAuthorizations()
 : cManagedVector(freeAuthorizationCallback)
{
}

cAuthorizations::~cAuthorizations()
{
}

cAuthorization *cAuthorizations::FindAuthorization(const char *SessionID)
{
  cAuthorization *a;

  for (size_t i=0; i < size(); ++i) {
      a = (cAuthorization *) (*this)[i];
      if (!strcmp(a->Opaque(), SessionID)) return a;
      }
  return NULL;
}

const cAuthorization &cAuthorizations::CreateAuthorization(const cHTTPRequest &originalRequest, const cConnectionPoint &client, unsigned long connectionNumber)
{
  cAuthorization *rv = new cAuthorization(originalRequest, CreateNOnce(client, connectionNumber));

  push_back(rv);

  return *rv;
}

char *cAuthorizations::CreateNOnce(const cConnectionPoint &client, unsigned long connectionNumber)
{
  char buf[40];
  cMD5Calculator hc;

  snprintf(buf, sizeof(buf), "%lu:%lu", connectionNumber, random());

  hc.AddContent(buf);
  hc.AddContent(":");
  hc.AddContent(client.HostName());

  return hc.Hash();
}

char *cAuthorizations::CreateSessionID(const cHTTPRequest &OriginalRequest, time_t AuthTime)
{
  char buf[40];
  cMD5Calculator hc;
  const char *p0, *p1;

  snprintf(buf, sizeof(buf), "%lu", AuthTime);

  p0 = OriginalRequest.ClientHost();
  p1 = OriginalRequest.UserAgent();

  hc.AddContent(p0 ? p0 : "localhost");
  hc.AddContent(":");
  hc.AddContent(buf);
  hc.AddContent(":");
  hc.AddContent(p1 ? p1 : "unknown");

  return hc.Hash();
}

void cAuthorizations::Del(cAuthorization *Auth2Invalidate)
{
//TODO:
}
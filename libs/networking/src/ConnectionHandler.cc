/**
 * ======================== legal notice ======================
 * 
 * File:      ConnectionHandler.cc
 * Created:   4. Juli 2012, 07:32
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
#include <ConnectionHandler.h>
#include <ServerSocket.h>
#include <HTTPRequest.h>
#include <HTTPFileResponse.h>
#include <HTTPAuthorizationRequest.h>
#include <HTTPRequestHandler.h>
#include <Authorization.h>
#include <Credentials.h>
#include <MD5Calculator.h>
#include <StringBuilder.h>
#include <TimeMs.h>
#include <Logging.h>
#include <util.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <iostream>
#include <tr1/unordered_map>

static unsigned long connectionCounter = 0;
class cHTTPRequestHandlers {
public:
  typedef std::tr1::unordered_map<std::string, cHTTPRequestHandler *>::iterator iterator;
  cHTTPRequestHandlers();
  ~cHTTPRequestHandlers();

  cHTTPRequestHandler *Handler(const char *UrlPrefix);
  void SetHandler(const char *UrlPrefix, cHTTPRequestHandler *Handler);
  cHTTPRequestHandler *DefaultHandler(void) { return defaultHandler; }
  void SetDefaultHandler(cHTTPRequestHandler *Handler) { defaultHandler = Handler; }

  cHTTPRequestHandlers::iterator begin() { return internalMap.begin(); }
  cHTTPRequestHandlers::iterator end() { return internalMap.end(); }

private:
  cHTTPRequestHandler *defaultHandler;
  std::tr1::unordered_map<std::string, cHTTPRequestHandler *> internalMap;
  };

cHTTPRequestHandlers::cHTTPRequestHandlers()
 : defaultHandler(NULL)
{
}

cHTTPRequestHandlers::~cHTTPRequestHandlers()
{
  cHTTPRequestHandlers::iterator it = internalMap.begin();

  while (it != internalMap.end()) {
        delete it->second;
        ++it;
        }
  if (defaultHandler) delete defaultHandler;
}

cHTTPRequestHandler *cHTTPRequestHandlers::Handler(const char* UrlPrefix)
{
  cHTTPRequestHandlers::iterator it = internalMap.find(UrlPrefix);

  if (it == internalMap.end()) return NULL;
  return it->second;
}

void cHTTPRequestHandlers::SetHandler(const char* UrlPrefix, cHTTPRequestHandler* Handler)
{
  Handler->SetID(UrlPrefix);
  internalMap[UrlPrefix] = Handler;
}
static cHTTPRequestHandlers registeredHandlers;

cConnectionHandler::cConnectionHandler(cConnectionPoint &Client, cServerConfig &Config, bool StayConnected)
 : config(Config)
 , client(Client)
 , connectionNumber(++connectionCounter)
 , bufSize(2048)
 , scratch(NULL)
 , nonce(NULL)
 , stayConnected(StayConnected)
{
}

cConnectionHandler::~cConnectionHandler()
{
  Cancel();
}

void cConnectionHandler::Action()
{
  if (!scratch) scratch = (char *)malloc(bufSize);
  if (!scratch) {
     esyslog("failed to allocate scratch buffer of size %ld", bufSize);
     return;
     }
  cHTTPRequest *request;
  cHTTPResponse *response = NULL;
  uint64_t start, end;
  size_t nTrans;

  isyslog("ConnectionHandler::Action() - start the loop");
  while (Running()) {
        memset(scratch, 0, bufSize);

        // process at least one request
        isyslog("read next request from Client");
        nTrans = read(client.Socket(), scratch, bufSize);
        if (nTrans < 1) {
           esyslog("failed to read client-Request! End of this connection handler ... #%d", errno);
           return;
           }
        start = cTimeMs::Now();
        if (nTrans == bufSize) {
           char *p = scratch + nTrans;

           bufSize += 2048;
           scratch = (char *) realloc(scratch, bufSize);
           nTrans += read(client.Socket(), p, 2048);

           //TODO: should we support multiple buffer resize?
           if (nTrans == bufSize) {
              esyslog("OUPS - buffer overflow? - Lets stop this connection handler ...");
              return;
              }
           }
        isyslog("#%lu - got client request |>%s<|", connectionNumber, scratch);

        request = new cHTTPRequest(scratch);
        if (!request) {
           esyslog("ERROR: failed to parse request from client!");
           response = new cHTTPResponse(HTTP_NotAcceptable);
           }
        else {
           isyslog("got request from client       (%ld bytes)       %s", nTrans, request->Url().Path());

           if (AuthorizationRequired()) {
              if (request->Authorization()) {
                 char *url = request->Url().ToString();

                 for (EVER) {
                     //TODO: 1, check uri from request against uri from auth
                     if (strcmp(request->Authorization()->Uri(), url)) {
                        esyslog("ATTENTION - security attack! URI mismatch between request and authorization header!");
                        response = new cHTTPResponse(HTTP_BadRequest);
                        break;
                        }

                     //TODO: 2. search user/principal
                     cAuthorization *auth = Authorizations().FindAuthorization(request->Authorization()->Opaque());

                     if (!auth) {
                        response = new cHTTPAuthorizationRequest(Authorizations().CreateAuthorization(*request, client, connectionNumber));
                        esyslog("Huh? - didn't find a matching authorization, but client sent authorization header. Something went wrong!");
                        break;
                        }

                     //TODO: 3. check auth->principal->hash against hash from found principal
                     if (IsAuthorizationValid(auth, *request))
                        response = ProcessRequest(*request);
                     if (!response) {
                        //TODO: 406 or should we create a new authorization request?
                        response = new cHTTPResponse(HTTP_NotAcceptable);
                        }
                     break;
                     }
                 free(url);
                 }
              else {
                 //TODO: create authorization request
                 response = new cHTTPAuthorizationRequest(Authorizations().CreateAuthorization(*request, client, connectionNumber));
                 }
              }
           else response = ProcessRequest(*request);
           }
        TransferResponse(response);
        delete response;
        delete request;
        response = NULL;
        request = NULL;
        end = cTimeMs::Now();
        isyslog("processing of request took %ld ms.", (end - start));

        isyslog("check IO status ...");
        if (!client.IOWait(500)) {
           if (!StayConnected()) {
              isyslog("         >>> connection timed out without any data <<<");
              break; // leave temporary connections after timeout
              }
           }
        }
  Cancel();
}

void cConnectionHandler::Cancel(int WaitSeconds)
{
  dsyslog("Ok, lets close the client socket ...");
  client.Close();
  FREE(scratch);
  FREE(nonce);
}

bool cConnectionHandler::IsAuthorizationValid(cAuthorization *ServerAuth, const cHTTPRequest &request)
{
  // Auth is the authorization based on opaque value from request->auth (session-ID)
  // check other values from auth/request too
  const cAuthorization *ClientAuth = request.Authorization();
  const cPrincipal *principal = ServerAuth->Principal();

  if (!principal || !strcmp(ServerAuth->UserID(), "unset"))
     principal = Credentials.FindPrincipal(ClientAuth->UserID(), ClientAuth->Realm());

  for (EVER) {
      if (!principal) {
         esyslog("username or realm is unknown");
         break;
         }
      if (strcmp(ClientAuth->UserID(), principal->Name()) || strcmp(ClientAuth->Realm(), principal->Realm())) {
         esyslog("username or realm did not match authenticated session");
         break;
         }
      if (strcmp(principal->Hash(), ClientAuth->UserCredential())) {
         esyslog("password given was invalid");
         break;
         }
      cAuthorization *authCheck = new cAuthorization(principal, request.Method(), *ClientAuth);
      const char *authHash = authCheck->CalculateResponse();

      if (strcmp(authHash, ClientAuth->Response())) {
         delete authCheck;
         break;
         }

      if (strcmp(ServerAuth->UserID(), principal->Name())) {
         // validation passed, so remember authorized user
         ServerAuth->SetPrincipal(principal);
         }
      delete authCheck;

      return true;
      }
  // validation of authorization failed, so remove any existing authorization from this session
  Authorizations().Del(ServerAuth);

  return false;
}

cHTTPResponse *cConnectionHandler::ProcessRequest(cHTTPRequest &Request)
{
  cHTTPResponse *res = NULL;

  isyslog("ConnectionHandler::ProcessRequest: %s", Request.Url().Path());
  if (!strcmp(Request.Url().Path(), "/stop")) {
      ServerSocket().SetActive(false);
      res = new cHTTPResponse(HTTP_Gone);
      }
  else if (!strcmp(Request.Url().Path(), "/favicon.ico")) {
      res = new cHTTPFileResponse(config.AppIconPath());
      }
  else if (!strcmp(Request.Url().Path(), "/help")) {
      cHTTPResponse *ir = new cHTTPResponse();

      isyslog("start assembling usage message ...");
      Usage(ir->StringBuilder());

      ir->StringBuilder().Append("<hr>").Append(ir->ServerID()).Append(" ").Append(config.DocumentRoot());
      isyslog("assembling of usage message done - let's send it to client ...");
      ir->SetContentType("text/html");
      ir->SetContentSize(ir->StringBuilder().Size());
      res = ir;
      }
  else {
     cHTTPRequestHandler *rh = registeredHandlers.Handler(Request.Url().Path());

     if (rh) res = rh->ProcessRequest(Request);
     if (!rh || !res) {
        rh = registeredHandlers.DefaultHandler();

        if (rh) res = rh->ProcessRequest(Request);
        }
     }
  if (!res) res = new cHTTPResponse(HTTP_NotFound);

  return res;
}

void cConnectionHandler::Usage(cStringBuilder& sb)
{
  cHTTPRequestHandlers::iterator it = registeredHandlers.begin();

  isyslog("start of cConnectionHandler::Usage() ...");
  sb.Append("<h2>Media server</h2><p>serves media files to remote/client media-players. Those ");
  sb.Append("media-player should support the http-protocol. Opposed to well known http-servers, this ");
  sb.Append("server handles multifile media transparently for the client.</p>");
  sb.Append("<h3>supported requests:</h3>");
  sb.Append("<dl>");

  while (it != registeredHandlers.end()) {
        sb.Append("<dt><br/><em>");
        sb.Append(it->first.c_str());
        sb.Append("</em></dt><dd>");
        it->second->Usage(sb);
        sb.Append("</dd>");
        ++it;
        }
  if (registeredHandlers.DefaultHandler()) {
     sb.Append("<dt><br/><em>");
     sb.Append("default");
     sb.Append("</em></dt><dd>");
     registeredHandlers.DefaultHandler()->Usage(sb);
     sb.Append("</dd>");
     sb.Append("</dl>");
     }
  isyslog("end of cConnectionHandler::Usage() ...");
}

void cConnectionHandler::TransferResponse(cHTTPResponse *Response)
{
  if (!Response) {
     esyslog("OUPS - should not happen!!! - Response was empty!");
     close(client.Socket());

     return;
     }
//#ifdef DEBUG
//  static int responseCounter = 0;
//  char filename[64] = {0};
//  sprintf(filename, "/tmp/rednose%03d", ++responseCounter);
//#endif

  memset(scratch, 0, bufSize);

//#ifdef DEBUG
//  int fdClient = open(filename, O_WRONLY | O_CREAT);
//#else
  int fdClient = client.Socket();
//#endif
  isyslog("gonna sent message to client (Socket #%d)", fdClient);

  int nRaw = Response->WritePrefix(scratch, bufSize);
  int nTrans = send(fdClient, scratch, nRaw, MSG_NOSIGNAL);
  size_t total = 0;

  if (nTrans != nRaw) esyslog("ERROR: failed to transmit response header! (%d <> %d)", nRaw, nTrans);
  while ((nRaw = Response->ReadContentChunk(scratch, bufSize)) > 0) {
        int nTrans = send(fdClient, scratch, nRaw, MSG_NOSIGNAL);

        if (nTrans < 1) {
           esyslog("failed to transmit chunk. Error #%d", errno);
           break;
           }
        total += nTrans;
        if (nTrans == nRaw) isyslog("successfully written message chunk of %d bytes", nTrans);
        else esyslog("failed to transmit response chunk (%d <> %d)", nRaw, nTrans);
        }
  if (total != Response->ContentSize())
     esyslog("failed to transfer response - should be %ld, was %ld", Response->ContentSize(), total);
//#ifdef DEBUG
//  close(fdClient);
//#endif
}

void cConnectionHandler::RegisterDefaultHandler(cHTTPRequestHandler *DefaultHandler)
{
  registeredHandlers.SetDefaultHandler(DefaultHandler);
}

void cConnectionHandler::RegisterRequestHandler(const char *UrlPrefix, cHTTPRequestHandler *RequestHandler)
{
  registeredHandlers.SetHandler(UrlPrefix, RequestHandler);
}

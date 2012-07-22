/**
 * ======================== legal notice ======================
 * 
 * File:      CommandHandler.cc
 * Created:   5. Juli 2012, 16
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
#include <CommandHandler.h>
#include <tr1/unordered_map>
#include <HTTPRequest.h>
#include <HTTPResponse.h>
#include <StringBuilder.h>
#include <Logging.h>

typedef struct {
  CommandCallback callback;
  void *opaque;
} CallbackInfo;
std::tr1::unordered_map<std::string, CallbackInfo *> supportedCommands;


cCommandHandler::cCommandHandler()
{
}

cCommandHandler::~cCommandHandler()
{
}

void cCommandHandler::Cleanup()
{
  std::tr1::unordered_map<std::string, CallbackInfo *>::iterator it = supportedCommands.begin();

  while (it != supportedCommands.end()) {
        free(it->second);
        ++it;
        }
}

cHTTPResponse *cCommandHandler::ProcessRequest(cHTTPRequest& Request)
{
  const char *command = Request.GetHeader("what");
  CallbackInfo *info;

  isyslog("cCommandHandler::ProcessRequest ...");
  if (!command) {
     esyslog("ERROR: no command in request");
     return new cHTTPResponse(HTTP_BadRequest);
     }
  info = supportedCommands[command];
  if (!info) {
     esyslog("ERROR: command not registered/supported!");
     return new cHTTPResponse(HTTP_BadRequest);
     }
  if ((*info->callback)(info->opaque, Request)) {
     esyslog("ERROR: failed to execute command!");
     return new cHTTPResponse(HTTP_InternalServerError);
     }
  isyslog("OK - all went well?!?");

  return new cHTTPResponse(HTTP_NoContent);
}

void cCommandHandler::Usage(cStringBuilder &sb)
{

}

void cCommandHandler::RegisterCallback(const char* CommandID, CommandCallback cb, void* opaque)
{
  CallbackInfo *info = (CallbackInfo *)malloc(sizeof(CallbackInfo));

  info->callback = cb;
  info->opaque = opaque;
  supportedCommands[CommandID] = info;
}


/**
 * ======================== legal notice ======================
 * 
 * File:      HTTPStatus.h
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
#ifndef HTTPSTATUS_H
#define	HTTPSTATUS_H

typedef enum {
  HTTP_Continue = 100
, HTTP_SwitchProtocol = 101
, HTTP_OK = 200
, HTTP_Created = 201
, HTTP_Accepted = 202
, HTTP_NoContent = 204
, HTTP_ResetContent = 205
, HTTP_PartialContent = 206
, HTTP_MultipleChoices = 300
, HTTP_MovedPermanently = 301
, HTTP_Found = 302
, HTTP_SeeOther = 303
, HTTP_NotModified = 304
, HTTP_UseProxy = 305
, HTTP_MovedTemporarily = 307
, HTTP_BadRequest = 400
, HTTP_UnAuthorized = 401
, HTTP_PaymentRequired = 402
, HTTP_Forbidden = 403
, HTTP_NotFound = 404
, HTTP_MethodNotAllowed = 405
, HTTP_NotAcceptable = 406
, HTTP_ProxyAuthenticationRequired = 407
, HTTP_RequestTimeout = 408
, HTTP_Conflict = 409
, HTTP_Gone = 410
, HTTP_LengthRequired = 411
, HTTP_PreconditionFailed = 412
, HTTP_RequestTooLarge = 413
, HTTP_RequestURIToLong = 414
, HTTP_UnsupportedMediaType = 415
, HTTP_RequestRangeNotSatisfiable = 416
, HTTP_ExpectationFailed = 417
, HTTP_InternalServerError = 500
, HTTP_NotImplemented = 501
, HTTP_BadGateway = 502
, HTTP_ServiceUnavailable = 503
, HTTP_GatewayTimeout = 504
, HTTP_VersionNotSupported = 505
  } HTTPStatusCode;

extern const char *httpStatus2Text(int Status);
extern HTTPStatusCode strtoHTTPStatus(const char *p);

#endif	/* HTTPSTATUS_H */


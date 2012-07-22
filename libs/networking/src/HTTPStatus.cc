/**
 * ======================== legal notice ======================
 * 
 * File:      HTTPStatus.cc
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
#include <HTTPStatus.h>
#include <stdlib.h>

const char *httpStatus2Text(int Status)
{
  switch (Status) {
    case HTTP_Continue: return "Continue";
    case HTTP_SwitchProtocol: return "Gonna switch Protocol";
    case HTTP_OK: return "Ok";
    case HTTP_Created: return "Created";
    case HTTP_Accepted: return "Accepted";
    case HTTP_NoContent: return "No Content";
    case HTTP_ResetContent: return "reset Content";
    case HTTP_PartialContent: return "partial Content";
    case HTTP_MultipleChoices: return "Multiple Choices";
    case HTTP_MovedPermanently: return "Permanently moved";
    case HTTP_Found: return "Found";
    case HTTP_SeeOther: return "See other";
    case HTTP_NotModified: return "Not modified";
    case HTTP_UseProxy: return "Use Proxy";
    case HTTP_MovedTemporarily: return "Temporarily moved";
    case HTTP_BadRequest: return "Bad Request";
    case HTTP_UnAuthorized: return "Unauthorized";
    case HTTP_PaymentRequired: return "Payment required";
    case HTTP_Forbidden: return "Forbidden";
    case HTTP_NotFound: return "Not Found";
    case HTTP_MethodNotAllowed: return "Not Allowed";
    case HTTP_NotAcceptable: return "Not acceptable";
    case HTTP_ProxyAuthenticationRequired: return "Authentication required";
    case HTTP_RequestTimeout: return "Request timed out";
    case HTTP_Conflict: return "Conflict";
    case HTTP_Gone: return "Gone";
    case HTTP_LengthRequired: return "Length required";
    case HTTP_PreconditionFailed: return "Precondition failed";
    case HTTP_RequestTooLarge: return "Request too large";
    case HTTP_RequestURIToLong: return "Requested URI to long";
    case HTTP_UnsupportedMediaType: return "Unsupported Media Type";
    case HTTP_RequestRangeNotSatisfiable: return "Request Range Not satisfiable";
    case HTTP_ExpectationFailed: return "Expectation failed";
    case HTTP_InternalServerError: return "Internal Server Error";
    case HTTP_NotImplemented: return "Not implemented";
    case HTTP_BadGateway: return "Bad Gateway";
    case HTTP_ServiceUnavailable: return "Service unavailable";
    case HTTP_GatewayTimeout: return "Gateway timed out";
    case HTTP_VersionNotSupported: return "Version not supported";
    default: return "Unsupported/Unknown status";
    }
}

HTTPStatusCode strtoHTTPStatus(const char *p)
{
  int tmp = atoi(p);

  switch (tmp) {
    case HTTP_Continue: return HTTP_Continue;
    case HTTP_SwitchProtocol: return HTTP_SwitchProtocol;
    case HTTP_OK: return HTTP_OK;
    case HTTP_Created: return HTTP_Created;
    case HTTP_Accepted: return HTTP_Accepted;
    case HTTP_NoContent: return HTTP_NoContent;
    case HTTP_ResetContent: return HTTP_ResetContent;
    case HTTP_PartialContent: return HTTP_PartialContent;
    case HTTP_MultipleChoices: return HTTP_MultipleChoices;
    case HTTP_MovedPermanently: return HTTP_MovedPermanently;
    case HTTP_Found: return HTTP_Found;
    case HTTP_SeeOther: return HTTP_SeeOther;
    case HTTP_NotModified: return HTTP_NotModified;
    case HTTP_UseProxy: return HTTP_UseProxy;
    case HTTP_MovedTemporarily: return HTTP_MovedTemporarily;
    case HTTP_BadRequest: return HTTP_BadRequest;
    case HTTP_UnAuthorized: return HTTP_UnAuthorized;
    case HTTP_PaymentRequired: return HTTP_PaymentRequired;
    case HTTP_Forbidden: return HTTP_Forbidden;
    case HTTP_NotFound: return HTTP_NotFound;
    case HTTP_MethodNotAllowed: return HTTP_MethodNotAllowed;
    case HTTP_NotAcceptable: return HTTP_NotAcceptable;
    case HTTP_ProxyAuthenticationRequired: return HTTP_ProxyAuthenticationRequired;
    case HTTP_RequestTimeout: return HTTP_RequestTimeout;
    case HTTP_Conflict: return HTTP_Conflict;
    case HTTP_Gone: return HTTP_Gone;
    case HTTP_LengthRequired: return HTTP_LengthRequired;
    case HTTP_PreconditionFailed: return HTTP_PreconditionFailed;
    case HTTP_RequestTooLarge: return HTTP_RequestTooLarge;
    case HTTP_RequestURIToLong: return HTTP_RequestURIToLong;
    case HTTP_UnsupportedMediaType: return HTTP_UnsupportedMediaType;
    case HTTP_RequestRangeNotSatisfiable: return HTTP_RequestRangeNotSatisfiable;
    case HTTP_ExpectationFailed: return HTTP_ExpectationFailed;
    case HTTP_InternalServerError: return HTTP_InternalServerError;
    case HTTP_NotImplemented: return HTTP_NotImplemented;
    case HTTP_BadGateway: return HTTP_BadGateway;
    case HTTP_ServiceUnavailable: return HTTP_ServiceUnavailable;
    case HTTP_GatewayTimeout: return HTTP_GatewayTimeout;
    case HTTP_VersionNotSupported: return HTTP_VersionNotSupported;
    default: return HTTP_InternalServerError;
    }
}


/****************************************************************************************************************************
  Portenta_H7_AsyncWebServer.cpp - Dead simple AsyncWebServer for STM32 LAN8720 or built-in LAN8742A Ethernet

  For Portenta_H7 (STM32H7) with Vision-Shield Ethernet or Murata WiFi

  Portenta_H7_AsyncWebServer is a library for the Portenta_H7 with Vision-Shield Ethernet or Murata WiFi

  Based on and modified from ESPAsyncWebServer (https://github.com/me-no-dev/ESPAsyncWebServer)
  Built by Khoi Hoang https://github.com/khoih-prog/Portenta_H7_AsyncWebServer
  Licensed under GPLv3 license

  Version: 1.5.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      06/10/2021 Initial coding for Portenta_H7 (STM32H7) with Vision-Shield Ethernet
  1.1.0   K Hoang      08/10/2021 Add support to Portenta_H7 (STM32H7) using Murata WiFi
  1.1.1   K Hoang      12/10/2021 Update `platform.ini` and `library.json`
  1.2.0   K Hoang      07/12/2021 Fix crashing issue
  1.2.1   K Hoang      12/01/2022 Fix authenticate issue caused by libb64
  1.3.0   K Hoang      26/09/2022 Fix issue with slow browsers or network
  1.4.0   K Hoang      02/10/2022 Option to use cString instead og String to save Heap
  1.4.1   K Hoang      04/10/2022 Don't need memmove(), String no longer destroyed
  1.4.2   K Hoang      10/11/2022 Add examples to demo how to use beginChunkedResponse() to send in chunks
  1.5.0   K Hoang      30/01/2023 Fix _catchAllHandler not working bug
 *****************************************************************************************************************************/

#if !defined(_PORTENTA_H7_AWS_LOGLEVEL_)
  #define _PORTENTA_H7_AWS_LOGLEVEL_     1
#endif

#include "Portenta_H7_AsyncWebServer_Debug.h"

#include "Portenta_H7_AsyncWebServer.h"
#include "Portenta_H7_AsyncWebHandlerImpl.h"

/////////////////////////////////////////////////

AsyncWebServer::AsyncWebServer(uint16_t port)
  : _server(port), _rewrites(LinkedList<AsyncWebRewrite * >([](AsyncWebRewrite * r)
{
  delete r;
}))
, _handlers(LinkedList<AsyncWebHandler*>([](AsyncWebHandler* h)
{
  delete h;
}))
{
  _catchAllHandler = new AsyncCallbackWebHandler();

  if (_catchAllHandler == NULL)
    return;

  _server.onClient([](void *s, AsyncClient * c)
  {
    if (c == NULL)
      return;

    // KH set no RxTimeout for slower Firefox / network
    //c->setRxTimeout(3);
    c->setRxTimeout(0);
    //////

    AsyncWebServerRequest *r = new AsyncWebServerRequest((AsyncWebServer*)s, c);

    if (r == NULL)
    {
      c->close(true);
      c->free();
      delete c;
    }
  }, this);
}

/////////////////////////////////////////////////

AsyncWebServer::~AsyncWebServer()
{
  reset();
  end();

  if (_catchAllHandler)
    delete _catchAllHandler;
}

/////////////////////////////////////////////////

AsyncWebRewrite& AsyncWebServer::addRewrite(AsyncWebRewrite* rewrite)
{
  _rewrites.add(rewrite);

  return *rewrite;
}

/////////////////////////////////////////////////

bool AsyncWebServer::removeRewrite(AsyncWebRewrite *rewrite)
{
  return _rewrites.remove(rewrite);
}

/////////////////////////////////////////////////

AsyncWebRewrite& AsyncWebServer::rewrite(const char* from, const char* to)
{
  return addRewrite(new AsyncWebRewrite(from, to));
}

/////////////////////////////////////////////////

AsyncWebHandler& AsyncWebServer::addHandler(AsyncWebHandler* handler)
{
  _handlers.add(handler);
  return *handler;
}

/////////////////////////////////////////////////

bool AsyncWebServer::removeHandler(AsyncWebHandler *handler)
{
  return _handlers.remove(handler);
}

/////////////////////////////////////////////////

void AsyncWebServer::begin()
{
  _server.setNoDelay(true);
  _server.begin();
}

/////////////////////////////////////////////////

void AsyncWebServer::end()
{
  _server.end();
}

/////////////////////////////////////////////////

#if ASYNC_TCP_SSL_ENABLED

void AsyncWebServer::onSslFileRequest(AcSSlFileHandler cb, void* arg)
{
  _server.onSslFileRequest(cb, arg);
}

/////////////////////////////////////////////////

void AsyncWebServer::beginSecure(const char *cert, const char *key, const char *password)
{
  _server.beginSecure(cert, key, password);
}

#endif

/////////////////////////////////////////////////

void AsyncWebServer::_handleDisconnect(AsyncWebServerRequest *request)
{
  delete request;
}

/////////////////////////////////////////////////

void AsyncWebServer::_rewriteRequest(AsyncWebServerRequest *request)
{
  for (const auto& r : _rewrites)
  {
    if (r->match(request))
    {
      request->_url = r->toUrl();
      request->_addGetParams(r->params());
    }
  }
}

/////////////////////////////////////////////////

void AsyncWebServer::_attachHandler(AsyncWebServerRequest *request)
{
  for (const auto& h : _handlers)
  {
    if (h->filter(request) && h->canHandle(request))
    {
      request->setHandler(h);

      return;
    }
  }

  request->addInterestingHeader("ANY");

  request->setHandler(_catchAllHandler);
}

/////////////////////////////////////////////////

AsyncCallbackWebHandler& AsyncWebServer::on(const char* uri, WebRequestMethodComposite method,
                                            ArRequestHandlerFunction onRequest,
                                            ArUploadHandlerFunction onUpload, ArBodyHandlerFunction onBody)
{
  AsyncCallbackWebHandler* handler = new AsyncCallbackWebHandler();

  handler->setUri(uri);
  handler->setMethod(method);
  handler->onRequest(onRequest);
  handler->onUpload(onUpload);
  handler->onBody(onBody);
  addHandler(handler);

  return *handler;
}

/////////////////////////////////////////////////

AsyncCallbackWebHandler& AsyncWebServer::on(const char* uri, WebRequestMethodComposite method,
                                            ArRequestHandlerFunction onRequest, ArUploadHandlerFunction onUpload)
{
  AsyncCallbackWebHandler* handler = new AsyncCallbackWebHandler();
  handler->setUri(uri);
  handler->setMethod(method);
  handler->onRequest(onRequest);
  handler->onUpload(onUpload);
  addHandler(handler);

  return *handler;
}

/////////////////////////////////////////////////

AsyncCallbackWebHandler& AsyncWebServer::on(const char* uri, WebRequestMethodComposite method,
                                            ArRequestHandlerFunction onRequest)
{
  AsyncCallbackWebHandler* handler = new AsyncCallbackWebHandler();
  handler->setUri(uri);
  handler->setMethod(method);
  handler->onRequest(onRequest);
  addHandler(handler);

  return *handler;
}

/////////////////////////////////////////////////

AsyncCallbackWebHandler& AsyncWebServer::on(const char* uri, ArRequestHandlerFunction onRequest)
{
  AsyncCallbackWebHandler* handler = new AsyncCallbackWebHandler();
  handler->setUri(uri);
  handler->onRequest(onRequest);
  addHandler(handler);

  return *handler;
}

/////////////////////////////////////////////////

void AsyncWebServer::onNotFound(ArRequestHandlerFunction fn)
{
  _catchAllHandler->onRequest(fn);
}

/////////////////////////////////////////////////

void AsyncWebServer::onRequestBody(ArBodyHandlerFunction fn)
{
  _catchAllHandler->onBody(fn);
}

/////////////////////////////////////////////////

void AsyncWebServer::reset()
{
  _rewrites.free();
  _handlers.free();

  if (_catchAllHandler != NULL)
  {
    _catchAllHandler->onRequest(NULL);
    _catchAllHandler->onUpload(NULL);
    _catchAllHandler->onBody(NULL);
  }
}

/////////////////////////////////////////////////



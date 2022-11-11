/****************************************************************************************************************************
  Portenta_H7_AsyncWebAuthentication.h

  For Portenta_H7 (STM32H7) with Vision-Shield Ethernet or Murata WiFi

  Portenta_H7_AsyncWebServer is a library for the Portenta_H7 with Vision-Shield Ethernet or Murata WiFi

  Based on and modified from ESPAsyncWebServer (https://github.com/me-no-dev/ESPAsyncWebServer)
  Built by Khoi Hoang https://github.com/khoih-prog/Portenta_H7_AsyncWebServer
  Licensed under GPLv3 license

  Version: 1.4.2

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
 *****************************************************************************************************************************/

#pragma once

#ifndef PORTENTA_H7_ASYNCWEB_AUTHENTICATION_H_
#define PORTENTA_H7_ASYNCWEB_AUTHENTICATION_H_

#include "Arduino.h"
#include "Portenta_H7_AsyncWebServer_Debug.h"

/////////////////////////////////////////////////

bool checkBasicAuthentication(const char * header, const char * username, const char * password);
String requestDigestAuthentication(const char * realm);
bool checkDigestAuthentication(const char * header, const char * method, const char * username, const char * password,
                               const char * realm,
                               bool passwordIsHash, const char * nonce, const char * opaque, const char * uri);

//for storing hashed versions on the device that can be authenticated against
String generateDigestHash(const char * username, const char * password, const char * realm);

#endif    // APORTENTA_H7_SYNCWEB_AUTHENTICATIO_H_

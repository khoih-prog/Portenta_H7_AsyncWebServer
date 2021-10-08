/****************************************************************************************************************************
  Portenta_H7_AsyncWebAuthentication.h
  
  For Portenta_H7 (STM32H7) with Vision-Shield Ethernet
  
  Portenta_H7_AsyncWebServer is a library for the Portenta_H7 with with Vision-Shield Ethernet
  
  Based on and modified from ESPAsyncWebServer (https://github.com/me-no-dev/ESPAsyncWebServer)
  Built by Khoi Hoang https://github.com/khoih-prog/Portenta_H7_AsyncWebServer
  Licensed under GPLv3 license
 
  Version: 1.0.0
  
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      06/10/2021 Initial coding for Portenta_H7 (STM32H7) with Vision-Shield Ethernet
 *****************************************************************************************************************************/

#pragma once

#ifndef PORTENTA_H7_ASYNCWEB_AUTHENTICATION_H_
#define PORTENTA_H7_ASYNCWEB_AUTHENTICATION_H_

#include "Arduino.h"
#include "Portenta_H7_AsyncWebServer_Debug.h"

bool checkBasicAuthentication(const char * header, const char * username, const char * password);
String requestDigestAuthentication(const char * realm);
bool checkDigestAuthentication(const char * header, const char * method, const char * username, const char * password, const char * realm, bool passwordIsHash, const char * nonce, const char * opaque, const char * uri);

//for storing hashed versions on the device that can be authenticated against
String generateDigestHash(const char * username, const char * password, const char * realm);

#endif    // APORTENTA_H7_SYNCWEB_AUTHENTICATIO_H_

/****************************************************************************************************************************
  Portenta_H7_AsyncWebServer_Debug.h
  
  For Portenta_H7 (STM32H7) with Vision-Shield Ethernet
  
  Portenta_H7_AsyncWebServer is a library for the Portenta_H7 with with Vision-Shield Ethernet
  
  Based on and modified from ESPAsyncWebServer (https://github.com/me-no-dev/ESPAsyncWebServer)
  Built by Khoi Hoang https://github.com/khoih-prog/Portenta_H7_AsyncWebServer
  Licensed under GPLv3 license
 
  Version: 1.4.0
  
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      06/10/2021 Initial coding for Portenta_H7 (STM32H7) with Vision-Shield Ethernet
  1.1.0   K Hoang      08/10/2021 Add support to Portenta_H7 (STM32H7) using Murata WiFi
  1.1.1   K Hoang      12/10/2021 Update `platform.ini` and `library.json`
  1.2.0   K Hoang      07/12/2021 Fix crashing issue
  1.2.1   K Hoang      12/01/2022 Fix authenticate issue caused by libb64
  1.3.0   K Hoang      26/09/2022 Fix issue with slow browsers or network
  1.4.0   K Hoang      02/10/2022 Option to use cString instead og String to save Heap
 *****************************************************************************************************************************/

#pragma once

#ifndef PORTENTA_H7_ASYNC_WEBSERVER_DEBUG_H
#define PORTENTA_H7_ASYNC_WEBSERVER_DEBUG_H

/////////////////////////////////////////////////

#ifdef PORTENTA_H7_ASYNCWEBSERVER_DEBUG_PORT
  #define DBG_PORT_AWS      PORTENTA_H7_ASYNCWEBSERVER_DEBUG_PORT
#else
  #define DBG_PORT_AWS      Serial
#endif

/////////////////////////////////////////////////

// Change _PORTENTA_H7_AWS_LOGLEVEL_ to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: ERROR: errors
// 2: WARN: errors and warnings
// 3: INFO: errors, warnings and informational (default)
// 4: DEBUG: errors, warnings, informational and debug

#ifndef _PORTENTA_H7_AWS_LOGLEVEL_
  #define _PORTENTA_H7_AWS_LOGLEVEL_       0
#endif

/////////////////////////////////////////////////////////

#define AWS_PRINT_MARK      AWS_PRINT("[AWS] ")
#define AWS_PRINT_SP        DBG_PORT_AWS.print(" ")

#define AWS_PRINT           DBG_PORT_AWS.print
#define AWS_PRINTLN         DBG_PORT_AWS.println

/////////////////////////////////////////////////////////

#define AWS_LOGERROR(x)         if(_PORTENTA_H7_AWS_LOGLEVEL_>0) { AWS_PRINT_MARK; AWS_PRINTLN(x); }
#define AWS_LOGERROR0(x)        if(_PORTENTA_H7_AWS_LOGLEVEL_>0) { AWS_PRINT(x); }
#define AWS_LOGERROR1(x,y)      if(_PORTENTA_H7_AWS_LOGLEVEL_>0) { AWS_PRINT_MARK; AWS_PRINT(x); AWS_PRINT_SP; AWS_PRINTLN(y); }
#define AWS_LOGERROR2(x,y,z)    if(_PORTENTA_H7_AWS_LOGLEVEL_>0) { AWS_PRINT_MARK; AWS_PRINT(x); AWS_PRINT_SP; AWS_PRINT(y); AWS_PRINT_SP; AWS_PRINTLN(z); }
#define AWS_LOGERROR3(x,y,z,w)  if(_PORTENTA_H7_AWS_LOGLEVEL_>0) { AWS_PRINT_MARK; AWS_PRINT(x); AWS_PRINT_SP; AWS_PRINT(y); AWS_PRINT_SP; AWS_PRINT(z); AWS_PRINT_SP; AWS_PRINTLN(w); }

/////////////////////////////////////////////////

#define AWS_LOGWARN(x)          if(_PORTENTA_H7_AWS_LOGLEVEL_>1) { AWS_PRINT_MARK; AWS_PRINTLN(x); }
#define AWS_LOGWARN0(x)         if(_PORTENTA_H7_AWS_LOGLEVEL_>1) { AWS_PRINT(x); }
#define AWS_LOGWARN1(x,y)       if(_PORTENTA_H7_AWS_LOGLEVEL_>1) { AWS_PRINT_MARK; AWS_PRINT(x); AWS_PRINT_SP; AWS_PRINTLN(y); }
#define AWS_LOGWARN2(x,y,z)     if(_PORTENTA_H7_AWS_LOGLEVEL_>1) { AWS_PRINT_MARK; AWS_PRINT(x); AWS_PRINT_SP; AWS_PRINT(y); AWS_PRINT_SP; AWS_PRINTLN(z); }
#define AWS_LOGWARN3(x,y,z,w)   if(_PORTENTA_H7_AWS_LOGLEVEL_>1) { AWS_PRINT_MARK; AWS_PRINT(x); AWS_PRINT_SP; AWS_PRINT(y); AWS_PRINT_SP; AWS_PRINT(z); AWS_PRINT_SP; AWS_PRINTLN(w); }

/////////////////////////////////////////////////

#define AWS_LOGINFO(x)          if(_PORTENTA_H7_AWS_LOGLEVEL_>2) { AWS_PRINT_MARK; AWS_PRINTLN(x); }
#define AWS_LOGINFO0(x)         if(_PORTENTA_H7_AWS_LOGLEVEL_>2) { AWS_PRINT(x); }
#define AWS_LOGINFO1(x,y)       if(_PORTENTA_H7_AWS_LOGLEVEL_>2) { AWS_PRINT_MARK; AWS_PRINT(x); AWS_PRINT_SP; AWS_PRINTLN(y); }
#define AWS_LOGINFO2(x,y,z)     if(_PORTENTA_H7_AWS_LOGLEVEL_>2) { AWS_PRINT_MARK; AWS_PRINT(x); AWS_PRINT_SP; AWS_PRINT(y); AWS_PRINT_SP; AWS_PRINTLN(z); }
#define AWS_LOGINFO3(x,y,z,w)   if(_PORTENTA_H7_AWS_LOGLEVEL_>2) { AWS_PRINT_MARK; AWS_PRINT(x); AWS_PRINT_SP; AWS_PRINT(y); AWS_PRINT_SP; AWS_PRINT(z); AWS_PRINT_SP; AWS_PRINTLN(w); }

/////////////////////////////////////////////////

#define AWS_LOGDEBUG(x)         if(_PORTENTA_H7_AWS_LOGLEVEL_>3) { AWS_PRINT_MARK; AWS_PRINTLN(x); }
#define AWS_LOGDEBUG0(x)        if(_PORTENTA_H7_AWS_LOGLEVEL_>3) { AWS_PRINT(x); }
#define AWS_LOGDEBUG1(x,y)      if(_PORTENTA_H7_AWS_LOGLEVEL_>3) { AWS_PRINT_MARK; AWS_PRINT(x); AWS_PRINT_SP; AWS_PRINTLN(y); }
#define AWS_LOGDEBUG2(x,y,z)    if(_PORTENTA_H7_AWS_LOGLEVEL_>3) { AWS_PRINT_MARK; AWS_PRINT(x); AWS_PRINT_SP; AWS_PRINT(y); AWS_PRINT_SP; AWS_PRINTLN(z); }
#define AWS_LOGDEBUG3(x,y,z,w)  if(_PORTENTA_H7_AWS_LOGLEVEL_>3) { AWS_PRINT_MARK; AWS_PRINT(x); AWS_PRINT_SP; AWS_PRINT(y); AWS_PRINT_SP; AWS_PRINT(z); AWS_PRINT_SP; AWS_PRINTLN(w); }
#define AWS_LOGDEBUG5(x,y,z,w,xx,yy)  if(_PORTENTA_H7_AWS_LOGLEVEL_>3) { AWS_PRINT_MARK; AWS_PRINT(x); AWS_PRINT_SP; AWS_PRINT(y); AWS_PRINT_SP; AWS_PRINT(z); AWS_PRINT_SP; AWS_PRINT(w); AWS_PRINT_SP; AWS_PRINT(xx); AWS_PRINT_SP; AWS_PRINTLN(yy);}

/////////////////////////////////////////////////

#endif    //PORTENTA_H7_ASYNC_WEBSERVER_DEBUG_H

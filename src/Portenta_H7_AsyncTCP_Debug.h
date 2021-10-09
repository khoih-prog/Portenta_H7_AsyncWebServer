/****************************************************************************************************************************
  Portenta_H7_AsyncTCP_Debug.h
  
  For Portenta_H7 (STM32H7) with Vision-Shield Ethernet
  
  Portenta_H7_ASYNC_TCP is a library for the Portenta_H7 with with Vision-Shield Ethernet
  
  Based on and modified from ESPASYNC_TCP (https://github.com/me-no-dev/ESPASYNC_TCP)
  Built by Khoi Hoang https://github.com/khoih-prog/Portenta_H7_ASYNC_TCP
  Licensed under MIT license
 
  Version: 1.1.0
  
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      06/10/2021 Initial coding for Portenta_H7 (STM32H7) with Vision-Shield Ethernet
  1.1.0   K Hoang      08/10/2021 Add support to Portenta_H7 (STM32H7) using Murata WiFi
 *****************************************************************************************************************************/

#pragma once

#ifndef PORTENTA_H7_ASYNC_TCP_DEBUG_H
#define PORTENTA_H7_ASYNC_TCP_DEBUG_H

#ifdef PORTENTA_H7_ASYNC_TCP_DEBUG_PORT
  #define DBG_PORT_ATCP      PORTENTA_H7_ASYNC_TCP_DEBUG_PORT
#else
  #define DBG_PORT_ATCP      Serial
#endif

// Change _PORTENTA_H7_ATCP_LOGLEVEL_ to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: ERROR: errors
// 2: WARN: errors and warnings
// 3: INFO: errors, warnings and informational (default)
// 4: DEBUG: errors, warnings, informational and debug

#ifndef _PORTENTA_H7_ATCP_LOGLEVEL_
  #define _PORTENTA_H7_ATCP_LOGLEVEL_       1
#endif

/////////////////////////////////////////////////////////

#define ATCP_PRINT_MARK      ATCP_PRINT("[ATCP] ")
#define ATCP_PRINT_SP        DBG_PORT_ATCP.print(" ")

#define ATCP_PRINT           DBG_PORT_ATCP.print
#define ATCP_PRINTLN         DBG_PORT_ATCP.println

/////////////////////////////////////////////////////////

#define ATCP_LOGERROR(x)         if(_PORTENTA_H7_ATCP_LOGLEVEL_>0) { ATCP_PRINT_MARK; ATCP_PRINTLN(x); }
#define ATCP_LOGERROR0(x)        if(_PORTENTA_H7_ATCP_LOGLEVEL_>0) { ATCP_PRINT(x); }
#define ATCP_LOGERROR1(x,y)      if(_PORTENTA_H7_ATCP_LOGLEVEL_>0) { ATCP_PRINT_MARK; ATCP_PRINT(x); ATCP_PRINT_SP; ATCP_PRINTLN(y); }
#define ATCP_LOGERROR2(x,y,z)    if(_PORTENTA_H7_ATCP_LOGLEVEL_>0) { ATCP_PRINT_MARK; ATCP_PRINT(x); ATCP_PRINT_SP; ATCP_PRINT(y); ATCP_PRINT_SP; ATCP_PRINTLN(z); }
#define ATCP_LOGERROR3(x,y,z,w)  if(_PORTENTA_H7_ATCP_LOGLEVEL_>0) { ATCP_PRINT_MARK; ATCP_PRINT(x); ATCP_PRINT_SP; ATCP_PRINT(y); ATCP_PRINT_SP; ATCP_PRINT(z); ATCP_PRINT_SP; ATCP_PRINTLN(w); }

#define ATCP_LOGWARN(x)          if(_PORTENTA_H7_ATCP_LOGLEVEL_>1) { ATCP_PRINT_MARK; ATCP_PRINTLN(x); }
#define ATCP_LOGWARN0(x)         if(_PORTENTA_H7_ATCP_LOGLEVEL_>1) { ATCP_PRINT(x); }
#define ATCP_LOGWARN1(x,y)       if(_PORTENTA_H7_ATCP_LOGLEVEL_>1) { ATCP_PRINT_MARK; ATCP_PRINT(x); ATCP_PRINT_SP; ATCP_PRINTLN(y); }
#define ATCP_LOGWARN2(x,y,z)     if(_PORTENTA_H7_ATCP_LOGLEVEL_>1) { ATCP_PRINT_MARK; ATCP_PRINT(x); ATCP_PRINT_SP; ATCP_PRINT(y); ATCP_PRINT_SP; ATCP_PRINTLN(z); }
#define ATCP_LOGWARN3(x,y,z,w)   if(_PORTENTA_H7_ATCP_LOGLEVEL_>1) { ATCP_PRINT_MARK; ATCP_PRINT(x); ATCP_PRINT_SP; ATCP_PRINT(y); ATCP_PRINT_SP; ATCP_PRINT(z); ATCP_PRINT_SP; ATCP_PRINTLN(w); }

#define ATCP_LOGINFO(x)          if(_PORTENTA_H7_ATCP_LOGLEVEL_>2) { ATCP_PRINT_MARK; ATCP_PRINTLN(x); }
#define ATCP_LOGINFO0(x)         if(_PORTENTA_H7_ATCP_LOGLEVEL_>2) { ATCP_PRINT(x); }
#define ATCP_LOGINFO1(x,y)       if(_PORTENTA_H7_ATCP_LOGLEVEL_>2) { ATCP_PRINT_MARK; ATCP_PRINT(x); ATCP_PRINT_SP; ATCP_PRINTLN(y); }
#define ATCP_LOGINFO2(x,y,z)     if(_PORTENTA_H7_ATCP_LOGLEVEL_>2) { ATCP_PRINT_MARK; ATCP_PRINT(x); ATCP_PRINT_SP; ATCP_PRINT(y); ATCP_PRINT_SP; ATCP_PRINTLN(z); }
#define ATCP_LOGINFO3(x,y,z,w)   if(_PORTENTA_H7_ATCP_LOGLEVEL_>2) { ATCP_PRINT_MARK; ATCP_PRINT(x); ATCP_PRINT_SP; ATCP_PRINT(y); ATCP_PRINT_SP; ATCP_PRINT(z); ATCP_PRINT_SP; ATCP_PRINTLN(w); }

#define ATCP_LOGDEBUG(x)         if(_PORTENTA_H7_ATCP_LOGLEVEL_>3) { ATCP_PRINT_MARK; ATCP_PRINTLN(x); }
#define ATCP_LOGDEBUG0(x)        if(_PORTENTA_H7_ATCP_LOGLEVEL_>3) { ATCP_PRINT(x); }
#define ATCP_LOGDEBUG1(x,y)      if(_PORTENTA_H7_ATCP_LOGLEVEL_>3) { ATCP_PRINT_MARK; ATCP_PRINT(x); ATCP_PRINT_SP; ATCP_PRINTLN(y); }
#define ATCP_LOGDEBUG2(x,y,z)    if(_PORTENTA_H7_ATCP_LOGLEVEL_>3) { ATCP_PRINT_MARK; ATCP_PRINT(x); ATCP_PRINT_SP; ATCP_PRINT(y); ATCP_PRINT_SP; ATCP_PRINTLN(z); }
#define ATCP_LOGDEBUG3(x,y,z,w)  if(_PORTENTA_H7_ATCP_LOGLEVEL_>3) { ATCP_PRINT_MARK; ATCP_PRINT(x); ATCP_PRINT_SP; ATCP_PRINT(y); ATCP_PRINT_SP; ATCP_PRINT(z); ATCP_PRINT_SP; ATCP_PRINTLN(w); }

#endif    //PORTENTA_H7_ASYNC_TCP_DEBUG_H

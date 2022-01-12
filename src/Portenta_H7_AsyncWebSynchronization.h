/****************************************************************************************************************************
  Portenta_H7_AsyncWebSynchronization.h
  
  For Portenta_H7 (STM32H7) with Vision-Shield Ethernet
  
  Portenta_H7_AsyncWebServer is a library for the Portenta_H7 with with Vision-Shield Ethernet
  
  Based on and modified from ESPAsyncWebServer (https://github.com/me-no-dev/ESPAsyncWebServer)
  Built by Khoi Hoang https://github.com/khoih-prog/Portenta_H7_AsyncWebServer
  Licensed under GPLv3 license
 
  Version: 1.2.1
  
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      06/10/2021 Initial coding for Portenta_H7 (STM32H7) with Vision-Shield Ethernet
  1.1.0   K Hoang      08/10/2021 Add support to Portenta_H7 (STM32H7) using Murata WiFi
  1.1.1   K Hoang      12/10/2021 Update `platform.ini` and `library.json`
  1.2.0   K Hoang      07/12/2021 Fix crashing issue
  1.2.1   K Hoang      12/01/2022 Fix authenticate issue caused by libb64
 *****************************************************************************************************************************/

#pragma once

#ifndef PORTENTA_H7_ASYNCWEBSYNCHRONIZATION_H_
#define PORTENTA_H7_ASYNCWEBSYNCHRONIZATION_H_

#include <Portenta_H7_AsyncWebServer.h>

// This is the STM32 version of the Sync Lock which is currently unimplemented
class AsyncWebLock
{

  public:
    AsyncWebLock()  {}

    ~AsyncWebLock() {}

    bool lock() const 
    {
      return false;
    }

    void unlock() const {}
};

class AsyncWebLockGuard
{
  private:
    const AsyncWebLock *_lock;

  public:
    AsyncWebLockGuard(const AsyncWebLock &l) 
    {
      if (l.lock()) 
      {
        _lock = &l;
      } 
      else 
      {
        _lock = NULL;
      }
    }

    ~AsyncWebLockGuard() 
    {
      if (_lock) 
      {
        _lock->unlock();
      }
    }
};

#endif // PORTENTA_H7_ASYNCWEBSYNCHRONIZATION_H_

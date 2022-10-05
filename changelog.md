# Portenta_H7_AsyncWebServer

[![arduino-library-badge](https://www.ardu-badge.com/badge/Portenta_H7_AsyncWebServer.svg?)](https://www.ardu-badge.com/Portenta_H7_AsyncWebServer)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/Portenta_H7_AsyncWebServer.svg)](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/releases)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/Portenta_H7_AsyncWebServer.svg)](http://github.com/khoih-prog/Portenta_H7_AsyncWebServer/issues)

---
---

## Table of Contents

* [Changelog](#changelog)
  * [Releases v1.4.1](#Releases-v141)
  * [Releases v1.4.0](#Releases-v140)
  * [Releases v1.3.0](#Releases-v130)
  * [Releases v1.2.1](#Releases-v121)
  * [Releases v1.2.0](#Releases-v120)
  * [Releases v1.1.1](#Releases-v111)
  * [Releases v1.1.0](#Releases-v110)
  * [Initial Releases v1.0.0](#Initial-Releases-v100)

---
---

## Changelog

### Releases v1.4.1

1. Don't need `memmove()`, CString no longer destroyed. Check [All memmove() removed - string no longer destroyed #11](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/pull/11)

### Releases v1.4.0

1. Support using `CString` in optional `SDRAM` to save heap to send `very large data`. Check [request->send(200, textPlainStr, jsonChartDataCharStr); - Without using String Class - to save heap #8](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/pull/8)
2. Add multiple examples to demo the new feature

### Releases v1.3.0

1. Fix issue with slow browsers or network. Check [Target stops responding after variable time when using Firefox on Windows 10 #3](https://github.com/khoih-prog/AsyncWebServer_RP2040W/issues/3)

### Releases v1.2.1

1. Fix authenticate issue caused by libb64

### Releases v1.2.0

1. Fix crashing issue in mbed_portenta v2.6.1+. To be used with [**Portenta_H7_AsyncTCP releases v1.3.0+**](https://github.com/khoih-prog/Portenta_H7_AsyncTCP/releases/tag/v1.3.0)

### Releases v1.1.1

1. Update `platform.ini` and `library.json` to use original `khoih-prog` instead of `khoih.prog` after PIO fix


### Releases v1.1.0

1. Add support to  **Portenta_H7 boards** such as Portenta_H7 Rev2 ABX00042, etc., using [**ArduinoCore-mbed mbed_portenta** core](https://github.com/arduino/ArduinoCore-mbed) and `Murata WiFi`

### Initial Releases v1.0.0

1. Initial coding to support **Portenta_H7 boards** such as Portenta_H7 Rev2 ABX00042, etc., using [**ArduinoCore-mbed mbed_portenta** core](https://github.com/arduino/ArduinoCore-mbed) and `Vision-shield Ethernet`

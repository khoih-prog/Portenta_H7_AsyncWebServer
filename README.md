# Portenta_H7_AsyncTCP 

[![arduino-library-badge](https://www.ardu-badge.com/badge/Portenta_H7_AsyncTCP.svg?)](https://www.ardu-badge.com/Portenta_H7_AsyncTCP)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/Portenta_H7_AsyncTCP.svg)](https://github.com/khoih-prog/Portenta_H7_AsyncTCP/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/Portenta_H7_AsyncTCP/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/Portenta_H7_AsyncTCP.svg)](http://github.com/khoih-prog/Portenta_H7_AsyncTCP/issues)


---
---

## Table of contents

* [Table of contents](#table-of-contents)
* [Why do we need this Portenta_H7_AsyncTCP library](#why-do-we-need-this-Portenta_H7_AsyncTCP-library)
  * [Features](#features)
  * [Why Async is better](#why-async-is-better)
  * [Currently supported Boards](#currently-supported-boards)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For Portenta_H7 boards using Arduino IDE in Linux](#1-for-portenta_h7-boards-using-arduino-ide-in-linux)
* [Orignal documentation](#Orignal-documentation)
  * [AsyncClient and AsyncServer](#AsyncClient-and-AsyncServer)
  * [AsyncPrinter](#AsyncPrinter)
  * [AsyncTCPbuffer](#AsyncTCPbuffer)
  * [SyncClient](#SyncClient)
* [Debug Terminal Output Samples](#debug-terminal-output-samples) 
  * [1. Async_AdvancedWebServer on PORTENTA_H7_M7 using Ethernet](#1-Async_AdvancedWebServer-on-PORTENTA_H7_M7-using-Ethernet)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Releases](#releases)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---

### Why do we need this [Portenta_H7_AsyncTCP library](https://github.com/khoih-prog/Portenta_H7_AsyncTCP)

#### Features

This library is based on, modified from:

1. [Hristo Gochkov's ESPAsyncTCP](https://github.com/me-no-dev/ESPAsyncTCP)
2. [Phil Bowles' STM32AsyncTCP](https://github.com/philbowles/STM32AsyncTCP)

to apply the better and faster **asynchronous** feature of the **powerful** [ESPAsyncTCP Library](https://github.com/me-no-dev/ESPAsyncTCP) into **Portenta_H7 boards**, and will be the base for future and more advanced Async libraries for Portenta_H7, such as Portenta_H7_AsyncWebServer, Portenta_H7_AsyncHTTPRequest, Portenta_H7_AsyncHTTPSRequest


#### Why Async is better

- Using asynchronous network means that you can handle **more than one connection at the same time**
- **You are called once the request is ready and parsed**
- When you send the response, you are **immediately ready** to handle other connections while the server is taking care of sending the response in the background
- **Speed is OMG**
- **Easy to use API, HTTP Basic and Digest MD5 Authentication (default), ChunkedResponse**
- Easily extensible to handle **any type of content**
- Supports Continue 100
- **Async WebSocket plugin offering different locations without extra servers or ports**
- Async EventSource (Server-Sent Events) plugin to send events to the browser
- URL Rewrite plugin for conditional and permanent url rewrites
- ServeStatic plugin that supports cache, Last-Modified, default index and more
- Simple template processing engine to handle templates


### Currently supported Boards

1. **Portenta_H7 boards** such as Portenta_H7 Rev2 ABX00042, etc., using [**ArduinoCore-mbed mbed_portenta** core](https://github.com/arduino/ArduinoCore-mbed)


---
---

## Prerequisites

 1. [`Arduino IDE 1.8.16+` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`ArduinoCore-mbed mbed_portenta core 2.5.2+`](https://github.com/arduino/ArduinoCore-mbed) for Arduino **Portenta_H7** boards, such as **Portenta_H7 Rev2 ABX00042, etc.**. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-mbed.svg)](https://github.com/arduino/ArduinoCore-mbed/releases/latest)

---
---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for [**Portenta_H7_AsyncTCP**](https://github.com/khoih-prog/Portenta_H7_AsyncTCP), then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/Portenta_H7_AsyncTCP.svg?)](https://www.ardu-badge.com/Portenta_H7_AsyncTCP) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [**Portenta_H7_AsyncTCP**](https://github.com/khoih-prog/Portenta_H7_AsyncTCP) page.
2. Download the latest release `Portenta_H7_AsyncTCP-master.zip`.
3. Extract the zip file to `Portenta_H7_AsyncTCP-master` directory 
4. Copy whole `Portenta_H7_AsyncTCP-master` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**Portenta_H7_AsyncTCP** library](https://platformio.org/lib/show/12919/Portenta_H7_AsyncTCP) by using [Library Manager](https://platformio.org/lib/show/12919/Portenta_H7_AsyncTCP/installation). Search for **Portenta_H7_AsyncTCP** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Packages' Patches

#### 1. For Portenta_H7 boards using Arduino IDE in Linux

  **To be able to upload firmware to Portenta_H7 using Arduino IDE in Linux (Ubuntu, etc.)**, you have to copy the file [portenta_post_install.sh](Packages_Patches/arduino/hardware/mbed_portenta/2.4.1/portenta_post_install.sh) into mbed_portenta directory (~/.arduino15/packages/arduino/hardware/mbed_portenta/2.4.1/portenta_post_install.sh). 
  
  Then run the following command using `sudo`
  
```
$ cd ~/.arduino15/packages/arduino/hardware/mbed_portenta/2.4.1
$ chmod 755 portenta_post_install.sh
$ sudo ./portenta_post_install.sh
```

This will create the file `/etc/udev/rules.d/49-portenta_h7.rules` as follows:

```
# Portenta H7 bootloader mode UDEV rules

SUBSYSTEMS=="usb", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="035b", GROUP="plugdev", MODE="0666"
```

Supposing the ArduinoCore-mbed core version is 2.4.1. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/2.4.1/portenta_post_install.sh`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/x.yy.zz/portenta_post_install.sh`


---
---

## Orignal documentation

For ESP32, check [AsyncTCP Library](https://github.com/me-no-dev/AsyncTCP)

[Join the ESPAsyncWebServer chat](https://gitter.im/me-no-dev/ESPAsyncWebServer)  [![Join the chat at https://gitter.im/me-no-dev/ESPAsyncWebServer](https://badges.gitter.im/me-no-dev/ESPAsyncWebServer.svg)](https://gitter.im/me-no-dev/ESPAsyncWebServer?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

This is a fully asynchronous TCP library, aimed at enabling trouble-free, multi-connection network environment for Espressif's ESP8266 MCUs.

### AsyncClient and AsyncServer

The base classes on which everything else is built. They expose all possible scenarios, but are really raw and require more skills to use.

### AsyncPrinter

This class can be used to send data like any other `Print` interface (`Serial` for example).

The object then can be used outside of the Async callbacks (the loop) and receive asynchronously data using `onData`. The object can be checked if the underlying `AsyncClient`is connected, or hook to the `onDisconnect` callback.

### AsyncTCPbuffer

This class is really similar to the `AsyncPrinter`, but it can buffer some of the incoming data.

### SyncClient

It is exactly what it sounds like. This is a standard, synchronous blocking TCP Client you're used to.


---
---

### Debug Terminal Output Samples

#### 1. Async_AdvancedWebServer on PORTENTA_H7_M7 using Ethernet

Following is the debug terminal and screen shot when running example [Async_AdvancedWebServer](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer/examples/Ethernet/Async_AdvancedWebServer) on Portenta_H7 Ethernet to demonstrate the operation of Portenta_H7_AsyncWebServer, based on this [Portenta_H7_AsyncTCP Library](https://github.com/khoih-prog/Portenta_H7_AsyncTCP).

```
Start Async_AdvancedWebServer on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
Portenta_H7_AsyncTCP v1.0.0
Portenta_H7_AsyncWebServer v1.0.0
Using mac index = 4
Connected! IP address: 192.168.2.87
HTTP EthernetWebServer is @ IP : 192.168.2.87
....
```

You can access the Async Advanced WebServers at the displayed server IP, e.g. `192.168.2.87`

<p align="center">
    <img src="https://github.com/khoih-prog/Portenta_H7_AsyncTCP/blob/main/pics/Async_AdvancedWebServer.png">
</p>


---
---

### Debug

Debug is enabled by default on Serial.

You can also change the debugging level `_PORTENTA_H7_ATCP_LOGLEVEL_` from 0 to 4 in the library `cpp` files

```cpp
#define _PORTENTA_H7_ATCP_LOGLEVEL_     1
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the core for Arduino boards.

Sometimes, the library will only work if you update the board core to the latest version because I am using newly added functions.


---
---

### Issues

Submit issues to: [Portenta_H7_AsyncTCP issues](https://github.com/khoih-prog/Portenta_H7_AsyncTCP/issues)

---

## TO DO

1. Search for bug and improvement.
2. Add support to Portenta_H7 `Murata WiFi`

---

## DONE

1. Add support to Portenta_H7 `Vision-shield Ethernet`
2. Add Table of Contents

---
---

### Contributions and Thanks

Many thanks for everyone for bug reporting, new feature suggesting, testing and contributing to the development of this library.

### Contributions and Thanks

1. Based on and modified from [Hristo Gochkov's ESPAsyncTCP](https://github.com/me-no-dev/ESPAsyncTCP). Many thanks to [Hristo Gochkov](https://github.com/me-no-dev) for great [ESPAsyncTCP Library](https://github.com/me-no-dev/ESPAsyncTCP)
2. Based on [PhilBowles' STM32 AsyncTCP Library](https://github.com/philbowles/STM32AsyncTCP).
3. Thanks to [rusty-bit](https://github.com/rusty-bit) to initiate the Discussion in [**AsyncWebserver for Portenta H7** #6](https://github.com/khoih-prog/AsyncWebServer_STM32/discussions/6) leading to these [Portenta_H7_AsyncTCP](https://github.com/khoih-prog/Portenta_H7_AsyncTCP) and [Portenta_H7_AsyncWebServer](https://github.com/khoih-prog/Portenta_H7_AsyncWebServer) libraries

<table>
  <tr>
    <td align="center"><a href="https://github.com/me-no-dev"><img src="https://github.com/me-no-dev.png" width="100px;" alt="me-no-dev"/><br /><sub><b>⭐️⭐️ Hristo Gochkov</b></sub></a><br /></td>
     <td align="center"><a href="https://github.com/philbowles"><img src="https://github.com/philbowles.png" width="100px;" alt="philbowles"/><br /><sub><b>⭐️ Phil Bowles</b></sub></a><br /></td>
     <td align="center"><a href="https://github.com/rusty-bit"><img src="https://github.com/rusty-bit.png" width="100px;" alt="rusty-bit"/><br /><sub><b>rusty-bit</b></sub></a><br /></td>
  </tr> 
</table>

---

## Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [GPLv3](https://github.com/khoih-prog/Portenta_H7_AsyncTCP/blob/main/LICENSE)

---

## Copyright

Copyright 2021- Khoi Hoang



/****************************************************************************************************************************
  Async_AdvancedWebServer_MemoryIssues_Send_CString.ino - Dead simple AsyncWebServer for Portenta_H7

  For Portenta_H7 (STM32H7) with Vision-Shield Ethernet or Murata WiFi

  Portenta_H7_AsyncWebServer is a library for the Portenta_H7 with Vision-Shield Ethernet or Murata WiFi

  Based on and modified from ESPAsyncWebServer (https://github.com/me-no-dev/ESPAsyncWebServer)
  Built by Khoi Hoang https://github.com/khoih-prog/Portenta_H7_AsyncWebServer
  Licensed under GPLv3 license

  Copyright (c) 2015, Majenko Technologies
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:

  Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

  Redistributions in binary form must reproduce the above copyright notice, this
  list of conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.

  Neither the name of Majenko Technologies nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************************************************************/

#if !( defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) )
	#error For Portenta_H7 only
#endif

#define _PORTENTA_H7_ATCP_LOGLEVEL_     1
#define _PORTENTA_H7_AWS_LOGLEVEL_      1

#define USE_WIFI_PORTENTA_H7        true

#include <WiFi.h>
#warning Using WiFi for Portenta_H7.

#include <Portenta_H7_AsyncWebServer.h>

char ssid[] = "your_ssid";        // your network SSID (name)
char pass[] = "12345678";         // your network password (use for WPA, or use as key for WEP), length must be 8+

int status = WL_IDLE_STATUS;

char *cStr;

// In bytes
#define CSTRING_SIZE                    40000

// Select either cString is stored in SDRAM or not
#define USING_CSTRING_IN_SDRAM          true

#if USING_CSTRING_IN_SDRAM
	#include "SDRAM.h"
#endif

AsyncWebServer    server(80);

int reqCount = 0;                // number of requests received

#define LED_OFF             HIGH
#define LED_ON              LOW

#define BUFFER_SIZE         768 // a little larger in case required for header shift (destructive send)
char temp[BUFFER_SIZE];

void handleRoot(AsyncWebServerRequest *request)
{
	digitalWrite(LED_BUILTIN, LED_ON);

	int sec = millis() / 1000;
	int min = sec / 60;
	int hr = min / 60;
	int day = hr / 24;

	snprintf(temp, BUFFER_SIZE - 1,
	         "<html>\
<head>\
<meta http-equiv='refresh' content='60'/>\
<title>AsyncWebServer-%s</title>\
<style>\
body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
</style>\
</head>\
<body>\
<h2>AsyncWebServer_Portenta_H7!</h2>\
<h3>running WiFi on %s</h3>\
<p>Uptime: %d d %02d:%02d:%02d</p>\
<img src=\"/test.svg\" />\
</body>\
</html>", BOARD_NAME, BOARD_NAME, day, hr % 24, min % 60, sec % 60);

	request->send(200, "text/html", temp);

	digitalWrite(LED_BUILTIN, LED_OFF);
}

void handleNotFound(AsyncWebServerRequest *request)
{
	digitalWrite(LED_BUILTIN, LED_ON);
	String message = "File Not Found\n\n";

	message += "URI: ";
	message += request->url();
	message += "\nMethod: ";
	message += (request->method() == HTTP_GET) ? "GET" : "POST";
	message += "\nArguments: ";
	message += request->args();
	message += "\n";

	for (uint8_t i = 0; i < request->args(); i++)
	{
		message += " " + request->argName(i) + ": " + request->arg(i) + "\n";
	}

	request->send(404, "text/plain", message);
	digitalWrite(LED_BUILTIN, LED_OFF);
}

void PrintHeapData(String hIn)
{
	static mbed_stats_heap_t heap_stats;
	static uint32_t maxHeapSize = 0;

	mbed_stats_heap_get(&heap_stats);

	// Print and update only when different
	if (maxHeapSize != heap_stats.max_size)
	{
		maxHeapSize = heap_stats.max_size;

		Serial.print("\nHEAP DATA - ");
		Serial.print(hIn);

		Serial.print("  Cur heap: ");
		Serial.print(heap_stats.current_size);
		Serial.print("  Res Size: ");
		Serial.print(heap_stats.reserved_size);
		Serial.print("  Max heap: ");
		Serial.println(heap_stats.max_size);
	}
}

void PrintStringSize(const char* cStr)
{
	Serial.print("\nOut String Length=");
	Serial.println(strlen(cStr));
}

void drawGraph(AsyncWebServerRequest *request)
{
	char temp[80];

	cStr[0] = '\0';

	strcat(cStr, "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"1810\" height=\"150\">\n");
	strcat(cStr, "<rect width=\"1810\" height=\"150\" fill=\"rgb(250, 230, 210)\" stroke-width=\"2\" stroke=\"rgb(0, 0, 0)\" />\n");
	strcat(cStr, "<g stroke=\"blue\">\n");
	int y = rand() % 130;

	for (int x = 10; x < 5000; x += 10)
	{
		int y2 = rand() % 130;
		sprintf(temp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"2\" />\n", x, 140 - y, x + 10, 140 - y2);
		strcat(cStr, temp);
		y = y2;
	}

	strcat(cStr, "</g>\n</svg>\n");

	PrintHeapData("Pre Send");

	// Print only when cStr length too large and corrupting memory
	if ( (strlen(cStr) >= CSTRING_SIZE))
	{
		PrintStringSize(cStr);
	}

	request->send(200, "image/svg+xml", cStr, false);

	PrintHeapData("Post Send");
}

void printWifiStatus()
{
	// print the SSID of the network you're attached to:
	Serial.print("SSID: ");
	Serial.println(WiFi.SSID());

	// print your board's IP address:
	IPAddress ip = WiFi.localIP();
	Serial.print("Local IP Address: ");
	Serial.println(ip);

	// print the received signal strength:
	long rssi = WiFi.RSSI();
	Serial.print("signal strength (RSSI):");
	Serial.print(rssi);
	Serial.println(" dBm");
}

void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LED_OFF);

	Serial.begin(115200);

	while (!Serial && millis() < 5000);

	delay(200);

#if USING_CSTRING_IN_SDRAM
	Serial.print("\nStart Async_AdvancedWebServer_MemoryIssues_Send_CString using SDRAM on ");
#else
	Serial.print("\nStart Async_AdvancedWebServer_MemoryIssues_Send_CString on ");
#endif

	Serial.print(BOARD_NAME);
	Serial.print(" with ");
	Serial.println(SHIELD_TYPE);
	Serial.println(PORTENTA_H7_ASYNC_TCP_VERSION);
	Serial.println(PORTENTA_H7_ASYNC_WEBSERVER_VERSION);

#if USING_CSTRING_IN_SDRAM
	SDRAM.begin();

	cStr = (char *) SDRAM.malloc(CSTRING_SIZE);     // make a little larger than required
#else
	cStr = (char *) malloc(CSTRING_SIZE);           // make a little larger than required
#endif

	if (cStr == NULL)
	{
		Serial.println("Unable top Allocate RAM");

		for (;;);
	}

	///////////////////////////////////

	// check for the WiFi module:
	if (WiFi.status() == WL_NO_MODULE)
	{
		Serial.println("Communication with WiFi module failed!");

		// don't continue
		while (true);
	}

	Serial.print(F("Connecting to SSID: "));
	Serial.println(ssid);

	status = WiFi.begin(ssid, pass);

	delay(1000);

	// attempt to connect to WiFi network
	while ( status != WL_CONNECTED)
	{
		delay(500);

		// Connect to WPA/WPA2 network
		status = WiFi.status();
	}

	printWifiStatus();

	///////////////////////////////////

	server.on("/", HTTP_GET, [](AsyncWebServerRequest * request)
	{
		handleRoot(request);
	});

	server.on("/test.svg", HTTP_GET, [](AsyncWebServerRequest * request)
	{
		drawGraph(request);
	});

	server.on("/inline", [](AsyncWebServerRequest * request)
	{
		request->send(200, "text/plain", "This works as well");
	});

	server.onNotFound(handleNotFound);

	server.begin();

	Serial.print(F("HTTP EthernetWebServer is @ IP : "));
	Serial.println(WiFi.localIP());

	PrintHeapData("Pre Create Arduino String");

}

void heartBeatPrint()
{
	static int num = 1;

	Serial.print(F("."));

	if (num == 80)
	{
		//Serial.println();
		PrintStringSize(cStr);
		num = 1;
	}
	else if (num++ % 10 == 0)
	{
		Serial.print(F(" "));
	}
}

void check_status()
{
	static unsigned long checkstatus_timeout = 0;

#define STATUS_CHECK_INTERVAL     10000L

	// Send status report every STATUS_REPORT_INTERVAL (60) seconds: we don't need to send updates frequently if there is no status change.
	if ((millis() > checkstatus_timeout) || (checkstatus_timeout == 0))
	{
		heartBeatPrint();
		checkstatus_timeout = millis() + STATUS_CHECK_INTERVAL;
	}
}

void loop()
{
	check_status();
}

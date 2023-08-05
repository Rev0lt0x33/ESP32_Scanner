#ifndef _WebServer_h
#define _WebServer_h

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>

#include "MemoryMap.h"
#include "Connection.h"
#include "SPIFFS.h"
class WebServer
{
protected:
private:
    AsyncWebServer *_server;
    static bool _loggedIn;
    static void handleLogin(AsyncWebServerRequest *request);
    static void handleLogout(AsyncWebServerRequest *request);
    static void handleRoot(AsyncWebServerRequest *request);
    static void handleNotFound(AsyncWebServerRequest *request);
    static void handleConfigData(AsyncWebServerRequest *request);
    static void handleConfigurationPage(AsyncWebServerRequest *request);
    static void handleDeviceData(AsyncWebServerRequest *request);
    static void handleReset(AsyncWebServerRequest *request);
    static void handleCss(AsyncWebServerRequest *request);
    static void handleRestart(AsyncWebServerRequest *request);

public:
    WebServer();
    ~WebServer();
};

#endif
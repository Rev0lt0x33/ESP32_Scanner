#include "WebsiteBuilder.h"

String WebsiteBuilder::generateLoginPage(const String &placeholder)
{
    if (placeholder == "SSID")
        return MemMap::getInstance().getSSID();

    if (placeholder == "SERVERIP")
        return MemMap::getInstance().getServerIP();

    if (placeholder == "APIKEY")
        return MemMap::getInstance().getApiKey();

    if (placeholder == "DEVICENAME")
        return MemMap::getInstance().getDeviceName();

    return String();
}
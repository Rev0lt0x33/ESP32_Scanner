#ifndef _ProbeRequest_
#define _ProbeRequest_

#include <vector>
#include "esp_wifi.h"
#include <string>
#include <WiFi.h>
#include <Arduino.h>
#include <HTTPClient.h>
#include "MemoryMap.h"
#include "Connection.h"
class ProbeRequest
{
private:
    typedef struct MacAddress
    {
        uint8_t mac[6];
    } __attribute__((packed)) MacAddress;

    typedef struct
    {
        int16_t fctl;
        int16_t duration;
        MacAddress da;
        MacAddress sa;
        MacAddress bssid;
        int16_t seqctl;
        unsigned char payload[];
    } __attribute__((packed)) PacketStruct;

    static String serializeJSON(String mac);
    static std::vector<String> *macArray;
    static void addToVector(String mac);

public:
    static unsigned short macCount;
    ProbeRequest();
    ~ProbeRequest();
    static void requestCallback(void *buf, wifi_promiscuous_pkt_type_t type);
    static void sendData();
};

#endif
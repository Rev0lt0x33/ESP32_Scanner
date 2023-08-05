#include "ProbeRequest.h"
std::vector<String> *ProbeRequest::macArray = new std::vector<String>();
unsigned short ProbeRequest::macCount = 0;

ProbeRequest::ProbeRequest()
{

    Serial.println("Working");
    Connection::getInstance().initAPProm();
}

ProbeRequest::~ProbeRequest()
{
    Connection::getInstance().disconnectAPProm();
}

void ProbeRequest::requestCallback(void *buf, wifi_promiscuous_pkt_type_t type)
{
    wifi_promiscuous_pkt_t *packet = (wifi_promiscuous_pkt_t *)buf;
    int len = packet->rx_ctrl.sig_len;
    PacketStruct *ps = (PacketStruct *)packet->payload;
    len -= sizeof(PacketStruct);

    if (len < 0)
    {
        Serial.println("Packet length: 0");
        return;
    }
    int fctl = ntohs(ps->fctl);

    if (fctl != 0x4000)
        return;

    String temp;
    temp = "";
    for (int i = 0; i < 6; i++)
    {
        temp += String(ps->sa.mac[i], HEX);
    }
    temp.toUpperCase();
    ProbeRequest::addToVector(temp);
}

void ProbeRequest::sendData()
{
    Connection::getInstance().disconnectAPProm();

    Connection::getInstance().initWiFi();
    HTTPClient httpClient;

    String server = MemMap::getInstance().getServerIP();
    const unsigned int port = 5000;
    String path = "/Data/Post";
    httpClient.begin(server, port, path);
    httpClient.addHeader("Content-Type", "application/json");

    for (int i = 0; i < macCount; i++)
    {
        String data = serializeJSON(ProbeRequest::macArray->at(i));
        httpClient.POST(data);
    }
    httpClient.end();
    ProbeRequest::macArray->clear();
    ProbeRequest::macCount = 0;
    Connection::getInstance().initAPProm();
}

String ProbeRequest::serializeJSON(String mac)
{
    String request = "{ \"Name\": \"" + MemMap::getInstance().getDeviceName() + "\",\"DeviceAddress\": \"" + ESP.getEfuseMac() + "\",\"ApiKey\": \"" + MemMap::getInstance().getApiKey() + "\" , \"Mac\": \"" + mac + "\"}";
    return request;
}

void ProbeRequest::addToVector(String mac)
{
    if (std::find(macArray->begin(), macArray->end(), mac) == macArray->end())
    {
        macArray->push_back(mac);
        macCount++;
        Serial.print("add data");
    }
}

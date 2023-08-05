
#include "Connection.h"

void Connection::disconnectWiFi()
{
	WiFi.disconnect(true);
}

void Connection::initWiFi()
{

	Serial.println("WIFI CONN");
	Serial.println(MemMap::getInstance().getSSID());
	Serial.println(MemMap::getInstance().getSSIDPassword());
	WiFi.mode(WIFI_STA);
	// WiFi.begin(MemMap::getInstance().getSSID(), MemMap::getInstance().getSSIDPassword());
	// if (WiFi.waitForConnectResult() != WL_CONNECTED) {
	// 	Serial.printf("WiFi Failed!\n");
	// 	//Debug::setLocalServer();
	// 	MemMap::getInstance().factorySetup();

	// }
	WiFi.begin(MemMap::getInstance().getSSID(), MemMap::getInstance().getSSIDPassword());
	if (WiFi.waitForConnectResult() != WL_CONNECTED)
	{
		Serial.printf("WiFi Failed!\n");
		// MemMap::getInstance().factorySetup();
	}
	Serial.print("IP Address: ");
	Serial.println(WiFi.localIP());
}

void Connection::initAP()
{
	WiFi.mode(WIFI_AP);
	if (!WiFi.softAP(MemMap::getInstance().getSSID(), MemMap::getInstance().getSSIDPassword(), 10, 0, 4))
	{
		Serial.println("Can't create AP");
		return;
	}
	Serial.print("Connected: ");
	Serial.print(WiFi.softAPIP());
}

void Connection::disconnectAP()
{
	WiFi.softAPdisconnect(true);
}

void Connection::disconnectAPProm()
{
	Serial.println("AP PROM DISCONN 1");
	esp_wifi_set_promiscuous(false);
	esp_wifi_set_promiscuous_rx_cb(nullptr);

	wifi_promiscuous_filter_t filter = {};
	filter.filter_mask = WIFI_PROMIS_FILTER_MASK_ALL;
	esp_wifi_set_promiscuous_filter(&filter);
	WiFi.softAPdisconnect();
}

void Connection::initAPProm()
{
	Serial.print(" AP PROM:");
	WiFi.mode(WIFI_AP);
	if (!WiFi.softAP("Listen", "123456789", 10, 1, 4))
	{
		Serial.println("Can't create AP");
		return;
	}
	Serial.print("created AP:");
	Serial.print(WiFi.softAPIP());
	const wifi_promiscuous_filter_t filter = {
		.filter_mask = WIFI_EVENT_MASK_AP_PROBEREQRECVED};

	esp_wifi_set_promiscuous_filter(&filter);
	esp_wifi_set_promiscuous(true);
	esp_wifi_set_promiscuous_rx_cb(&ProbeRequest::requestCallback);
}

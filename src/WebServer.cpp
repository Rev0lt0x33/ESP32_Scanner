#include "WebServer.h"
#include "WebsiteBuilder.h"

bool WebServer::_loggedIn = false;

WebServer::WebServer()
{

	_server = new AsyncWebServer(80);
	// Debug::setLocalServer();

	if (MemMap::getInstance().getConfigurationFlag() == 0)
		Connection::getInstance().initAP();
	if (MemMap::getInstance().getConfigurationFlag() == 1)
		Connection::getInstance().initWiFi();

	_server->on("/", HTTP_GET, [](AsyncWebServerRequest *request)
				{ handleRoot(request); });

	_server->on("/login", HTTP_POST, [](AsyncWebServerRequest *request)
				{ handleLogin(request); });
	_server->on("/networkconfig", HTTP_POST, [](AsyncWebServerRequest *request)
				{ handleConfigData(request); });
	_server->on("/deviceconfig", HTTP_POST, [](AsyncWebServerRequest *request)
				{ handleDeviceData(request); });
	_server->onNotFound([](AsyncWebServerRequest *request)
						{ handleNotFound(request); });
	_server->on("/configuration", HTTP_GET, [](AsyncWebServerRequest *request)
				{ handleConfigurationPage(request); });
	_server->on("/logout", HTTP_GET, [](AsyncWebServerRequest *request)
				{ handleLogout(request); });
	_server->on("/reset", HTTP_GET, [](AsyncWebServerRequest *request)
				{ handleReset(request); });
	_server->on("/restart", HTTP_GET, [](AsyncWebServerRequest *request)
				{ handleRestart(request); });
	_server->on("/config.css", HTTP_GET, [](AsyncWebServerRequest *request)
				{ handleCss(request); });

	_server->begin();
	Serial.println("Server Running");
}

WebServer::~WebServer()
{
	Connection::getInstance().disconnectWiFi();
	_server->end();
	delete _server;
	Serial.println("Server Shutdown");
}

void WebServer::handleRoot(AsyncWebServerRequest *request)
{
	if (_loggedIn)
	{
		request->redirect("/configuration");
	}

	request->send(SPIFFS, "/Index.html", String(), false, nullptr);
}

void WebServer::handleLogin(AsyncWebServerRequest *request)
{
	request->redirect("/");
	if (!request->hasParam("login"), true)
		request->redirect("/");
	if (!request->hasParam("password"), true)
		request->redirect("/");

	String InputLogin = request->getParam("login", true)->value();
	String InputPassword = request->getParam("password", true)->value();
	String password = MemMap::getInstance().getDevicePassword();
	String login = MemMap::getInstance().getDeviceLogin();

	if (InputLogin.equals(login) && InputPassword.equals(password))
	{
		_loggedIn = true;
	}

	request->send(200);
}

void WebServer::handleConfigData(AsyncWebServerRequest *request)
{

	if (!_loggedIn)
		request->redirect("/");

	if (!request->hasParam("serverIP", true) || request->getParam("serverIP", true)->value().length() == 0)
		request->redirect("/");
	if (!request->hasParam("ApiKey", true) || request->getParam("ApiKey", true)->value().length() == 0)
		request->redirect("/");
	String apiKey = request->getParam("ApiKey", true)->value();
	MemMap::getInstance().setApiKey(apiKey);
	String serverIP = request->getParam("serverIP", true)->value();
	MemMap::getInstance().setServerIP(serverIP);
	if (!request->hasParam("ssid", true) || request->getParam("ssid", true)->value().length() == 0)
		request->redirect("/");
	if (!request->hasParam("password", true) || request->getParam("password", true)->value().length() == 0)
		request->redirect("/");

	String ssid = request->getParam("ssid", true)->value();
	String password = request->getParam("password", true)->value();
	MemMap::getInstance().getInstance().setSSID(ssid);
	MemMap::getInstance().setSSIDPassword(password);

	Serial.println(MemMap::getInstance().getApiKey());

	if (MemMap::getInstance().getConfigurationFlag() == false)
	{
		MemMap::getInstance().setConfigurationFlag(1);
	}

	request->redirect("/configuration");
}

void WebServer::handleDeviceData(AsyncWebServerRequest *request)
{
	if (!_loggedIn)
		request->redirect("/");

	if (request->hasParam("DeviceName", true) || request->getParam("DeviceName", true)->value().length() != 0)
	{
		String deviceName = request->getParam("DeviceName", true)->value();
		MemMap::getInstance().setDeviceName(deviceName);
	}

	if (!request->hasParam("DeviceLogin", true) || request->getParam("DeviceLogin", true)->value().length() == 0)
		request->redirect("/Configuration");
	if (!request->hasParam("DevicePassword", true) || request->getParam("DevicePassword", true)->value().length() == 0)
		request->redirect("/Configuration");

	String deviceLogin = request->getParam("DeviceLogin", true)->value();
	String devicePassword = request->getParam("DevicePassword", true)->value();

	MemMap::getInstance().setDeviceLogin(deviceLogin);
	MemMap::getInstance().setDevicePassword(devicePassword);

	request->redirect("/configuration");
}

void WebServer::handleNotFound(AsyncWebServerRequest *request)
{
	request->redirect("/");
}

void WebServer::handleCss(AsyncWebServerRequest *request)
{
	Serial.println("test");
	request->send(SPIFFS, "/config.css", "text/css");
}

void WebServer::handleConfigurationPage(AsyncWebServerRequest *request)
{
	if (!_loggedIn)
		request->redirect("/");

	WebsiteBuilder *wb = new WebsiteBuilder();

	request->send(SPIFFS, "/Config.html", String(), false, wb->generateLoginPage);
	delete wb;
	Serial.println("delete wb cfg");
}

void WebServer::handleLogout(AsyncWebServerRequest *request)
{
	if (_loggedIn)
	{
		_loggedIn = false;
	}
	request->redirect("/");
}

void WebServer::handleReset(AsyncWebServerRequest *request)
{
	if (!_loggedIn)
	{
		request->redirect("/");
	}
	_loggedIn = false;

	if (MemMap::getInstance().getConfigurationFlag() == true)
	{
		MemMap::getInstance().factorySetup();
	}

	request->redirect("/");
}

void WebServer::handleRestart(AsyncWebServerRequest *request)
{
	if (!_loggedIn)
	{
		request->redirect("/");
	}
	_loggedIn = false;
	request->redirect("/");
	ESP.restart();
}
#include "Manager.h"

Manager::Manager(int pin, int time)
{
    if (!SPIFFS.begin(true))
    {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    buttonPin = pin;
    buttonPressStartTime = 0;
    buttonHoldTimeReq = time;
    buttonState = LOW;
    lastButtonState = LOW;
    buttonPressStartTime = 0;
    dataSendTimeInterval = 60000;
    prevDataSendTime = 0;
    pinMode(buttonPin, INPUT);
    pinMode(BUILTIN_LED, OUTPUT);
    digitalWrite(BUILTIN_LED, LOW);

    if (MemMap::getInstance().getConfigurationFlag() == 0)
    {
        MemMap::getInstance().factorySetup();
        runServer();
        digitalWrite(BUILTIN_LED, HIGH);
    }

    if (MemMap::getInstance().getConfigurationFlag() == 1)
    {
        requestCapture = new ProbeRequest();
    }
}

void Manager::runServer()
{
    if (requestCapture != nullptr)
    {
        stopCapture();
    }
    confRun = 1;
    webServer = new WebServer();
}

void Manager::runCapture()
{
    if (webServer != nullptr)
    {
        stopServer();
    }
    confRun = 0;
    requestCapture = new ProbeRequest();
}

void Manager::stopServer()
{
    delete webServer;
    webServer = nullptr;
}

void Manager::stopCapture()
{
    delete requestCapture;
    requestCapture = nullptr;
}

bool Manager::isConfRunning()
{
    return confRun;
}

void Manager::buttonListen()
{

    buttonState = digitalRead(buttonPin);
    if (buttonState != lastButtonState)
    {
        if (buttonState == HIGH)
        {
            buttonPressStartTime = millis();
        }
        else
        {

            unsigned long holdDuration = millis() - buttonPressStartTime;
            if (holdDuration >= buttonHoldTimeReq)
            {
                if (isConfRunning() == 0)
                {
                    digitalWrite(BUILTIN_LED, HIGH);
                    runServer();
                }
                else
                {
                    digitalWrite(BUILTIN_LED, LOW);
                    runCapture();
                }
            }
        }
    }
    lastButtonState = buttonState;
}

void Manager::dataCheck()
{
    if (requestCapture->macCount == 20)
    {
        stopCapture();
        requestCapture->sendData();
        runCapture();
    }
    currentMillis = millis();
    if (currentMillis - prevDataSendTime >= dataSendTimeInterval)
    {
        prevDataSendTime = currentMillis;
        stopCapture();
        requestCapture->sendData();
        runCapture();
    }
}
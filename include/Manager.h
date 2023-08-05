#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "WebServer.h"
#include "ProbeRequest.h"

class Manager
{
private:
    WebServer *webServer = nullptr;
    ProbeRequest *requestCapture = nullptr;
    bool confRun = false;
    int buttonPin;
    int buttonState;
    int lastButtonState;
    unsigned long buttonPressStartTime;
    unsigned long buttonHoldTimeReq;
    unsigned long prevDataSendTime;
    unsigned long dataSendTimeInterval;
    Manager();

public:
    void runServer();
    void runCapture();
    void stopServer();
    void stopCapture();
    bool isConfRunning();
    void buttonListen();
    void dataCheck();
    Manager(int pin, int time);
};

#endif
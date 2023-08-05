#ifndef _CONNECTION_H
#define _CONNECTION_H

#include "WiFi.h"
#include "esp_wifi.h"
#include "MemoryMap.h"
#include "ProbeRequest.h"

class Connection{
    private:
    Connection(){
        
        }
    public:
        
        Connection(const Connection&) = delete;
        Connection& operator=(const Connection&) = delete;

        static Connection& getInstance() {
            static Connection instance;
            return instance;
        }
        void disconnectWiFi();
        void initWiFi();
        void initAP();
        void initAPProm();
        void disconnectAPProm();
        void disconnectAP();
};




#endif
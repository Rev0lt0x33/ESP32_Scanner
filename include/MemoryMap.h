
#ifndef _EEPROM_MAP_H
#define _EEPROM_MAP_H

// EEPROM data
#include <EEPROM.h>

class MemMap
{
private:
    const unsigned int _eepromSize = 256;
    // Memory addr
    // Flags
    const bool _configurationFlag = 0;

    //
    const unsigned int _deviceLogin = 1;
    const unsigned int _devicePassword = 33;
    const unsigned int _ssid = 65;
    const unsigned int _ssidPassword = 97;
    const unsigned int _serverIP = 129;
    const unsigned int _deviceName = 161;
    const unsigned int _apiKey = 193;
    MemMap()
    {
        EEPROM.begin(_eepromSize);
        Serial.println("EEPROM INIT");
    }

public:
    MemMap(const MemMap &) = delete;
    MemMap &operator=(const MemMap &) = delete;

    static MemMap &getInstance()
    {
        static MemMap instance;
        return instance;
    }

    String getDeviceLogin()
    {
        return EEPROM.readString(_deviceLogin);
    }
    void setDeviceLogin(String deviceLogin)
    {
        EEPROM.writeString(_deviceLogin, deviceLogin);
        EEPROM.commit();
    }

    bool getConfigurationFlag()
    {
        return EEPROM.readBool(_configurationFlag);
    }
    void setConfigurationFlag(bool configurationFlag)
    {
        EEPROM.writeBool(_configurationFlag, configurationFlag);
        EEPROM.commit();
    }
    String getDevicePassword()
    {
        return EEPROM.readString(_devicePassword);
    }
    void setDevicePassword(String devicePassword)
    {
        EEPROM.writeString(_devicePassword, devicePassword);
        EEPROM.commit();
    }

    String getSSID()
    {
        return EEPROM.readString(_ssid);
    }
    void setSSID(String ssid)
    {
        EEPROM.writeString(_ssid, ssid);
        EEPROM.commit();
    }

    String getSSIDPassword()
    {
        return EEPROM.readString(_ssidPassword);
    }
    void setSSIDPassword(String ssidPassword)
    {
        EEPROM.writeString(_ssidPassword, ssidPassword);
        EEPROM.commit();
    }

    String getServerIP()
    {
        return EEPROM.readString(_serverIP);
    }
    void setServerIP(String serverIP)
    {
        EEPROM.writeString(_serverIP, serverIP);
        EEPROM.commit();
    }

    String getDeviceName()
    {
        return EEPROM.readString(_deviceName);
    }
    void setDeviceName(String deviceName)
    {
        EEPROM.writeString(_deviceName, deviceName);
        EEPROM.commit();
    }
    String getApiKey()
    {
        return EEPROM.readString(_apiKey);
    }
    void setApiKey(String apiKey)
    {
        EEPROM.writeString(_apiKey, apiKey);
        EEPROM.commit();
    }

    void factorySetup()
    {
        setDeviceLogin("admin");
        setDevicePassword("admin");
        setSSID("ConfigureMe");
        setSSIDPassword("Admin12345");
        setDeviceName("");
        setServerIP("");
        setApiKey("");
        setConfigurationFlag(0);
        Serial.println("Mem Flush");
    }
};

#endif
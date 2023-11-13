#ifndef WifiHelper_H
#define WifiHelper_H

#include <Arduino.h>
#include <WiFiManager.h>

class WifiHelper
{
private:
    char _ssid[32];
    // void configCallback(WiFiManager *myWiFiManager);
public:
    WifiHelper(char* apName);
    ~WifiHelper();
    WiFiManager wm;
    void begin();
    void resetSetting();
    void startWifiManager(bool forceConfig);
};


#endif
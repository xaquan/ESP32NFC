#ifndef WifiHelper_H
#define WifiHelper_H

#include <Arduino.h>
#include <WiFiManager.h>
#include "config.h"

class WifiHelper
{
private:
    // void configCallback(WiFiManager *myWiFiManager);
public:
    WifiHelper();
    ~WifiHelper();
    WiFiManager wm;
    void begin();
    void resetSetting();
    void startWifiManager(bool forceConfig);
};


#endif
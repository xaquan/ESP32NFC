#include "wifiHelper.h"

bool wm_nonblocking = false; // change to true to use non blocking

WiFiManagerParameter custom_field;

void saveParamCallback();
int timeout = 120;

WifiHelper::WifiHelper()
{

}

WifiHelper::~WifiHelper()
{
}

/// @brief Setting up wifi
void WifiHelper::begin(){    
    Serial.println("\n Wifi Initializing...");
    WiFi.mode(WIFI_STA);
    startWifiManager(false);
}

/// @brief Reset wifi setting, erase wifi credential.
void WifiHelper::resetSetting(){
  wm.resetSettings();
}


/// @brief Start wifi manager portal. Where use can choose wifi network and enter password. After connecting to network. It will store credential to reconnect to wifi nextime.
/// @param forceConfig 
void WifiHelper::startWifiManager(bool forceConfig){
    bool res;   
    wm.setConnectTimeout(timeout);
    if(forceConfig){
      res = wm.startConfigPortal(DEVICE_SSID);
    }else{            
      res = wm.autoConnect(DEVICE_SSID);
    }    

    if(!res) {
      Serial.println("Failed to connect or hit timeout");
      delay(3000);
      ESP.restart();
      delay(5000);
    } 
    else {
      //if you get here you have connected to the WiFi    
      Serial.printf("Connected to %s\n", wm.getWiFiSSID());
    }
}

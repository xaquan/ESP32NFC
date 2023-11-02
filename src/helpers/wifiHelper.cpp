#include "wifiHelper.h"

#define WIFI_SSID "NETGEAR44"
#define WIFI_PASSWORD "elatedbanana167"

WifiHelper::WifiHelper(){

}

WifiHelper::WifiHelper(int data){
    Serial.printf("dsdsds $d", data);
}


void WifiHelper::begin(){
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();
}

int test(){
    return 100;
}
#if !defined(MET_GLOBAL)
#define MET_GLOBAL

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>
#include <helpers/helpers.h>
#include <NTPClient.h>
#include "config.h"

class MetGlobal
{
private:
    // NTPClient _timeClient;    
    bool loggedIn = false;
public:
    MetGlobal(/* args */);
    ~MetGlobal();

    void LogInSuccess();
    void LogOut();
    bool isLogged();
    // NTPClient getnNTPClient();
    // void setNTPClient(NTPClient timeClient);
};

#endif // MET_GLOBAL

#ifndef WifiHelper_H
#define WifiHelper_H

#include <Arduino.h>
#include <WiFi.h>

// namespace Helpers
// {
//     class WifiHelper;

// }

class WifiHelper
{
    private:

    public:
        WifiHelper();
        WifiHelper(int data);
        void begin();
        int test();

};

#endif
#include <map>
#include <iostream>
#include <Arduino.h>

class DelayHelper
{
private:
    std::map<char*, int*> _timerMap;
    bool isTimerExist(char* delayName);
public:
    DelayHelper(/* args */);
    ~DelayHelper();
    void delay(char* delayName);
    void newDelay(char* delayName, int miliseconds);
};




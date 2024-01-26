#include "blinkerHelper.h"

BlinkerHelper::BlinkerHelper(/* args */)
{
}

BlinkerHelper::~BlinkerHelper()
{
}

void BlinkerHelper::addBlinker(int pin, int milisecond)
{
    _blinkerHash[pin] = milisecond;
}

bool BlinkerHelper::isExisted(int pin)
{
    return _blinkerHash.find(pin) != _blinkerHash.end();
}

void BlinkerHelper::startBlinking()
{
    for (Blinker::iterator led = _blinkerHash.begin(); led != _blinkerHash.end(); ++led)
    {
        /* code */
    }
    
}
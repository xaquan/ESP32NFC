#if !defined(BLINKERHELPER_H)
#define BLINKERHELPER_H

#include <map>
#include <WString.h>
#include <Arduino.h>
typedef std::map<int, int> Blinker;

class BlinkerHelper
{
private:
    /* data */
    
    Blinker _blinkerHash;
    

public:
    BlinkerHelper(/* args */);
    ~BlinkerHelper();

    void addBlinker(int pin, int milisecond);
    bool isExisted(int pin);
    void startBlinking();
};






#endif // BLINKERHELPER_H

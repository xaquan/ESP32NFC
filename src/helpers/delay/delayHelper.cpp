#include "delayHelper.h"


DelayHelper::DelayHelper(/* args */)
{
}

DelayHelper::~DelayHelper()
{
}


void DelayHelper::delay(char* delayName){
     if(!isTimerExist(delayName)){
        std::cerr << "Error: delay does not exist.";
        return;
    }

    _timerMap[delayName];
}

void DelayHelper::newDelay(char* delayName, int miliseconds){
    if(isTimerExist(delayName)){
        std::cerr << "Error: delayName existed.";
        return;
    }

    int times[2]={millis(), miliseconds};
    _timerMap[delayName] = times;
}

bool DelayHelper::isTimerExist(char* delayName){    
    return _timerMap.find(delayName) != _timerMap.end();
}
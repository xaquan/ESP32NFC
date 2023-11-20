#ifndef SCANLOGOBJ_H
#define SCANLOGOBJ_H

#include "firebaseConfig.h"
#include <iostream>
#include <ctime>

class ScanLogObj
{
private:
    /* data */
public:
    ScanLogObj(char* cardId, char* deviceId, int scannedTime = time(0));
    ScanLogObj(char* uuid, char* cardId, char* deviceId, int scannedTime);
    ~ScanLogObj();
    char* uuid;
    char* cardId;
    int scannedTime;
    char* deviceId;
};

ScanLogObj::ScanLogObj(char* cardId, char* deviceId, int scannedTime /*=CurrentTime*/)
{    
    this->cardId = cardId;
    this->deviceId = deviceId;
    this->scannedTime = scannedTime;
}

ScanLogObj::ScanLogObj(char* uuid, char* cardId, char* deviceId, int scannedTime)
{    
    this->uuid = uuid;
    ScanLogObj(cardId, deviceId, scannedTime);
}


ScanLogObj::~ScanLogObj()
{
}


#endif
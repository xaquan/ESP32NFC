#if !defined(SCAN_LOG_MODEL_H)
#define SCAN_LOG_MODEL_H

#include "scanLogObj.h"

class ScanLogModel
{
private:
    /* data */
public:
    ScanLogModel(/* args */);
    ~ScanLogModel();
    ScanLogObj getLog(char* uuid);
    void addLog(ScanLogObj scanLog);
};

ScanLogObj ScanLogModel::getLog(char* uuid){
    struct ScanLogObj res;

    return res;
}

void ScanLogModel::addLog(ScanLogObj scanLog){
    
}

ScanLogModel::ScanLogModel(/* args */)
{
}

ScanLogModel::~ScanLogModel()
{
}


#endif // SCAN_LOG_MODEL_H

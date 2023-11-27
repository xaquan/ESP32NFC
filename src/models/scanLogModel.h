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
    scanLogObj getLog(char* uuid);
    void addLog(scanLogObj scanLog);
};

scanLogObj ScanLogModel::getLog(char* uuid){
    struct scanLogObj res;

    return res;
}

void ScanLogModel::addLog(scanLogObj scanLog){
    
}

ScanLogModel::ScanLogModel(/* args */)
{
}

ScanLogModel::~ScanLogModel()
{
}


#endif // SCAN_LOG_MODEL_H

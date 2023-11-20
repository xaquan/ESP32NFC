#if !defined(SCAN_LOG_MODEL_H)
#define SCAN_LOG_MODEL_H

#include "firebaseConfig.h"
#include "scanLogObj.h"

class ScanLogModel
{
private:
    /* data */
public:
    ScanLogModel(/* args */);
    ~ScanLogModel();
    ScanLogObj getLog();
    void addLog(ScanLogObj obj);
};

ScanLogObj ScanLogModel::getLog(){

}

void ScanLogModel::addLog(ScanLogObj obj){
    
}

ScanLogModel::ScanLogModel(/* args */)
{
}

ScanLogModel::~ScanLogModel()
{
}


#endif // SCAN_LOG_MODEL_H

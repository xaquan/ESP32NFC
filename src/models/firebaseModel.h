#if !defined(FIREBASE_MODEL_H)
#define FIREBASE_MODEL_H

#include "firebaseConfig.h"
#include <Firebase_ESP_Client.h>
// #include "scanLogObj.h"

class FirebaseModel
{
private:
    /* data */
public:
    FirebaseModel(/* args */);
    ~FirebaseModel();
    // void addDoc(ScanLogObj obj);
    void getDoc(char* uuid);    
};


#endif // FIREBASE_MODEL_H




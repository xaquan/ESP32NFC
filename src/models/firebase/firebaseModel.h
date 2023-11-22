#if !defined(FIREBASE_MODEL_H)
#define FIREBASE_MODEL_H

#include "firebaseConfig.h"
#include "..\..\config.h"

#include <Firebase_ESP_Client.h>
// #include "scanLogObj.h"

class FirebaseModel
{
private:
    /* data */
public:
    FirebaseModel(/* args */);
    ~FirebaseModel();
    void begin();
    void refreshToken();
    // void addDoc(ScanLogObj obj);
    void getDoc();   
    void addLog(String cardId); 
};


#endif // FIREBASE_MODEL_H




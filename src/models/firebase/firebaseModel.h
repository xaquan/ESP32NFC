#if !defined(FIREBASE_MODEL_H)
#define FIREBASE_MODEL_H

#define FIREBASE_API_KEY "AIzaSyDNWwWhBJYRc134Qrzk6EsB02NRoag_2to"
#define FIREBASE_AUTH_DOMAIN "cptc-met-iot.firebaseapp.com"
#define FIREBASE_PROJECT_ID "cptc-met-iot"
#define FIREBASE_STORAGE_BUCKET "cptc-met-iot.appspot.com"
#define FIREBASE_MESSAGING_SEDNER_ID "271377445440"
#define FIREBASE_APP_ID "1:271377445440:web:466b7edb4e6d8bd30965a5"

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
    void getDoc(char* uuid);    
};


#endif // FIREBASE_MODEL_H



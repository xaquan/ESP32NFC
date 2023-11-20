#include "firebaseModel.h"

#include <addons/TokenHelper.h>
#define FB_EMAIL "MET_Device@MET.shop"
#define FB_PASSWORD "Mach@nical"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void FirebaseModel::getDoc(char* uuid){
    String docPath = "Devices";

    if (Firebase.Firestore.getDocument(&fbdo, FIREBASE_PROJECT_ID, "", docPath.c_str(), ""))
    {
        Serial.println(fbdo.payload().c_str());
    }
    else
    {
        Serial.println(fbdo.errorReason());
    }
    
}

FirebaseModel::FirebaseModel(/* args */)
{        
    Serial.println("Connecting to Firebase...");
    auth.user.email = FB_EMAIL;
    auth.user.password = FB_PASSWORD;
    config.token_status_callback = tokenStatusCallback;
    Firebase.reconnectNetwork(true);
    fbdo.setBSSLBufferSize(4096, 1024);
    fbdo.setResponseSize(2048);
    Firebase.begin(&config, &auth);    
}

FirebaseModel::~FirebaseModel()
{
}


#include "firebaseModel.h"
#include <addons/TokenHelper.h>

#define FB_EMAIL "quanhuutrinhxa@gmail.com"
#define FB_PASSWORD "123456"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void FirebaseModel::begin(){
    Serial.println("Connecting to Firebase...");

    if(WiFi.status() == WL_CONNECTED){
        Serial.println("Authentication...");      
        auth.user.email = FB_EMAIL;
        auth.user.password = FB_PASSWORD;
        config.api_key = FIREBASE_API_KEY;
        config.token_status_callback = tokenStatusCallback;
        config.max_token_generation_retry = 5;
        Firebase.reconnectNetwork(true);
        fbdo.setBSSLBufferSize(4096, 1024);
        fbdo.setResponseSize(2048);
        Firebase.begin(&config, &auth);  

        Serial.println("Getting User UID");
        while ((auth.token.uid) == "") {
            Serial.print('.');
            delay(1000);
        }  

        String uid = auth.token.uid.c_str();
        Serial.printf("User UID: %s\n", uid);
    }
}

void FirebaseModel::refreshToken(){
    if (Firebase.isTokenExpired()){
        Firebase.refreshToken(&config);
        Serial.println("Refresh token");
    }
}

void FirebaseModel::getDoc(String uuid){
    String docPath = "/Logs/oCagQxLsuIKpEQN4eTfO";
    if (Firebase.Firestore.getDocument(&fbdo, FIREBASE_PROJECT_ID, "", docPath.c_str()))
        Serial.printf("Get\n%s\n\n", fbdo.payload().c_str());
    else
        Serial.println(fbdo.errorReason());
}

void FirebaseModel::addDoc(struct scanLogObj scanLog){
    // String docPath = "Logs";
    FirebaseJson content;

    Serial.printf("Card Id %s\n", scanLog.cardId);
    Serial.printf("Device Id %s\n", scanLog.deviceId);

    content.set("fields/CardId/stringValue", scanLog.cardId);
    content.set("fields/DeviceId/stringValue", scanLog.deviceId);    
    // content.set("fields/TimeStamp/timestampValue", scanLog.timeStamp);


    content.toString(Serial, true);

    Serial.print("Adding log... ");
    if(Firebase.Firestore.createDocument(&fbdo, FIREBASE_PROJECT_ID, "", PATH_LOGS, content.raw())){
        FirebaseJson data;
        data.setJsonData(fbdo.payload());

        // Serial.printf("Add\n%s\n\n", data.valueAt(0));

    }else{
        Serial.println(fbdo.errorReason());
    }
}



FirebaseModel::FirebaseModel(/* args */)
{        
}

FirebaseModel::~FirebaseModel()
{
}

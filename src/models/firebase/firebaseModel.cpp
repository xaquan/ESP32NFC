#include "firebaseModel.h"
#include <addons/TokenHelper.h>
#include <WiFiManager.h>
#include <Arduino.h>
#define FB_EMAIL "quanhuutrinhxa@gmail.com"
#define FB_PASSWORD "123456"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;


bool taskCompleted = false;

unsigned long dataMillis = 0;
// void FirebaseModel::getDoc(char* uuid){
//     String docPath = "Devices";

//     if (Firebase.Firestore.getDocument(&fbdo, FIREBASE_PROJECT_ID, "", docPath.c_str(), ""))
//     {
//         Serial.println(fbdo.payload().c_str());
//     }
//     else
//     {
//         Serial.println(fbdo.errorReason());
//     }
    
// }

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

void FirebaseModel::getDoc(){
    // String docPath = "/Logs/oCagQxLsuIKpEQN4eTfO";
    // if (Firebase.Firestore.getDocument(&fbdo, FIREBASE_PROJECT_ID, "", docPath.c_str()))
    //     Serial.printf("Get\n%s\n\n", fbdo.payload().c_str());
    // else
    //     Serial.println(fbdo.errorReason());

    Serial.print("Get document... ");
    if (Firebase.ready() && (millis() - dataMillis > 60000 || dataMillis == 0))
    {
        dataMillis = millis();

        if (!taskCompleted)
        {
            taskCompleted = true;

                      
            // info is the collection id, countries is the document id in collection info.
            String documentPath = "info/countries";
            std::vector<struct firebase_firestore_document_write_t> writes;

            struct firebase_firestore_document_write_t transform_write;
            
            transform_write.type = firebase_firestore_document_write_type_transform;
            transform_write.document_transform.transform_document_path = "info";
            
            struct  firebase_firestore_document_write_field_transforms_t field_transforms;

            field_transforms.fieldPath = "timeStamp"                        ;
            field_transforms.transform_type = firebase_firestore_transform_type_set_to_server_value;
            field_transforms.transform_content = "REQUEST_TIME";

            transform_write.document_transform.field_transforms.push_back(field_transforms);            
            


            // struct firebase_firestore_document_write_t update_write;

            // update_write.type = firebase_firestore_document_write_type_update;

            // // For the usage of FirebaseJson, see examples/FirebaseJson/BasicUsage/Create_Edit_Parse/Create_Edit_Parse.ino
            FirebaseJson content;

            // content.set("fields/Japan/time_zone/integerValue", "9");
            // content.set("fields/Japan/population/integerValue", "125570000");

            // update_write.update_document_content = content.raw();
            // update_write.update_document_path = documentPath.c_str();

            writes.push_back(transform_write);
            // writes.push_back(update_write);
            

            // content.set("fields/Japan/mapValue/fields/time_zone/integerValue", "9");
            // content.set("fields/Japan/mapValue/fields/population/integerValue", "125570000");
            // content.set("fields/Japan/mapValue/fields/timeStamp/timestampValue", "2014-10-02T15:01:23.045123456Z");

            // content.set("fields/Belgium/mapValue/fields/time_zone/integerValue", "1");
            // content.set("fields/Belgium/mapValue/fields/population/integerValue", "11492641");
            // content.set("fields/Belgium/mapValue/fields/timeStamp/timestampValue/ServerValue.REQUEST_TIME");

            // content.set("fields/Singapore/mapValue/fields/time_zone/integerValue", "8");
            // content.set("fields/Singapore/mapValue/fields/population/integerValue", "5703600");
            // content.set("fields/Singapore/mapValue/fields/timeStamp/timestampValue", "ServerValue.REQUEST_TIME");

            

            // Serial.print("Create document... ");

             if (Firebase.Firestore.commitDocument(&fbdo, FIREBASE_PROJECT_ID, "" /* databaseId can be (default) or empty */, writes /* dynamic array of firebase_firestore_document_write_t */, "" /* transaction */))
                Serial.printf("ok\n%s\n\n", fbdo.payload().c_str());
            else
                Serial.println(fbdo.errorReason()); 

            // if (Firebase.Firestore.createDocument(&fbdo, FIREBASE_PROJECT_ID, "" /* databaseId can be (default) or empty */, documentPath.c_str(), content.raw()))
            //     Serial.printf("ok\n%s\n\n", fbdo.payload().c_str());
            // else
            //     Serial.println(fbdo.errorReason());
        }

        String documentPath = "info/countries";
        String mask = "Japan";

        // If the document path contains space e.g. "a b c/d e f"
        // It should encode the space as %20 then the path will be "a%20b%20c/d%20e%20f"

        Serial.print("Get a document... ");

        if (Firebase.Firestore.getDocument(&fbdo, FIREBASE_PROJECT_ID, "", documentPath.c_str(), mask.c_str()))
            Serial.printf("ok\n%s\n\n", fbdo.payload().c_str());
        else
            Serial.println(fbdo.errorReason());
    }

}

void FirebaseModel::addLog(String cardId){
    String docPath = "Logs";

    FirebaseJson content;

    Serial.printf("Card Id %s\n", cardId);
    Serial.printf("Device Id %s\n", DEVICE_ID);

    content.set("fields/CardId/stringValue", cardId);
    content.set("fields/DeviceId/stringValue", DEVICE_ID);    
    content.set("fields/TimeStamp/timestampValue", "ServerValue.TIMESTAMP");


    content.toString(Serial, true);

    Serial.print("Adding log... ");
    if(Firebase.Firestore.createDocument(&fbdo, FIREBASE_PROJECT_ID, "", docPath.c_str(), content.raw())){
        Serial.printf("Add\n%s\n\n", fbdo.payload().c_str());
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

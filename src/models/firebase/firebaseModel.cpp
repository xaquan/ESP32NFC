
#include "firebaseModel.h"
#include <addons/TokenHelper.h>
#include <string>

#define FB_EMAIL "equipmentaccess@met.cptc"
#define FB_PASSWORD "123456"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
// MetGlobal global;

// NTPClient timeClient = global.getnNTPClient();

WiFiUDP wifiUDP;
NTPClient timeClient(wifiUDP);

void FirebaseModel::begin()
{
    timeClient.begin();
    configTime(0, 0, "ntp.pool.org");

    Serial.println("Connecting to Firebase...");

    if (WiFi.status() == WL_CONNECTED)
    {
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
        while ((auth.token.uid) == "")
        {
            Serial.print('.');
            delay(1000);
        }

        String uid = auth.token.uid.c_str();
        Serial.printf("User UID: %s\n", auth.token.uid);
    }
}

void FirebaseModel::refreshToken()
{
    if (Firebase.isTokenExpired())
    {
        Firebase.refreshToken(&config);
        Serial.println("Refresh token");
    }
}

CardObj FirebaseModel::getUserByCardId(String cardId)
{
    String docPath = "Cards/";
    docPath += cardId;
    CardObj cardObj;

    if (Firebase.Firestore.getDocument(&fbdo, FIREBASE_PROJECT_ID, "", docPath.c_str()))
    {
        // Serial.printf("Get\n%s\n\n", fbdo.payload().c_str());
        FirebaseJson data;
        data.setJsonData(fbdo.payload());
        cardObj.cardId = cardId;

        FirebaseJsonData isActive;
        FirebaseJsonData userId;
        FirebaseJsonData cardId;
        FirebaseJsonData lastScanned;

        data.get(isActive, "fields/isActive/booleanValue");
        data.get(userId, "fields/userId/stringValue");
        data.get(cardId, "fields/cardId/stringValue");
        data.get(lastScanned, "fields/lastScanned/stringValue");

        if (lastScanned.success)
        {
            cardObj.isActive = isActive.boolValue;
            cardObj.cardId = cardId.stringValue;
            cardObj.userId = userId.stringValue;
            cardObj.lastScanned =lastScanned.stringValue;

            // Serial.println(cardObj.lastScanned);
        }
    }
    else
    {
        Serial.println("Not found");
        Serial.println(fbdo.errorReason());
    }

    return cardObj;
}

void FirebaseModel::addActivity(struct ScanLogObj scanLog)
{
    timeClient.update();
    // String docPath = "Logs";
    FirebaseJson content;

    // getUserByCardId(scanLog.cardId)

    unsigned long epochTime = timeClient.getEpochTime();

    Serial.println(timeClient.isTimeSet());

    // Convert to time structure
    struct tm *ptm = gmtime((time_t *)&epochTime);

    // Format as Zulu time
    char buffer[25];
    strftime(buffer, 25, "%FT%TZ", ptm);

    Serial.printf("Card Id %s\n", scanLog.cardId);
    Serial.printf("Device Id %s\n", scanLog.deviceId);

    content.set("fields/cardId/stringValue", scanLog.cardId);
    content.set("fields/deviceId/stringValue", scanLog.deviceId);
    content.set("fields/timestamp/timestampValue", buffer);

    content.toString(Serial, true);

    Serial.print("Adding log... ");
    if (Firebase.Firestore.createDocument(&fbdo, FIREBASE_PROJECT_ID, "", PATH_ACTIVITIES, content.raw()))
    {
        // FirebaseJson data;
        FirebaseJsonArray data;
        data.setJsonArrayData(fbdo.payload());

        Serial.println(data.raw());

        // FirebaseJson readDate;
        // // data.get(readDate, "createTime");
        // Serial.println(data.get(readDate, "fields/CardId"))
        // Serial.printf("Add\n%s\n\n", data);
    }
    else
    {
        Serial.println(fbdo.errorReason());
    }
}

FirebaseModel::FirebaseModel(/* args */)
{
}

FirebaseModel::~FirebaseModel()
{
}

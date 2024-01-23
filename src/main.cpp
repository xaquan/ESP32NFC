
#include <global.h>
#include "models/firebase/firebaseModel.h"

#define UNLOCK_PIN (23)
#define WIFI_RESET_PIN (32)
// MetGlobal global;
WifiHelper wifiHelper;
NFCHelper nfcHelper;
ButtonHelper btnHelper;
FirebaseModel fbModel;
// WiFiUDP wiFiUDP;
// NTPClient timeClient(wiFiUDP);



void SuccessReadCard(uint8_t uid[], uint8_t uidLength);
void CardProcessed();
void Unlock();
void startWifiConfig();

void setupPins(){
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(UNLOCK_PIN, OUTPUT);
  pinMode(WIFI_RESET_PIN, INPUT);
  // attachInterrupt(WIFI_RESET_PIN, resetWifi_btn_interrupt, PULLDOWN);  
}

void setup(void) {
  setupPins();  
  Serial.begin(115200);  
  Serial.setDebugOutput(true);
  Serial.println("Starting...");
  nfcHelper.begin();
  wifiHelper.begin();
  fbModel.begin();
}


// Main loop
void loop(void) {
  btnHelper.pressAndHold(WIFI_RESET_PIN, 2000, startWifiConfig);
  nfcHelper.ReadNFCCard(SuccessReadCard, 500);
}


void Unlock(int output){
  digitalWrite(UNLOCK_PIN, output);
}


void SuccessReadCard(uint8_t uid[], uint8_t uidLength){

  digitalWrite(LED_BUILTIN, HIGH);
  // Display some basic information about the card
    Serial.println("Found a card");
    Serial.print("  UID Length: ");Serial.print(uidLength, DEC);Serial.println(" bytes");
    Serial.print("  UID Value: ");
    nfcHelper.printHex(uid, uidLength);

      uint32_t cardid = uid[0];
      for (int i = 1; i < uidLength; i++)
      {
        cardid <<= 8;
        cardid |= uid[i];
      }
      Serial.print("Card #");
      Serial.println(cardid);

      if(Firebase.ready()){
        
        // fbModel.getDoc();

        CardObj cardObj = fbModel.getUserByCardId(String(cardid));
        if (cardObj.isActive)
        {
          CardProcessed();
        }

        ScanLogObj log;
        // sprintf(log.cardId, "%lu", cardid);
        log.deviceId = DEVICE_ID;
        log.userId = cardObj.userId;
        log.cardId = cardid;
        fbModel.addActivity(log);
        
      }
    
    
}

void CardProcessed(){
  Unlock(HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  Unlock(LOW);
}

void startWifiConfig(){  
  // wifiHelper.resetSetting();
  wifiHelper.startWifiManager(true);
}


void resetWifi_cancel(){
   Serial.println("cancel");
}

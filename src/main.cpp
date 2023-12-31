
#include <global.h>
#include "models/firebase/firebaseModel.h"

#define UNLOCK_PIN (23)
#define WIFI_RESET_PIN (13)
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
  // timeClient.begin();

  // global.setNTPClient(timeClient);
}


// Main loop
void loop(void) {
  // resetWifi_btn_press();
  btnHelper.pressAndHold(WIFI_RESET_PIN, 2000, startWifiConfig);
  nfcHelper.ReadNFCCard(SuccessReadCard, 100);
}


void Unlock(int output){
  digitalWrite(UNLOCK_PIN, output);
}


void SuccessReadCard(uint8_t uid[], uint8_t uidLength){


  digitalWrite(LED_BUILTIN, HIGH);
  // Display some basic information about the card
    Serial.println("Found an ISO14443A card");
    Serial.print("  UID Length: ");Serial.print(uidLength, DEC);Serial.println(" bytes");
    Serial.print("  UID Value: ");
    nfcHelper.printHex(uid, uidLength);

    // if (uidLength == 4)
    // {
      // We probably have a Mifare Classic card ...
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
        scanLogObj log;
        sprintf(log.cardId, "%lu", cardid);
        log.deviceId = DEVICE_ID;
        fbModel.addDoc(log);
      }
    // }
    
    CardProcessed();
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

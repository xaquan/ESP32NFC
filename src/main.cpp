#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>
#include <FirebaseESP32.h>
#include <helpers/wifiHelper.h>
#include <helpers/nfcHelper.h>

#define UNLOCK_PIN (23)

WifiHelper wifiHelper;
NFCHelper nfcHelper;

// uint8_t ReadNFCCard();
void SuccessReadCard(uint8_t uid[], uint8_t uidLength);
void CardProcessed();
void Unlock();

void setupPins(){
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(UNLOCK_PIN, OUTPUT);
}

void setup(void) {
  setupPins();  
  Serial.begin(9600);  
  Serial.setDebugOutput(true);  
  while (!Serial) delay(10); // for Leonardo/Micro/Zero

  Serial.println("Hello!");

  

  nfcHelper.begin();
  wifiHelper.begin();
}


void loop(void) {

  nfcHelper.ReadNFCCard(SuccessReadCard);
  
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

    if (uidLength == 4)
    {
      // We probably have a Mifare Classic card ...
      uint32_t cardid = uid[0];
      cardid <<= 8;
      cardid |= uid[1];
      cardid <<= 8;
      cardid |= uid[2];
      cardid <<= 8;
      cardid |= uid[3];
      Serial.print("Seems to be a Mifare Classic card #");
      Serial.println(cardid);
    }
    Serial.println("");
    // Unlock(HIGH);
    delay(1000);
}

void CardProcessed(){
  digitalWrite(LED_BUILTIN, LOW);
  Unlock(LOW);
}



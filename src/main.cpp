#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>
#include <FirebaseESP32.h>
#include <helpers/wifiHelper.h>


#define PN532_IRQ   (22)
#define PN532_RESET (21)  // Not connected by default on the NFC Shield
#define UNLOCK_PIN (23)

Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);
WifiHelper wifiHelper(1);


uint8_t ReadNFCCard();
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
  while (!Serial) delay(10); // for Leonardo/Micro/Zero

  Serial.println("Hello!");

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX);
  Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC);
  Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);

  Serial.println("Waiting for an ISO14443A Card ...");

  
  wifiHelper.begin();
}


void loop(void) {

  ReadNFCCard();
  
}

uint8_t ReadNFCCard(){
  uint8_t res;

  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (success) {
    SuccessReadCard(uid, uidLength);
    
    CardProcessed();
  }

  return res;
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
    nfc.PrintHex(uid, uidLength);

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
    Unlock(HIGH);
    delay(1000);
}

void CardProcessed(){
  digitalWrite(LED_BUILTIN, LOW);
  Unlock(LOW);
}



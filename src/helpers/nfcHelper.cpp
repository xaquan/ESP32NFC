#include "nfcHelper.h"

#define PN532_IRQ   (22)
#define PN532_RESET (21)  // Not connected by default on the NFC Shield

Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);

NFCHelper::NFCHelper(/* args */)
{
}

NFCHelper::~NFCHelper()
{
}


void NFCHelper::begin(){
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
}

void NFCHelper::printHex(const byte *data, uint32_t numBytes){
    nfc.PrintHex(data, numBytes);
}

uint8_t NFCHelper::ReadNFCCard(void (*callback)(uint8_t uid[], uint8_t uidLength)){
  uint8_t res;

  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (success) {
    callback(uid, uidLength);    
    // CardProcessed();
  }

  return res;
}



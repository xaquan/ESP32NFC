#ifndef NFC_Helper_H
#define NFC_Helper_H

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>

class NFCHelper
{
private:
    /* data */
    void SuccessReadCard(uint8_t uid[], uint8_t uidLength);
public:
    NFCHelper(/* args */);
    ~NFCHelper();
    void begin();
    void printHex(const byte *data, uint32_t numBytes);
    void ReadNFCCard(void (*callback)(uint8_t uid[], uint8_t uidLength), uint16_t timeout = 0);
} ;


#endif


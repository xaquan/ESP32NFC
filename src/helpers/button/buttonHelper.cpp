#include "buttonHelper.h"

/**
 * @brief Destroy the Button Helper:: Button Helper object
 * 
 */
ButtonHelper::~ButtonHelper()
{
}


void ButtonHelper::read(){
 
    
}

/** 
 * @brief if the button is pressed and held for amount of second.
 * @param pin Button pin number.
 * @param holdDuration Call the callback function after a set duration, in miliseconds.
 * @param callback Callback function
 * @param detectionState What state of the button will it detect for? LOW or HIGH
*/
void ButtonHelper::pressAndHold(uint8_t pin, uint16_t holdDuration, void (*callback)(),uint8_t detectionState /*=HIGH*/){
    uint8_t btnState = digitalRead(pin);
    
    if(btnState == detectionState){
        if(!isBtnExist(pin)){
            
            Serial.printf("Button is holding...");
            _btnTracker[pin] = millis();
        }else{            
            if (millis()-_btnTracker[pin] >= holdDuration)
            {
                
                Serial.printf("Held for %d miliseconds.\n", holdDuration);
                removeBtn(pin);
                callback();
            }            
        }
    }else{
        if(isBtnExist(pin)){
            Serial.println("Button released.");
            removeBtn(pin);
        }
    }
}

bool ButtonHelper::isBtnExist(uint8_t pin){
    return _btnTracker.find(pin) != _btnTracker.end();
}

void ButtonHelper::removeBtn(u_int8_t pin){
    
    _btnTracker.erase(pin);
}

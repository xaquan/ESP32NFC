#include <iostream>
#include <map>
#include <Arduino.h>
#include <vector>

class ButtonHelper
{
private:
    std::map<int, int> _btnTracker;
    bool isBtnExist(u_int8_t pin);
    void removeBtn(u_int8_t pin);

public:
    ~ButtonHelper();
    void read();
    void pressAndHold(uint8_t pin, uint16_t holdDuration, void (*callback)(), uint8_t detectionState = HIGH);
};

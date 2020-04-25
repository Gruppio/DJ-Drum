#ifndef CORE_H
#define CORE_H

#include <Arduino.h>
#include <TM1637Display.h>
#include <Adafruit_NeoPixel.h>

class Core {
public:
    Core();
    void padPressed(int pad);
    void padReleased(int pad);
    void updateDisplay();
    
protected:
    uint8_t numberOfPadsCurrentlyPressed;
    // unsigned long previousDuration;
    // bool isRisen;
    // bool isFallen;
    // int threshold;
    // uint16_t debounceTimeMillis;
    // unsigned long lastChangedTime;
    // uint8_t previousPressedState;
    // uint8_t pin;
};

#endif

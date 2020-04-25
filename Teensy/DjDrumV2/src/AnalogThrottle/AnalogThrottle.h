#ifndef ANALOG_THROTTLE_H
#define ANALOG_THROTTLE_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif

class AnalogThrottle
{
public:
    AnalogThrottle();
    AnalogThrottle(int pin);
    AnalogThrottle(int pin, uint16_t interval_millis);
    AnalogThrottle(int pin, uint16_t interval_millis, int threshold);
    void attach(int pin);
    void setThreshold(int threshold);
    void interval(uint16_t interval_millis);
    bool update();
    bool fell();
    bool rose();
    bool changed();
    bool read();
    unsigned long duration();

protected:
    unsigned long previousDuration;
    bool isRisen;
    bool isFallen;
    int threshold;
    uint16_t debounceTimeMillis;
    unsigned long lastChangedTime;
    uint8_t previousPressedState;
    uint8_t pin;
};

#endif

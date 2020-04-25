#include "AnalogThrottle.h"

AnalogThrottle::AnalogThrottle() : previousDuration(0),
                                   isRisen(false),
                                   isFallen(false),
                                   debounceTimeMillis(50),
                                   lastChangedTime(0),
                                   previousPressedState(0),
                                   pin(0) {}

AnalogThrottle::AnalogThrottle(int pin) : previousDuration(0),
                                          isRisen(false),
                                          isFallen(false),
                                          debounceTimeMillis(50),
                                          lastChangedTime(0),
                                          previousPressedState(0),
                                          pin(pin)
{
    attach(pin);
}

AnalogThrottle::AnalogThrottle(int pin, uint16_t interval_millis) : previousDuration(0),
                                                                    isRisen(false),
                                                                    isFallen(false),
                                                                    debounceTimeMillis(50),
                                                                    lastChangedTime(0),
                                                                    previousPressedState(0),
                                                                    pin(pin)
{
    attach(pin);
    interval(interval_millis);
}

AnalogThrottle::AnalogThrottle(int pin, uint16_t interval_millis, int threshold) : previousDuration(0),
                                                                                   isRisen(false),
                                                                                   isFallen(false),
                                                                                   debounceTimeMillis(50),
                                                                                   lastChangedTime(0),
                                                                                   previousPressedState(0),
                                                                                   pin(pin)
{
    attach(pin);
    interval(interval_millis);
    setThreshold(threshold);
}

void AnalogThrottle::attach(int pin)
{
    this->pin = pin;
    previousPressedState = 0;
    pinMode(pin, INPUT);
}

void AnalogThrottle::interval(uint16_t debounceTimeMillis)
{
    this->debounceTimeMillis = debounceTimeMillis;
}

void AnalogThrottle::setThreshold(int threshold)
{
    this->threshold = threshold;
}

bool AnalogThrottle::fell()
{
    return isFallen;
}

bool AnalogThrottle::rose()
{
    return isRisen;
}

bool AnalogThrottle::changed()
{
    return fell() || rose();
}

bool AnalogThrottle::read()
{
    return previousPressedState;
}

unsigned long AnalogThrottle::duration()
{
    return previousDuration;
}

bool AnalogThrottle::update()
{
    isRisen = false;
    isFallen = false;
    unsigned long currentTime = millis();
    if (currentTime - lastChangedTime > debounceTimeMillis)
    {
        bool isPressedState = analogRead(pin) >= threshold;

        if (isPressedState == previousPressedState)
            return false;

        if (isPressedState)
        {
            isFallen = true;
        }
        else
        {
            isRisen = true;
        }

        previousDuration = currentTime - lastChangedTime;
        lastChangedTime = currentTime;
        previousPressedState = isPressedState;
        return true;
    }
    return false;
}
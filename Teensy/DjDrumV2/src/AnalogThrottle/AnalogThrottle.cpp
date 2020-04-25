#include "AnalogThrottle.h"

AnalogThrottle::AnalogThrottle() : previousDuration(0),
                                   isRisen(false),
                                   isFallen(false),
                                   debounceTimeMillis(50),
                                   lastChangedTime(0),
                                   previousAboveThresholdState(0),
                                   pin(0) {}

AnalogThrottle::AnalogThrottle(int pin) : previousDuration(0),
                                          isRisen(false),
                                          isFallen(false),
                                          debounceTimeMillis(50),
                                          lastChangedTime(0),
                                          previousAboveThresholdState(0),
                                          pin(pin)
{
    attach(pin);
}

AnalogThrottle::AnalogThrottle(int pin, uint16_t interval_millis) : previousDuration(0),
                                                                    isRisen(false),
                                                                    isFallen(false),
                                                                    debounceTimeMillis(50),
                                                                    lastChangedTime(0),
                                                                    previousAboveThresholdState(0),
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
                                                                                   previousAboveThresholdState(0),
                                                                                   pin(pin)
{
    attach(pin);
    interval(interval_millis);
    setThreshold(threshold);
}

void AnalogThrottle::attach(int pin)
{
    this->pin = pin;
    previousAboveThresholdState = 0;
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

int AnalogThrottle::intensity()
{
    return maxPeak;
    // if (fell()) {
    //     return maxPeak;
    // }
    // return 0;
}

bool AnalogThrottle::changed()
{
    return fell() || rose();
}

bool AnalogThrottle::read()
{
    return previousAboveThresholdState;
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
        int readValue = analogRead(pin);
        bool isAboveThreshold = readValue >= threshold;

        if (previousAboveThresholdState)
            maxPeak = 0;

        if (isAboveThreshold == previousAboveThresholdState)
            return false;
            
        // Is Searching Peak
        if (isAboveThreshold && (readValue > maxPeak))
        {
            // Serial.print("New Max:");
            // Serial.println(readValue);
            maxPeak = readValue;
            return false;
        }

        if (readValue < (maxPeak - 10) && (maxPeak > threshold))
        {
            // Serial.print("Fallen:");
            // Serial.println(readValue);
            isFallen = true;
            previousAboveThresholdState = true;
            previousDuration = currentTime - lastChangedTime;
            lastChangedTime = currentTime;
            return true;
        }

        if (!isAboveThreshold) {
            // Serial.print("Rised:");
            // Serial.println(readValue);
            isRisen = true;
            maxPeak = 0;
            previousAboveThresholdState = false;
            previousDuration = currentTime - lastChangedTime;
            lastChangedTime = currentTime;
            return true;
        }
    }
    return false;
}
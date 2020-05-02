#ifndef DISPLAY_H
#define DISPLAY_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif

#include <TM1637Display.h>
#include "pinout.h"

class Display
{
public:
    Display();
    void update();
    void setDigits(byte d0, byte d1, byte d2, byte d3);
    void clear();
    void write(const char *text);
    void write(char *text);
    void writeValue(int value);
    void writeTitleValue(const char title, uint8_t value);
    void writeTitle2Value(const char title, const char title2, uint8_t value);

protected:
    bool needsUpdate = false;
    byte digits[4];
    TM1637Display *display = new TM1637Display(PIN_SCL, PIN_SDA);
    byte digitFor(char character);
};

#endif

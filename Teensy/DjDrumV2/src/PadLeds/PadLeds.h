#ifndef PAD_LEDS_H
#define PAD_LEDS_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif

#include <Adafruit_NeoPixel.h>
#include "pinout.h"

#define NUM_PIXELS 108
#define COLOR uint32_t

class PadLeds
{
public:
    PadLeds();
    void turnOnPad(int pad, int noteSymbol);
    void turnOffPad(int pad, int noteSymbol);

protected:
    Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, PIN_RGB1, NEO_GRB + NEO_KHZ800);
    COLOR onColors[12] = {
        pixels.Color(0, 255, 255),
        pixels.Color(255, 0, 255),
        pixels.Color(255, 255, 0),
        pixels.Color(0, 255, 255),
        pixels.Color(255, 0, 255),
        pixels.Color(255, 255, 0),
        pixels.Color(0, 255, 255),
        pixels.Color(255, 0, 255),
        pixels.Color(255, 255, 0),
        pixels.Color(0, 255, 255),
        pixels.Color(255, 0, 255),
        pixels.Color(255, 255, 0),
    };

    COLOR offColors[12] = {
        pixels.Color(0, 50, 50),
        pixels.Color(50, 0, 50),
        pixels.Color(50, 50, 0),
        pixels.Color(0, 50, 50),
        pixels.Color(50, 0, 50),
        pixels.Color(50, 50, 0),
        pixels.Color(0, 50, 50),
        pixels.Color(50, 0, 50),
        pixels.Color(50, 50, 0),
        pixels.Color(0, 50, 50),
        pixels.Color(50, 0, 50),
        pixels.Color(50, 50, 0),
    };
};

#endif
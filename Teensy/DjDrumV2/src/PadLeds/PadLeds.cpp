#include "PadLeds.h"

PadLeds::PadLeds() 
{
    pixels.begin();
    delay(2000);
    pixels.setPixelColor(1, pixels.Color(255, 50, 10));
    pixels.show();
    //setAllPixelsColor(pixels.Color(30, 30, 30));
}

void PadLeds::turnOnPad(int pad, int noteSymbol) 
{
    for (int i = 0; i < 6; i++) {
      int pixelIndex = /*NUM_PIXELS - (pad * 6)  -*/ i;
      pixels.setPixelColor(pixelIndex, pixels.Color(255, 50, 10));
    }
    pixels.show();
}

void PadLeds::turnOffPad(int pad, int noteSymbol) 
{
    for (int i = 0; i < 6; i++) {
      int pixelIndex = /*NUM_PIXELS - (pad * 6)  - */i;
      pixels.setPixelColor(pixelIndex, offColors[noteSymbol]);
    }
    pixels.show();
}
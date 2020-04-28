#ifndef CORE_H
#define CORE_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "Midi/Midi.h"
#include "Display/Display.h"

class Core {
public:
    Core();
    void padPressed(int pad, uint8_t velocity);
    void update();
    void updateDisplay();
    
protected:
    Midi midi;

    uint8_t midiChannel = 1;
    int noteDuration = 1000;
};

#endif

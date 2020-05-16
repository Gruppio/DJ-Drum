#ifndef MIDI_H
#define MIDI_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif

class Midi {
public:
    Midi();
    void sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel);
    void sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel);
    void update();
};

#endif
#ifndef MIDI_H
#define MIDI_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif

class Midi {
public:
    Midi();
    virtual void sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel);
    virtual void sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel);
    virtual void update();
};

#endif
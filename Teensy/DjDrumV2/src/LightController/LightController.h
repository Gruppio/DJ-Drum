#ifndef LIGHT_CONTROLLER_H
#define LIGHT_CONTROLLER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif

#include "NoteEncoder/NoteEncoder.h"
#include "NoteModulator/NoteModulator.h"

class LightController
{
protected:
    NoteEncoder *noteEncoder;
    NoteModulator *noteModulator;
    bool debug = false;

public:
    LightController(NoteEncoder *noteEncoder, NoteModulator *noteModulator);
    void sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel);
    void sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel);
};

#endif
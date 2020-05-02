#ifndef MIDI_NOTE_RECORD_H
#define MIDI_NOTE_RECORD_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif

struct MidiNoteRecord
{
    MidiNoteRecord(bool isOn, uint8_t note, uint8_t velocity, uint8_t channel, unsigned long timestamp);
    bool isOn;
    uint8_t note;
    uint8_t velocity;
    uint8_t channel;
    unsigned long timestamp;
};

#endif
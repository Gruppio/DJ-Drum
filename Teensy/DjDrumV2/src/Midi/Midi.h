#ifndef MIDI_H
#define MIDI_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif

#include <list>

#define DEBUG false

struct MidiNoteOffRecord
{
    MidiNoteOffRecord(uint8_t note, uint8_t velocity, uint8_t channel, int duration);
    uint8_t note;
    uint8_t velocity;
    uint8_t channel;
    unsigned long scheduledTime;
};

class Midi
{
public:
    Midi();
    void sendNote(uint8_t note, uint8_t velocity, uint8_t channel, int duration);
    void update();
    int numberOfNotesCurrenltyPlaying();

protected:
    int _numberOfNotesCurrenltyPlaying = 0;
    std::list<MidiNoteOffRecord *> scheduledMidiNoteOff;

    void sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel);
    void sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel);
};

#endif

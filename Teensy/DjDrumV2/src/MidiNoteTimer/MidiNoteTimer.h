#ifndef MIDI_NOTE_TIMER_H
#define MIDI_NOTE_TIMER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif

#include <list>
#include "Models/MidiNoteRecord.h"
#include "Midi/Midi.h"

#define DEBUG false

class MidiNoteTimer
{
public:
    MidiNoteTimer(Midi *midi);
    void sendNote(uint8_t note, uint8_t velocity, uint8_t channel, int duration);
    void update();
    int numberOfNotesCurrenltyPlaying();

protected:
    Midi *midi;
    int _numberOfNotesCurrenltyPlaying = 0;
    std::list<MidiNoteRecord *> scheduledMidiNoteOff;

    void sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel);
    void sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel);
};

#endif

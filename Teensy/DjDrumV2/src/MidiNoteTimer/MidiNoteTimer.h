#ifndef MIDI_H
#define MIDI_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif

#include <list>
#include "Models/MidiNoteRecord.h"
#include "MidiRecorder/MidiRecorder.h"

#define DEBUG false

class MidiNoteTimer
{
public:
    MidiNoteTimer(MidiRecorder *midiRecorder);
    void sendNote(uint8_t note, uint8_t velocity, uint8_t channel, int duration);
    void update();
    int numberOfNotesCurrenltyPlaying();

protected:
    MidiRecorder *midiRecorder;
    int _numberOfNotesCurrenltyPlaying = 0;
    std::list<MidiNoteRecord *> scheduledMidiNoteOff;

    void sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel);
    void sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel);
};

#endif

#ifndef RECORDER_MIDI_DECORATOR_H
#define RECORDER_MIDI_DECORATOR_H

#include "Midi.h"
#include "MidiDecorator.h"
#include "MidiRecorder/MidiRecorder.h"

class RecorderMidiDecorator : public MidiDecorator
{
protected:
    MidiRecorder *midiRecorder;

public:
    RecorderMidiDecorator(MidiRecorder *midiRecorder, Midi *midi);
    virtual void sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel);
    virtual void sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel);
    virtual void update();
};

#endif
#ifndef MIDI_DECORATOR_H
#define MIDI_DECORATOR_H

#include "Midi.h"

class MidiDecorator : public Midi
{
protected:
    Midi *midi;

public:
    MidiDecorator(Midi *midi) : midi(midi) {}
    virtual ~MidiDecorator();
    
    virtual void sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel);
    virtual void sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel);
    virtual void update();
};

#endif
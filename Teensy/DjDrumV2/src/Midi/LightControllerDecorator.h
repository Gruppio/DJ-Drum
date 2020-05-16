#ifndef SERIAL_MIDI_DECORATOR_H
#define SERIAL_MIDI_DECORATOR_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif

#include "Midi.h"
#include "MidiDecorator.h"
#include "LightController/LightController.h"

class LightControllerDecorator : public MidiDecorator
{
protected:
    LightController *lightController;

public:
    LightControllerDecorator(LightController *lightController, Midi *midi);
    virtual void sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel);
    virtual void sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel);
};

#endif
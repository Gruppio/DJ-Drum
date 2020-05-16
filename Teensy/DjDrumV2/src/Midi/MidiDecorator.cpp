
#include "MidiDecorator.h"

void MidiDecorator::sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel)
{
    midi->sendNoteOn(note, velocity, channel);
}

void MidiDecorator::sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel)
{
    midi->sendNoteOff(note, velocity, channel);
}

void MidiDecorator::update()
{
    midi->update();
}
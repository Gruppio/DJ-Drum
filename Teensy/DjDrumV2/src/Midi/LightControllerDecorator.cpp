
#include "LightControllerDecorator.h"

LightControllerDecorator::LightControllerDecorator(LightController *lightController,
                                                   Midi *midi) : MidiDecorator(midi)
{
    this->lightController = lightController;
}

void LightControllerDecorator::sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel)
{
    lightController->sendNoteOn(note, velocity, channel);
    midi->sendNoteOn(note, velocity, channel);
}

void LightControllerDecorator::sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel)
{
    lightController->sendNoteOff(note, velocity, channel);
    midi->sendNoteOff(note, velocity, channel);
}

#include "Midi.h"

Midi::Midi() {}

void Midi::sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel) {
    usbMIDI.sendNoteOn(note, velocity, channel);
}

void Midi::sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel) {
    usbMIDI.sendNoteOff(note, velocity, channel);
}

void Midi::update() {
    while (usbMIDI.read())
    {
    }
}

#include "Core/Core.h"

Core::Core() {
}

void Core::padPressed(int pad, uint8_t velocity) {
    midi->sendNote(60, velocity, midiChannel, noteDuration);
}

void Core::update() {
    midi->update();
    display->writeTitleValue('c', 27);
}

void Core::updateDisplay() {
    digitalWrite(LED_BUILTIN, midi->numberOfNotesCurrenltyPlaying() > 0);
    display->update();
}


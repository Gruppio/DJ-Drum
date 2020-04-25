#include "Core/Core.h"

Core::Core() {
}

void led(bool value) {
    digitalWrite(LED_BUILTIN, value);
}

void Core::padPressed(int pad, int velocity) {
    numberOfPadsCurrentlyPressed++;
    usbMIDI.sendNoteOn(60, (uint8_t) velocity, 1);
}

void Core::padReleased(int pad) {
    numberOfPadsCurrentlyPressed--;
    usbMIDI.sendNoteOff(60, 0, 1);
}

void Core::updateDisplay() {
    led(numberOfPadsCurrentlyPressed > 0);
}


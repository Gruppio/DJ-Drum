#include "Core/Core.h"

Core::Core() {
}

void led(bool value) {
    digitalWrite(LED_BUILTIN, value);
}

void Core::padPressed(int pad) {
    numberOfPadsCurrentlyPressed++;
}

void Core::padReleased(int pad) {
    numberOfPadsCurrentlyPressed--;
}

void Core::updateDisplay() {
    led(numberOfPadsCurrentlyPressed > 0);
}

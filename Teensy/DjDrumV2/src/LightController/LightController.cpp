
#include "LightController/LightController.h"

LightController::LightController(NoteEncoder *noteEncoder,
                                 NoteModulator *noteModulator)
{
    this->noteEncoder = noteEncoder;
    this->noteModulator = noteModulator;
}

void LightController::sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel)
{
    int pad = noteModulator->padForNote(note);
    if (pad > 0)
    {
        uint8_t noteEncoded = noteEncoder->encode(1 + (note % 12), pad);
        Serial1.write(noteEncoded);
    }
}

void LightController::sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel)
{
    int pad = noteModulator->padForNote(note);
    if (pad > 0)
    {
        uint8_t noteEncoded = noteEncoder->encode(0, pad);
        Serial1.write(noteEncoded);
    }
}
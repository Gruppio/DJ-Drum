#ifndef CORE_H
#define CORE_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "Midi/Midi.h"
#include "Display/Display.h"
#include "NoteModulator/NoteModulator.h"
#include "Models/NoteSymbol.h"
#include "PadLeds/PadLeds.h"

class Core {
public:
    Core();
    void padPressed(int pad, uint8_t velocity);
    void update();
    void updateDisplay();

    void incrChannel();
    void decrChannel();
    void incrOctave();
    void decrOctave();
    void incrScale();
    void decrScale();
    void incrIntonation();
    void decrIntonation();

public:
    Display *display = new Display();
    NoteModulator *noteModulator = new NoteModulator();

protected:
    Midi *midi = new Midi();
    //PadLeds *padLeds = new PadLeds();
    int noteDuration = 1000;
    void displayWriteScale();
    void displayWriteNote(byte note);
    NoteSymbol noteSymbolForNote(byte note);
};

#endif

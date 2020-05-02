#ifndef CORE_H
#define CORE_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "Midi/Midi.h"
#include "Display/Display.h"
#include "NoteModulator/NoteModulator.h"
#include "Models/NoteSymbol.h"
#include "MidiRecorder/MidiRecorder.h"
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
    void didPressRecording();
    void didReleaseRecording();
    void setNoteDuration(int duration);

public:
    
    Display *display = new Display();
    NoteModulator *noteModulator = new NoteModulator();
    MidiRecorder *midiRecorder = new MidiRecorder();

protected:
    int noteDuration = 400;
    Midi *midi = new Midi(midiRecorder);
    //PadLeds *padLeds = new PadLeds();
    void displayWriteScale();
    void displayWriteNote(byte note);
    NoteSymbol noteSymbolForNote(byte note);
};

#endif

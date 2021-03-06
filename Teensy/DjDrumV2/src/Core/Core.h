#ifndef CORE_H
#define CORE_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "MidiNoteTimer/MidiNoteTimer.h"
#include "Display/Display.h"
#include "NoteModulator/NoteModulator.h"
#include "Models/NoteSymbol.h"
#include "MidiRecorder/MidiRecorder.h"
#include "NoteEncoder/NoteEncoder.h"
#include "Midi/Midi.h"
#include "LightController/LightController.h"
#include "Midi/RecorderMidiDecorator.h"
#include "Midi/LightControllerDecorator.h"

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
    void setNoteVelocity(uint8_t velocity);

public:
    
    Display *display = new Display();
    NoteModulator *noteModulator = new NoteModulator();
    MidiRecorder *midiRecorder = new MidiRecorder();

protected:
    int noteDuration = 400;
    uint8_t noteVelocity = 127;
    NoteEncoder *noteEncoder = new NoteEncoder();
    LightController *lightController = new LightController(noteEncoder, noteModulator);
    Midi *midi = new LightControllerDecorator(lightController, new RecorderMidiDecorator(midiRecorder, new Midi()));
    MidiNoteTimer *midiNoteTimer = new MidiNoteTimer(midi);
    
    void displayWriteScale();
    void displayWriteNote(byte note);
    NoteSymbol noteSymbolForNote(byte note);
    void updateAllLightColors();
};

#endif

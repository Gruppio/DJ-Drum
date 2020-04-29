#ifndef NOTE_MODULATOR_H
#define NOTE_MODULATOR_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif

#include "NormalScale.h"
#include "MajorScale.h"
#include "BlackAndWhiteScale.h"

#define NUMBER_OF_MIDI_CHANNELS 16

#define DEFAULT_OCTAVE 3
#define NUMBER_OF_OCTAVES 8

#define DEFAULT_SCALE 0
#define NUMBER_OF_SCALES 3
enum Scale { Normal = 0, Major, BlackAndWhite };

#define NUMBER_OF_INTONATIONS 11

//enum Note {C = 0, Cd, D, Dd, E, F, Fd,  G,  Gd,  A, Ad, B};

class NoteModulator
{
public:
    NoteModulator();
    uint8_t noteForPad(int pad);
    int* padOffsets();

    uint8_t getChannel();
    uint8_t getOctave();
    uint8_t getIntonation();
    Scale getScale();

    void incrChannel();
    void decrChannel();
    void incrScale();
    void decrScale();
    void incrIntonation();
    void decrIntonation();

protected:
    uint8_t channel = 0;
    uint8_t channelOctave[NUMBER_OF_MIDI_CHANNELS];
    uint8_t channelScale[NUMBER_OF_MIDI_CHANNELS];
    uint8_t channelIntonation[NUMBER_OF_MIDI_CHANNELS];
};

#endif

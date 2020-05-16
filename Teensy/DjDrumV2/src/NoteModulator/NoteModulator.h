#ifndef NOTE_MODULATOR_H
#define NOTE_MODULATOR_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif

#define NUMBER_OF_MIDI_CHANNELS 16

#define DEFAULT_OCTAVE 4
#define NUMBER_OF_OCTAVES 8

#define DEFAULT_SCALE 1
#define NUMBER_OF_SCALES 3

#define NUMBER_OF_PADS 18
enum Scale
{
    Normal = 0,
    Major,
    BlackAndWhite
};

#define NUMBER_OF_INTONATIONS 11

//enum Note {C = 0, Cd, D, Dd, E, F, Fd,  G,  Gd,  A, Ad, B};

class NoteModulator
{
public:
    NoteModulator();
    uint8_t noteForPad(int pad);
    int padForNote(uint8_t note);
    int *padOffsets();

    uint8_t getChannel();
    uint8_t getOctave();
    uint8_t getIntonation();
    Scale getScale();

    void incrChannel();
    void decrChannel();
    void incrOctave();
    void decrOctave();
    void incrScale();
    void decrScale();
    void incrIntonation();
    void decrIntonation();

protected:
    uint8_t channel = 0;
    uint8_t channelOctave[NUMBER_OF_MIDI_CHANNELS];
    uint8_t channelScale[NUMBER_OF_MIDI_CHANNELS];
    uint8_t channelIntonation[NUMBER_OF_MIDI_CHANNELS] = {0};

    int blackAndWhiteScale[NUMBER_OF_PADS] = {1, 3, 6, 8, 10, 13,
                                              0, 2, 4, 5, 7, 9,
                                              11, 12, 14, 16, 17, 15};

    int majorScale[NUMBER_OF_PADS] = {-10, -8, -7, -5, -3, -1,
                                      0, 2, 4, 5, 7, 9,
                                      11, 12, 14, 16, 17, 19};

    int normalScale[NUMBER_OF_PADS] = {-6, -5, -4, -3, -2, -1,
                                       0, 1, 2, 3, 4, 5,
                                       6, 7, 8, 9, 10, 11};
};

#endif

// Keyboard
// Black Keys:    | 2 | 4 |   | 7 | 9 | 11 |     | 14 | 16 |
// White Keys:  | 1 | 3 | 5 | 6 | 8 | 10 | 12 | 13 | 15 | 17 | 

// NORMAL
// Pad Number
// (Offset)

//    1      2      3      4      5      6
// ( -6 ) ( -5 ) ( -4 ) ( -3 ) ( -2 ) ( -1 )

//   7     8     9    10     11    12
// ( 0 ) ( 1 ) ( 2 ) ( 3 ) ( 4 ) ( 5 )

//   13    14    15    16    17     18
// ( 6 ) ( 7 ) ( 8 ) ( 9 ) ( 10 ) ( 11 )

// ------------

// MAJOR

// Pad Number
// (Offset)

//    1      2      3      4      5      6
// ( -10 ) ( -8 ) ( -7 ) ( -5 ) ( -3 ) ( -1 )

//   7     8     9    10     11    12
// ( 0 ) ( 2 ) ( 4 ) ( 5 ) ( 7 ) ( 9 )

//   13    14    15    16    17    18
// ( 11 )( 12 )( 14 )( 16 )( 17 )( 19 )

// ---------------

// Black and white

// Pad Number
// (Offset)

//   1     2     3     4     5     6
// ( 2 ) ( 4 ) ( 7 ) ( 9 ) ( 11 )( 14 )

//   7     8     9    10     11    12
// ( 1 ) ( 3 ) ( 5 ) ( 6 ) ( 8 ) ( 10 )

//   13    14    15    16    17    18
// ( 12 )( 13 )( 15 )( 17 )( 18 )( 16 )

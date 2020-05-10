#ifndef NOTE_ENCODER_H
#define NOTE_ENCODER_H

#include <Arduino.h>

#define NUMBER_OF_PADS 18
#define NUMBER_OF_NOTES 13 // OFF + NOTES

class NoteEncoder {
public:
    NoteEncoder();
    uint8_t encode(uint8_t note, uint8_t pad);
    uint8_t decodeNote(uint8_t value);
    uint8_t decodePad(uint8_t value);
};

#endif

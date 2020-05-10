#include "NoteEncoder.h"

NoteEncoder::NoteEncoder()
{
}

uint8_t NoteEncoder::encode(uint8_t note, uint8_t pad)
{
    uint8_t result = note;
    result += pad * NUMBER_OF_NOTES;
    return result;
}

uint8_t NoteEncoder::decodeNote(uint8_t value)
{
    uint8_t padOffset = decodePad(value) * NUMBER_OF_NOTES;
    return value - padOffset;
}

uint8_t NoteEncoder::decodePad(uint8_t value)
{
    return value / NUMBER_OF_NOTES;
}
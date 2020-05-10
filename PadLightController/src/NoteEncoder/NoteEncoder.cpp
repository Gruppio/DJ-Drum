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

void NoteEncoder::test()
{
  bool printOnlyErrors = true;
  int initialNote = 0;
  int initialPad = 0;
  for (initialNote = 0; initialNote < NUMBER_OF_NOTES; initialNote++)
  {
    for (initialPad = 0; initialPad < NUMBER_OF_PADS; initialPad++)
    {
      uint8_t enc = encode(initialNote, initialPad);
      uint8_t pad = decodePad(enc);
      uint8_t note = decodeNote(enc);
      if (printOnlyErrors)
      {
        if (note != initialNote || pad != initialPad)
        {
          Serial.print("Error: Note: ");
          Serial.print(initialNote);
          Serial.print(", Pad: ");
          Serial.print(initialPad);
          Serial.print(", Enc: ");
          Serial.println(enc);
        }
      }
      else
      {
        Serial.print(initialNote);
        Serial.print(" ");
        Serial.print(note);
        Serial.print(" - ");
        Serial.print(initialPad);
        Serial.print(" ");
        Serial.print(pad);
        Serial.print(" - ");
        Serial.println(enc);
      }
    }
  }
  Serial.println("Test Done");
}
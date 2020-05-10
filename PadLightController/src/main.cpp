#include <Arduino.h>
#include "FastLED.h"

#define PIN_LED 2
#define NUM_LEDS 108
CRGB leds[NUM_LEDS];

#define NUMBER_OF_PADS 18
#define NUMBER_OF_NOTES 13 // OFF + NOTES

#define LOW_LUMINOSITY 50
#define HIGH_LUMINOSITY 255

class NoteEncoder
{
public:
  NoteEncoder();
  uint8_t encode(uint8_t note, uint8_t pad);
  uint8_t decodeNote(uint8_t value);
  uint8_t decodePad(uint8_t value);
};

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

NoteEncoder noteEncoder;

void testEncoder()
{
  bool printOnlyErrors = true;
  int initialNote = 0;
  int initialPad = 0;
  for (initialNote = 0; initialNote < NUMBER_OF_NOTES; initialNote++)
  {
    for (initialPad = 0; initialPad < NUMBER_OF_PADS; initialPad++)
    {
      uint8_t enc = noteEncoder.encode(initialNote, initialPad);
      uint8_t pad = noteEncoder.decodePad(enc);
      uint8_t note = noteEncoder.decodeNote(enc);
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

void getLedIndexes(int pad, int &tl, int &ml, int &bl, int &tr, int &mr, int &br)
{
  bool backwardIndexing = (pad < 6 || pad > 11);
  int baseIndex = 0;

  if (backwardIndexing)
  {
    baseIndex = NUM_LEDS - (pad * 6) - 1;
    tl = baseIndex - 0;
    ml = baseIndex - 1;
    bl = baseIndex - 2;
    tr = baseIndex - 3;
    mr = baseIndex - 4;
    br = baseIndex - 5;
  }
  else
  {
    baseIndex = (12 * 6) + (pad - 6) * 6 + 1;
    tl = baseIndex + 0;
    ml = baseIndex + 1;
    bl = baseIndex + 2;
    tr = baseIndex + 3;
    mr = baseIndex + 4;
    br = baseIndex + 5;
  }
}

void testLedIndexes()
{
  int tl, ml, bl, tr, mr, br = 0;
  for (int pad = 0; pad < NUMBER_OF_PADS; pad++)
  {
    getLedIndexes(pad, tl, ml, bl, tr, mr, br);
    Serial.print("Pad : ");
    Serial.print(pad);
    Serial.print(" - ");
    Serial.print(tl);
    Serial.print(" ");
    Serial.print(ml);
    Serial.print(" ");
    Serial.print(bl);
    Serial.print(" ");
    Serial.print(tr);
    Serial.print(" ");
    Serial.print(mr);
    Serial.print(" ");
    Serial.print(br);
    Serial.println(" ");
  }
}

void updateWithSerialValue(uint8_t value)
{
  uint8_t pad = noteEncoder.decodePad(value);
  uint8_t note = noteEncoder.decodeNote(value);

  if (note == 0)
  {
  }
}

void setup()
{
  Serial.begin(9600);
  delay(2000);
  FastLED.addLeds<NEOPIXEL, PIN_LED>(leds, NUM_LEDS);
  testLedIndexes();
}

void loop()
{
  if (Serial.available() > 0)
  {
    int value = Serial.read();
    updateWithSerialValue((uint8_t)value);
  }

  leds[0] = CRGB::White;
  FastLED.show();
  delay(30);
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(30);
}

#include <Arduino.h>
#include "NoteEncoder/NoteEncoder.h"
#include "FastLED.h"

#define PIN_LED 2
#define NUM_LEDS 108
CRGB leds[NUM_LEDS];

#define LOW_LUMINOSITY 50
#define HIGH_LUMINOSITY 255

NoteEncoder noteEncoder;

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
    br = baseIndex - 3;
    mr = baseIndex - 4;
    tr = baseIndex - 5;
  }
  else
  {
    baseIndex = pad * 6;
    tl = baseIndex + 0;
    ml = baseIndex + 1;
    bl = baseIndex + 2;
    br = baseIndex + 3;
    mr = baseIndex + 4;
    tr = baseIndex + 5;
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
  //testLedIndexes();
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

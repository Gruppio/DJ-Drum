#include <Arduino.h>
#include "NoteEncoder/NoteEncoder.h"
#include "FastLED.h"

#define PIN_LED 2
#define NUM_LEDS 108
CRGB leds[NUM_LEDS];

#define LOW_LUMINOSITY 10
#define HIGH_LUMINOSITY 255

#define HUE_DO 140
#define HUE_RE 42
#define HUE_MI 85
#define HUE_FA 0
#define HUE_SOL 170
#define HUE_LA 235
#define HUE_SI 128

#define COLOR_VARIANCE 8

uint8_t noteHues[NUMBER_OF_NOTES][2] = {
  {0, 0},
  {HUE_DO, HUE_DO},
  {HUE_DO, HUE_RE},
  {HUE_RE, HUE_RE},
  {HUE_RE, HUE_MI},
  {HUE_MI, HUE_MI},
  {HUE_FA, HUE_FA},
  {HUE_FA, HUE_SOL},
  {HUE_SOL, HUE_SOL},
  {HUE_SOL, HUE_LA},
  {HUE_LA, HUE_LA},
  {HUE_LA, HUE_SI},
  {HUE_SI, HUE_SI}
};

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

void setNoteToPad(uint8_t note, uint8_t pad) {
  int tl, ml, bl, tr, mr, br = 0;
  getLedIndexes(pad, tl, ml, bl, tr, mr, br);
  if (note == 0) {
    uint8_t fade = 255 - LOW_LUMINOSITY;
    leds[tl].fadeLightBy(fade);
    leds[ml].fadeLightBy(fade);
    leds[bl].fadeLightBy(fade);
    leds[tr].fadeLightBy(fade);
    leds[mr].fadeLightBy(fade);
    leds[br].fadeLightBy(fade);
  } else {
    uint8_t hues[2] = { noteHues[note][0], noteHues[note][1] };
    leds[tl].setHue(hues[0]);
    leds[ml].setHue(hues[0] + COLOR_VARIANCE);
    leds[bl].setHue(hues[0] + COLOR_VARIANCE * 2);
    leds[tr].setHue(hues[1]);
    leds[mr].setHue(hues[1] + COLOR_VARIANCE);
    leds[br].setHue(hues[1] + COLOR_VARIANCE * 2);
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
  setNoteToPad(note, pad);
}

void setup()
{
  pinMode(0, INPUT);
  FastLED.addLeds<NEOPIXEL, PIN_LED>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );;
  Serial.begin(9600);
  delay(2000);
  //testLedIndexes();
}

void loop()
{
  if (Serial.available() > 0)
  {
    uint8_t value = Serial.read();
    updateWithSerialValue(value);
    FastLED.show();
  }

  // for(uint8_t note = 0; note < NUMBER_OF_NOTES; note++) {
  //   setNoteToPad(note, 16);
  //   FastLED.show();
  //   delay(1000);
  // }
}

//   leds[0] = CRGB::White;
//   FastLED.show();
//   delay(30);
//   leds[0] = CRGB::Black;
//   FastLED.show();
//   delay(30);
// }

#include <Throttle.h>
#include <Arduino.h>
#include <MIDIUSB.h>
#include <TM1637Display.h>
#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN   4
#define NUM_PIXELS  108
#define COLOR uint32_t

// In order to flash the arduino Due(milanove) you have to download the SAMD ( search for "DUE" ) board in the board manager
// keep press the erase button, then press the reset button and then you can program it
// You need to install also MIDIUSB, Throttle (Mine), TM1637Display (https://github.com/avishorp/TM1637) libs

#define velocity 64

#define START_PIN 36
#define NUMBER_OF_PADS 18
#define DEBOUNCE_TIME 50

// Modalities from 0 to 9 uses the 0 - 9 channels without intonation
// Modalities from 11 to 20 uses the 0 - 9 channels with intonation
// Modality 10 use 3 channels for each drum row without intonation
#define NUMBER_OF_MODALITIES 21
#define DEFAULT_OCTAVE 4

#define DEBUG 0
#define SERIAL_ENABLED 0

#define DIO 2 // Pink wire
#define CLK 3 // Gray wire

// Keyboard
// Black Keys:    | 2 | 4 |   | 7 | 9 | 11 |     | 14 | 16 |
// White Keys:  | 1 | 3 | 5 | 6 | 8 | 10 | 12 | 13 | 15 | 17 | 18 |

// Drum with No Intonation 
// Pad Number
// (Offset)
//   1     2     3     4     5     6
// ( 2 ) ( 4 ) ( 7 ) ( 9 ) ( 11 )( 14 )

//   7     8     9    10     11    12
// ( 1 ) ( 3 ) ( 5 ) ( 6 ) ( 8 ) ( 10 )

//   13    14    15    16    17    18
// ( 12 )( 13 )( 15 )( 17 )( 18 )( 16 )


// Drum with Intonation
// Pad Number
// (Offset)
//     1      2      3      4      5      6
// ( -9 ) ( -7 ) ( -6 ) ( -4 ) ( -2 ) ( -1 )

//   7     8     9    10     11    12
// ( 0 ) ( 2 ) ( 4 ) ( 5 ) ( 7 ) ( 9 )

//   13    14    15    16    17    18
// ( 11 )( 12 )( 14 )( 16 )( 17 )( 19 )


// char startCharacters[] = {'Q', 'W', 'E', 'R', 'T', 'Y', 'A', 'S', 'D', 'F', 'G', 'H', 'Z', 'X', 'C', 'V', 'B', 'N'};
// char stopCharacters[] = {'q', 'w', 'e', 'r', 't', 'y', 'a', 's', 'd', 'f', 'g', 'h', 'z', 'x', 'c', 'v', 'b', 'n'};
// char keyboardCharacters[] = { 'w', 'e', 't', 'y', 'u', 'o', 
//                               'a', 's', 'd', 'f', 'g', 'h', 
//                               'j', 'k', 'l', ';', '\'', 'p'};

TM1637Display display(CLK, DIO);

int padOffsetsWithNoIntonation[] = {1, 3, 6, 8, 10, 13,
                                    0, 2, 4, 5, 7, 9,
                                    11, 12, 14, 16, 17, 15};

int padOffsetsWithIntonation[] = {-9, -7, -6, -4, -2, -1,
                                  0, 2, 4, 5, 7, 9,
                                  11, 12, 14, 16, 17, 19};

uint32_t activatedColors[NUMBER_OF_PADS];
uint32_t deactivatedColors[NUMBER_OF_PADS];

Throttle pads[NUMBER_OF_PADS]; // 22 27
Throttle increaseModalityButton(23, INPUT_PULLUP, 100);
Throttle decreaseModalityButton(25, INPUT_PULLUP, 100);
Throttle increaseOctaveButton(22, INPUT_PULLUP, 100);
Throttle decreaseOctaveButton(27, INPUT_PULLUP, 100);
Throttle increaseIntonationButton(26, INPUT_PULLUP, 100);
Throttle decreaseIntonationButton(24, INPUT_PULLUP, 100);

//         Do     Do# Re Re# Mi Fa Fa# Sol Sol# LA  LA# SI
enum Note {C = 0, Cd, D, Dd, E, F, Fd,  G,  Gd,  A, Ad, B};

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

int modality = 11;
int octaveForModality[NUMBER_OF_MODALITIES];
int intonationForModality[NUMBER_OF_MODALITIES];

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t getColorWheel(byte index, byte intensity) {
  float floatIndex = (float) index;
  floatIndex /= 85;
  
   if(index < 85) {
       return pixels.Color(floatIndex * intensity, (1 - floatIndex) * intensity, 0);
   } else if(index < 170) {
       floatIndex -= 1;
       return pixels.Color((1 - floatIndex) * intensity, 0, floatIndex * intensity);
   } else {
       floatIndex -= 2;
       return pixels.Color(0, floatIndex * intensity, (1 - floatIndex) * intensity);
   }
}

void setAllPixelsColor(COLOR color) {
  for (int i = 0; i < NUM_PIXELS; i++) {
    pixels.setPixelColor(i, color);
  }
  pixels.show();
}

void setPadColor(int pad, COLOR color) {
  /*
  if (pad > 5 && pad < 12) {
    for (int i = 0; i < 6; i++) {
      int pixelIndex = (NUM_PIXELS / 3) + ((pad - 6) * 6) - i;
      pixels.setPixelColor(pixelIndex, color);
    }
  } else {
    for (int i = 0; i < 6; i++) {
      int pixelIndex = NUM_PIXELS - pad * 6  - i;
      pixels.setPixelColor(pixelIndex, color);
    }
  }*/
  for (int i = 0; i < 6; i++) {
      int pixelIndex = NUM_PIXELS - (pad * 6)  - i;
      pixels.setPixelColor(pixelIndex, color);
    }
    pixels.show();
}

void setPadColorOn(int pad) {
  setPadColor(pad, activatedColors[pad]);
}

void setPadColorOff(int pad) {
  setPadColor(pad, deactivatedColors[pad]);
}

void updateColors() {
  byte modalityOffset = (modality % 5) * 50;
  for (int i = 0; i < NUMBER_OF_PADS; i++) {
    byte c = modalityOffset + (i * 4);
    activatedColors[i] = getColorWheel(c, 255);
    deactivatedColors[i] = getColorWheel(c, 30);
    setPadColor(i, deactivatedColors[i]);
  }

  pixels.show();
}

void increaseModality() {
  modality = constrain(modality + 1, 0, NUMBER_OF_MODALITIES);
  updateDisplay();
  updateColors();
  print("Increase Modality");
  printState();
}

void decreaseModality() {
  modality = constrain(modality - 1, 0, NUMBER_OF_MODALITIES);
  updateDisplay();
  updateColors();
  print("Decrease Modality");
  printState();
}

void increaseOctave() {
  octaveForModality[modality] = constrain(octaveForModality[modality] + 1, 0, 7);
  updateDisplay();
  print("Increase Octave");
  printState();
}

void decreaseOctave() {
  octaveForModality[modality] = constrain(octaveForModality[modality] - 1, 0, 7);
  updateDisplay();
  print("Decrease Octave");
  printState();
}

void increaseIntonation() {
  intonationForModality[modality] = constrain(intonationForModality[modality] + 1, 0, 11);
  updateDisplay();
  print("Increase Intonation");
  printState();
}

void decreaseIntonation() {
  intonationForModality[modality] = constrain(intonationForModality[modality] - 1, 0, 11);
  updateDisplay();
  print("Decrease Intonation");
  printState();
}

bool shouldUseIntonation() {
  return modality > 10;
}

bool is3ChannelModality() {
  return modality == 10;
}

byte getChannel(int pad) {
  // Modality = 10
  if (is3ChannelModality()) {
    return (byte)(pad / 6);
  }

  if (shouldUseIntonation()) {
    // Modality from 11 - 20
    return (byte)(modality - 11);
  } else {
    // Modality from 0 - 9
    return (byte)(9 - modality);
  }

  return 0;
}

int getPadOffset(int pad) {
  return shouldUseIntonation() ? padOffsetsWithIntonation[pad] : padOffsetsWithNoIntonation[pad];
}

int getIntonation() {
  return shouldUseIntonation() ? intonationForModality[modality] : 0;
}

byte getNoteOnSerialByte(int pad) {
  return (byte)pad;
}

byte getNoteOffSerialByte(int pad) {
  return (byte)(pad + 100);
}

byte noteForPad(int pad) {
  int padOffset = getPadOffset(pad);
  int octave = octaveForModality[modality];
  int intonation = getIntonation();
  int note = ((octave + 1) * 12) + padOffset + intonation;
  int constrainedNote = constrain(note, 21, 108);
  return (byte)constrainedNote;
}

Note noteSymbolForNote(byte note) {
  return Note(note % 12);
}

// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).
void noteOn(int pad) {
  byte note = noteForPad(pad);
  byte channel = getChannel(pad);
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, note, velocity};
  MidiUSB.sendMIDI(noteOn);
  printNoteOn(note);
}

void noteOff(int pad) {
  byte note = noteForPad(pad);
  byte channel = getChannel(pad);
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, note, velocity};
  MidiUSB.sendMIDI(noteOff);
  printNoteOff(note);
}

//
//      A
//     ---
//  F |   | B
//     -G-
//  E |   | C
//     ---
//      D
byte digitFor(char character) {
  switch (character) {
    //                 XGFEDCBA
    case '0': return 0b00111111;    // 0
    case '1': return 0b00000110;    // 1
    case '2': return 0b01011011;    // 2
    case '3': return 0b01001111;    // 3
    case '4': return 0b01100110;    // 4
    case '5': return 0b01101101;    // 5
    case '6': return 0b01111101;    // 6
    case '7': return 0b00000111;    // 7
    case '8': return 0b01111111;    // 8
    case '9': return 0b01101111;    // 9
    case 'a': return 0b01110111;    // A
    case 'b': return 0b01111100;    // B
    case 'c': return 0b00111001;    // C
    case 'd': return 0b01011110;    // D
    case 'e': return 0b01111001;    // E
    case 'f': return 0b01110001;    // F
    case 'g': return 0b01111101;    // G
    case 'h': return 0b01110110;    // H
    case 'k': return 0b01110110;    // K
    case 'i': return 0b00000110;    // I
    case 'l': return 0b00111000;    // L
    case 'm': return 0b00110111;    // M
    case 'n': return 0b01010100;    // N
    case 'o': return 0b00111111;    // O
    case 'p': return 0b01110011;    // P
    case 'q': return 0b01011100;    // Q
    case 'r': return 0b01010000;    // R
    case 's': return 0b01101101;    // S
    case 't': return 0b01111000;    // T
    case 'u': return 0b00111110;    // U
    case 'v': return 0b00011100;    // V
    case 'w': return 0b00011100;    // W
    case 'x': return 0b01110110;    // X
    case 'y': return 0b01100110;    // Y
    case 'z': return 0b01011011;    // Z
    case '.': return 0b10000000;    // .
    case '=': return 0b01001001;    // =
  }
  return 0b00000000;
}

byte digitFor(char character, bool point) {
  byte value = digitFor(character);
  return point ? (value | 0x80) : value;
}

byte getModalityDigit() {
  if (is3ChannelModality())
    return digitFor('=', true);

  char channel = '0' + getChannel(0);
  return digitFor(channel, shouldUseIntonation());
}

byte getOctaveDigit() {
  char octave = '0' + (char)octaveForModality[modality];
  return digitFor(octave);
}

byte getIntonationDigits(bool first) {
  if (!shouldUseIntonation()) {
    return 0;
  }
  byte intonation = getIntonation();
  switch (intonation)
  {
  case 0:
    return first ? digitFor('d') : digitFor('o');

  case 1:
    return first ? digitFor('d') : digitFor('h');

  case 2:
    return first ? digitFor('r') : digitFor('e');

  case 3:
    return first ? digitFor('r') : digitFor('h');

  case 4:
    return first ? digitFor('m') : digitFor('i');
  
  case 5:
    return first ? digitFor('f') : digitFor('a');

  case 6:
    return first ? digitFor('f') : digitFor('h');

  case 7:
    return first ? digitFor('s') : digitFor('o');

  case 8:
    return first ? digitFor('s') : digitFor('h');

  case 9:
    return first ? digitFor('l') : digitFor('a');

  case 10:
    return first ? digitFor('l') : digitFor('h');

  case 11:
    return first ? digitFor('s') : digitFor('i');
  
  default:
    return digitFor('0');
  }
}

void updateDisplay() {
  byte digits[4];
  digits[0] = getModalityDigit();
  digits[1] = getOctaveDigit();
  digits[2] = getIntonationDigits(true);
  digits[3] = getIntonationDigits(false);
  if (shouldUseIntonation()) {
    digits[1] |= 0b10000000;
  }
  display.setSegments(digits, 4, 0);
}

void setup()
{
  // Is in Pin 13 that is already used
  // pinMode(LED_BUILTIN, OUTPUT);
  // digitalWrite(LED_BUILTIN, LOW);
  pinMode(PIXEL_PIN, OUTPUT);
  /*
  for (int i = 0; i < NUMBER_OF_PADS; i++)
  {
    pads[i].attach(i + START_PIN, INPUT_PULLUP);
    pads[i].interval(DEBOUNCE_TIME);
  }

  for (int i = 0; i < NUMBER_OF_MODALITIES; i++)
  {
    intonationForModality[i] = 0;
    octaveForModality[i] = DEFAULT_OCTAVE;
  }

  Serial.begin(9600);*/
  pixels.begin();
  delay(2000);
  setAllPixelsColor(pixels.Color(30, 30, 30));
}
void loop()
{
}
  /*delay(1000);
  updateColors();
  printState();
  display.setBrightness(0x0a);
  updateDisplay();
}

void loop()
{
  
  increaseModalityButton.update();
  decreaseModalityButton.update();
  increaseOctaveButton.update();
  decreaseOctaveButton.update();
  increaseIntonationButton.update();
  decreaseIntonationButton.update(); 

  if (increaseModalityButton.fell()) { increaseModality(); }
  if (decreaseModalityButton.fell()) { decreaseModality(); }
  if (increaseOctaveButton.fell()) { increaseOctave(); }
  if (decreaseOctaveButton.fell()) { decreaseOctave(); }
  if (increaseIntonationButton.fell()) { increaseIntonation(); }
  if (decreaseIntonationButton.fell()) { decreaseIntonation(); }

  for (int i = 0; i < NUMBER_OF_PADS; i++)
  {
    pads[i].update();

    if (pads[i].fell())
    {
      noteOn(i);
      //setPadColorOn(i);
      //pixels.show();
      if (SERIAL_ENABLED) {
        Serial.write(getNoteOnSerialByte(i));
      }
    }

    if (pads[i].rose())
    {
      noteOff(i);
      //setPadColorOff(i);
      //pixels.show();
      if (SERIAL_ENABLED) {
        Serial.write(getNoteOffSerialByte(i));
      }
    }
  }
  MidiUSB.flush();
}
*/
void print(String s) {
  if (DEBUG) {
    Serial.print(s);
  }
}

void println(String s) {
  if (DEBUG) {
    Serial.println(s);
  }
}

void printState() {
  if (DEBUG) {
    Serial.println("");
    Serial.println("Current State:");
    Serial.print("Modality: "); Serial.println(modality);
    Serial.print("Octave: "); Serial.println(octaveForModality[modality]);
    Serial.print("Should Use Intonation: "); Serial.println(shouldUseIntonation());
    Serial.print("Intonation: "); Serial.println(intonationForModality[modality]);
    Serial.println("");
  }
}

void printNoteOn(byte note) {
  if (DEBUG) {
    Serial.println("");
    Serial.print("Note On: "); Serial.println(note);
  }
}

void printNoteOff(byte note) {
  if (DEBUG) {
    Serial.println("");
    Serial.print("Note Off: "); Serial.println(note);
  }
}

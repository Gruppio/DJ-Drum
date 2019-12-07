#include <Throttle.h>
#include <Arduino.h>
#include <MIDIUSB.h>

// In order to flash the arduino Due(milanove) you have to download the SAMD ( search for "DUE" ) board in the board manager
// keep press the erase button, then press the reset button and then you can program it
// You need to install also MIDIUSB lib

#define velocity 64

#define START_PIN 36
#define NUMBER_OF_PADS 18
#define DEBOUNCE_TIME 50

// Modalities from 0 to 9 uses the 0 - 9 channels without intonation
// Modalities from 11 to 20 uses the 0 - 9 channels with intonation
// Modality 10 use 3 channels for each drum row without intonation
#define NUMBER_OF_MODALITIES 21
#define DEFAULT_OCTAVE 4

#define DEBUG 1

// Keyboard
// Black Keys:    | 2 | 4 |   | 7 | 9 | 11 |     | 14 | 16 |
// White Keys:  | 1 | 3 | 5 | 6 | 8 | 10 | 12 | 13 | 15 | 17 | 18 |

// Drum with No Intonation 
// Pad Number
// (Offser)
//   1     2     3     4     5     6
// ( 2 ) ( 4 ) ( 7 ) ( 9 ) ( 11 )( 14 )

//   7     8     9    10     11    12
// ( 1 ) ( 3 ) ( 5 ) ( 6 ) ( 8 ) ( 10 )

//   13    14    15    16    17    18
// ( 12 )( 13 )( 15 )( 17 )( 18 )( 16 )


// Drum with Intonation
// Pad Number
// (Offser)
//     1      2      3      4      5      6
// ( -10 ) ( -8 ) ( -7 ) ( -5 ) ( -3 ) ( -1 )

//   7     8     9    10     11    12
// ( 0 ) ( 3 ) ( 5 ) ( 6 ) ( 8 ) ( 10 )

//   13    14    15    16    17    18
// ( 12 )( 13 )( 15 )( 17 )( 18 )( 20 )


// char startCharacters[] = {'Q', 'W', 'E', 'R', 'T', 'Y', 'A', 'S', 'D', 'F', 'G', 'H', 'Z', 'X', 'C', 'V', 'B', 'N'};
// char stopCharacters[] = {'q', 'w', 'e', 'r', 't', 'y', 'a', 's', 'd', 'f', 'g', 'h', 'z', 'x', 'c', 'v', 'b', 'n'};
// char keyboardCharacters[] = { 'w', 'e', 't', 'y', 'u', 'o', 
//                               'a', 's', 'd', 'f', 'g', 'h', 
//                               'j', 'k', 'l', ';', '\'', 'p'};

int padOffsetsWithNoIntonation[] = {1, 3, 6, 8, 10, 13,
                                    0, 2, 4, 5, 7, 9,
                                    11, 12, 14, 16, 17, 15};

int padOffsetsWithIntonation[] = {-10, -8, -7, -5, -3, -1,
                                  0, 3, 5, 6, 8, 10,
                                  12, 13, 15, 17, 18, 20};

Throttle pads[NUMBER_OF_PADS];
Throttle increaseModalityButton(13, INPUT_PULLUP, 100);
Throttle decreaseModalityButton(12, INPUT_PULLUP, 100);
Throttle increaseOctaveButton(11, INPUT_PULLUP, 100);
Throttle decreaseOctaveButton(10, INPUT_PULLUP, 100);
Throttle increaseIntonationButton(9, INPUT_PULLUP, 100);
Throttle decreaseIntonationButton(8, INPUT_PULLUP, 100);


int modality = 11;
int octaveForModality[NUMBER_OF_MODALITIES];
int intonationForModality[NUMBER_OF_MODALITIES];

void increaseModality() {
  modality = constrain(modality + 1, 0, NUMBER_OF_MODALITIES);
  printState();
}

void decreaseModality() {
  modality = constrain(modality - 1, 0, NUMBER_OF_MODALITIES);
  printState();
}

void increaseOctave() {
  octaveForModality[modality] = constrain(octaveForModality[modality] + 1, 0, 7);
  printState();
}

void decreaseOctave() {
  octaveForModality[modality] = constrain(octaveForModality[modality] - 1, 0, 7);
  printState();
}

void increaseIntonation() {
  intonationForModality[modality] = constrain(intonationForModality[modality] + 1, 0, 11);
  printState();
}

void decreaseIntonation() {
  intonationForModality[modality] = constrain(intonationForModality[modality] - 1, 0, 11);
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
    return (byte)(modality - 10);
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

void printState() {
  if (DEBUG) {
    Serial.println("");
    Serial.println("Current State:");
    Serial.print("Modality: "); Serial.println(modality);
    Serial.print("Octave: "); Serial.println(octaveForModality[modality]);
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

void setup()
{
  // Is in Pin 13 that is already used
  // pinMode(LED_BUILTIN, OUTPUT);
  // digitalWrite(LED_BUILTIN, LOW);
  
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

  
  pinMode(13, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);

  Serial.begin(9600);

  delay(1000);
  printState();
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
      Serial.write(getNoteOnSerialByte(i));
    }

    if (pads[i].rose())
    {
      noteOff(i);
      Serial.write(getNoteOffSerialByte(i));
    }
  }
  MidiUSB.flush();
}

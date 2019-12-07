#include <Arduino.h>
//#include <Keyboard.h>
#include <MIDIUSB.h>
#include "Throttle/Throttle.h"

// In order to flash the arduino Due(milanove) you have to download the SAMD ( search for "DUE" ) board in the board manager
// keep press the erase button, then press the reset button and then you can program it
// You need to install also MIDIUSB lib

#define velocity 64
#define channel 0
#define octave 4

#define START_PIN 36
#define NUMBER_OF_PINS 18
#define DEBOUNCE_TIME 50

// Keyboard
// B:    | 2 | 4 |   | 7 | 9 | 11 |     | 14 | 16 |
// W:  | 1 | 3 | 5 | 6 | 8 | 10 | 12 | 13 | 15 | 17 | 18 |

// Drum
//   1     2     3     4     5     6
// ( 2 ) ( 4 ) ( 7 ) ( 9 ) ( 11 )( 14 )

//   7     8     9    10     11    12
// ( 1 ) ( 3 ) ( 5 ) ( 6 ) ( 8 ) ( 10 )

//   13    14    15    16    17    18
// ( 12 )( 13 )( 15 )( 17 )( 18 )( 16 )


// char startCharacters[] = {'Q', 'W', 'E', 'R', 'T', 'Y', 'A', 'S', 'D', 'F', 'G', 'H', 'Z', 'X', 'C', 'V', 'B', 'N'};
// char stopCharacters[] = {'q', 'w', 'e', 'r', 't', 'y', 'a', 's', 'd', 'f', 'g', 'h', 'z', 'x', 'c', 'v', 'b', 'n'};
char keyboardCharacters[] = { 'w', 'e', 't', 'y', 'u', 'o', 
                              'a', 's', 'd', 'f', 'g', 'h', 
                              'j', 'k', 'l', ';', '\'', 'p'};

byte midiNoteOffset[] = { 1,  3,  6,  8,  10, 13, 
                          0,  2,  4,  5,  7,  9, 
                          11, 12, 14, 16, 17, 15 };
                                                      
unsigned long lastChangedTime[NUMBER_OF_PINS];
uint8_t previousPressedState[NUMBER_OF_PINS];

// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).

byte noteForPad(int pad) {
  byte offset = midiNoteOffset[pad];
  byte note = (octave + 1) * 12 + offset;
  return note;
}

void noteOn(int pad) {
  byte note = noteForPad(pad);
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, note, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(int pad) {
  byte note = noteForPad(pad);
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, note, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void setup()
{
  // Setup all pins (digital and analog) in INPUT mode (default is nothing)
  /*for (uint32_t ul = 0 ; ul < NUM_DIGITAL_PINS ; ul++ )
  {
    pinMode( ul, INPUT ) ;
  }*/

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  for (int i = 0; i < NUMBER_OF_PINS; i++)
  {
    pinMode(i + START_PIN, INPUT_PULLUP);
  }

  memset(lastChangedTime, 0, sizeof(lastChangedTime));
  memset(previousPressedState, 0, sizeof(previousPressedState));

  //pinMode(LED_BUILTIN, OUTPUT);
  //Serial.begin(9600);
  //Keyboard.begin();
}

void loop()
{
  for (int i = 0; i < NUMBER_OF_PINS; i++)
  {
    unsigned long t = millis();
    if (t - lastChangedTime[i] > DEBOUNCE_TIME)
    {
      bool isPressedState = (digitalRead(i + START_PIN) == LOW);

      if (isPressedState == previousPressedState[i])
        continue;

      if(isPressedState) {
        noteOn(i);
        //Keyboard.press(keyboardCharacters[i]);
      } else {
        noteOff(i);
        //Keyboard.release(keyboardCharacters[i]);
      }
      //Serial.print(isPressedState ? startCharacters[i] : stopCharacters[i]);
      lastChangedTime[i] = t;
      previousPressedState[i] = isPressedState;
    }
  }
  MidiUSB.flush();
}

#include <Arduino.h>
#include <TM1637Display.h>
#include <Adafruit_NeoPixel.h>
#include "MIDIcontroller.h"

// byte MIDIchannel = 1;
// const int drumPin = 23; // Change this to the correct ANALOG pin

// Drum Parameters are: pin, note number (See GM DRUM SOUNDS below)
//MIDIdrum myDrum(drumPin, 38);


void setup() {
  Serial.begin(9600);
}

int val;
void loop() {
  //usbMIDI.sendNoteOn(60, 99, 1);
  // myDrum.send();


  // while (usbMIDI.read()) {
  // }

  val = analogRead(23);
  Serial.println(val);
  delay(10);
}
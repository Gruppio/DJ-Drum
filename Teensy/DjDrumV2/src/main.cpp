#include <Arduino.h>
// #include <TM1637Display.h>
// #include <Adafruit_NeoPixel.h>
//#include "MIDIcontroller.h"
#include "pinout.h"
#include "AnalogThrottle/AnalogThrottle.h"
#include "Core/Core.h"

// byte MIDIchannel = 1;
// const int drumPin = 23; // Change this to the correct ANALOG pin

// Drum Parameters are: pin, note number (See GM DRUM SOUNDS below)
//MIDIdrum myDrum(drumPin, 38);

#define DEBOUNCE_TIME 35
#define PAD_ACTIVATION_THRESHOLD 300

AnalogThrottle pads[NUM_PADS];
Core core;

void setupPads()
{
  for (int i = 0; i < NUM_PADS; i++)
  {
    pads[i].attach(pinPads[i]);
    pads[i].interval(DEBOUNCE_TIME);
    pads[i].setThreshold(PAD_ACTIVATION_THRESHOLD);
  }
}

void setupInternalLed()
{
  pinMode(LED_BUILTIN, OUTPUT);
}

void setupSerial()
{
  Serial.begin(9600);
}

void setup()
{
  setupPads();
  setupInternalLed();
  setupSerial();
}

void loop()
{
  //usbMIDI.sendNoteOn(60, 99, 1);
  // myDrum.send();

  // while (usbMIDI.read()) {
  // }

  for (int i = 0; i < NUM_PADS; i++)
  {
    pads[i].update();

    if (pads[i].fell())
    {
      core.padPressed(i);
    }

    if (pads[i].rose())
    {
      core.padReleased(i);
    }
  }
  //MidiUSB.flush();
  core.updateDisplay();
}

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

#define DEBOUNCE_TIME 10
#define PAD_ACTIVATION_THRESHOLD 200

Core core;
AnalogThrottle pads[NUM_PADS];

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

uint8_t computeMidiVelocityFromIntensity(int intensity) {
  return (uint8_t)map(intensity, 0, 1024, 20, 127);
}

void setup()
{
  setupPads();
  setupInternalLed();
  setupSerial();
}


void loop()
{
  for (int i = 0; i < NUM_PADS; i++)
  {
    pads[i].update();

    if (pads[i].fell())
    {
      int intensity = pads[i].intensity();
      int velocity = computeMidiVelocityFromIntensity(intensity);
      core.padPressed(i, velocity);
    }
  }

  core.update();
  core.updateDisplay();
}

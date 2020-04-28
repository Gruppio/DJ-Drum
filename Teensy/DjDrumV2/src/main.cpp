#include <Arduino.h>
#include "pinout.h"
#include "AnalogThrottle/AnalogThrottle.h"
#include "Core/Core.h"


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
  return (uint8_t)map(intensity, 0, 1024, 0, 127);
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

#include <Arduino.h>
#include "pinout.h"
#include "AnalogThrottle/AnalogThrottle.h"
#include "Core/Core.h"


#define DEBOUNCE_TIME 10
#define PAD_ACTIVATION_THRESHOLD 200



Core core;
AnalogThrottle pads[NUM_PADS];

uint8_t pinPads[] = {
    PIN_PAD1,
    PIN_PAD2,
    PIN_PAD3,
    PIN_PAD4,
    PIN_PAD5,
    PIN_PAD6,
    PIN_PAD7,
    PIN_PAD8,
    PIN_PAD9,
    PIN_PAD10,
    PIN_PAD11,
    PIN_PAD12,
    PIN_PAD13,
    PIN_PAD14,
    PIN_PAD15,
    PIN_PAD16,
    PIN_PAD17,
    PIN_PAD18
};

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

void setupI2C()
{
  pinMode(PIN_SDA, OUTPUT);
  pinMode(PIN_SCL, OUTPUT);
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
  setupI2C();
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

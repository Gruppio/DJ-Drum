#include <Arduino.h>
#include "pinout.h"
#include "AnalogThrottle/AnalogThrottle.h"
#include "Core/Core.h"
#include "Throttle.h"


#define DEBOUNCE_TIME 50
#define PAD_ACTIVATION_THRESHOLD 350
Core core;
AnalogThrottle pads[NUM_PADS];
Throttle decrScaleButton(PIN_BUTTON6, INPUT_PULLUP, 100);
Throttle incrScaleButton(PIN_BUTTON5, INPUT_PULLUP, 100);
Throttle decrOctaveButton(PIN_BUTTON4, INPUT_PULLUP, 100);
Throttle incrOctaveButton(PIN_BUTTON3, INPUT_PULLUP, 100);
Throttle decrIntonationButton(PIN_BUTTON2, INPUT_PULLUP, 100);
Throttle incrIntonationButton(PIN_BUTTON1, INPUT_PULLUP, 100);
Throttle decrChannelButton(PIN_FOOTSWITCH1, INPUT_PULLUP, 100);
Throttle incrChannelButton(PIN_FOOTSWITCH2, INPUT_PULLUP, 100);
Throttle recordingButton(PIN_FOOTSWITCH4, INPUT_PULLUP, 100);

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

void setupPotentiometers()
{
  pinMode(PIN_VOLUME_POTENTIOMETER, INPUT);
  pinMode(PIN_VELOCITY_POTENTIOMETER, INPUT);
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
  pinMode(PIN_TX, OUTPUT);
  Serial.begin(9600);
  Serial1.begin(9600);
}

void setup()
{
  setupPads();
  setupPotentiometers();
  setupInternalLed();
  setupI2C();
  setupSerial();
}

int oldDurationReadValue = 0;
void updateNoteDuration() {
  int readValue = analogRead(PIN_VOLUME_POTENTIOMETER);
  if (abs(readValue - oldDurationReadValue) > 10) {
    int noteDuration = map(readValue, 0, 1024, 0, 2000);
    core.setNoteDuration(noteDuration);
    oldDurationReadValue = readValue;
  }
}

int oldVelocityReadValue = 0;
void updateNoteVelocity() {
  int readValue = analogRead(PIN_VELOCITY_POTENTIOMETER);
  if (abs(readValue - oldVelocityReadValue) > 10) {
    int noteVelocity = map(readValue, 0, 1024, 0, 127);
    core.setNoteVelocity((uint8_t) noteVelocity);
    oldVelocityReadValue = readValue;
  }
}

uint8_t computeMidiVelocityFromIntensity(int intensity) {
  return (uint8_t)map(intensity, 0, 1024, 0, 127);
}

int loopCount = 0;
bool everyLoop(int n) {
  return (loopCount % n) == 0;
}

void loop()
{
  // Update Pads
  for (int i = 0; i < NUM_PADS; i++)
  {
    pads[i].update();

    if (pads[i].fell())
    {
      //int intensity = pads[i].intensity();
      //int velocity = computeMidiVelocityFromIntensity(intensity);
      core.padPressed(i, 0);
    }
  }

  // Update Buttons
  decrScaleButton.update();
  incrScaleButton.update();
  decrOctaveButton.update();
  incrOctaveButton.update();
  decrIntonationButton.update();
  incrIntonationButton.update();
  decrChannelButton.update();
  incrChannelButton.update();
  recordingButton.update();

  if(decrScaleButton.fell()) { core.decrScale(); };
  if(incrScaleButton.fell()) { core.incrScale(); };
  if(decrOctaveButton.fell()) { core.decrOctave(); };
  if(incrOctaveButton.fell()) { core.incrOctave(); };
  if(decrIntonationButton.fell()) { core.decrIntonation(); };
  if(incrIntonationButton.fell()) { core.incrIntonation(); };
  if(decrChannelButton.fell()) { core.decrChannel(); };
  if(incrChannelButton.fell()) { core.incrChannel(); };
  if(recordingButton.fell()) { core.didPressRecording(); };
  if(recordingButton.rose()) { core.didReleaseRecording(); };

  if (everyLoop(50)) {
    updateNoteDuration();
    updateNoteVelocity();
  }

  core.update();

  if (everyLoop(50))
    core.updateDisplay();

  loopCount++;
}

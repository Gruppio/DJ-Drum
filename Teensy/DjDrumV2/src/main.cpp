#include <Arduino.h>
//efine FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>


#define NUM_LEDS 1
#define DATA_PIN 2
CRGB leds[NUM_LEDS];

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
}


void loop() { 
  // Turn the LED on, then pause
  digitalWrite(LED_BUILTIN, HIGH);
  leds[0] = CRGB::Red;
  FastLED.show();
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  // Now turn the LED off, then pause
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(500);
  
}

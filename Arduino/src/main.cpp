#include <Arduino.h>

#define START_PIN 2
#define NUMBER_OF_PINS 18
#define DEBOUNCE_TIME 100

char characters[] = {'z', 'x', 'c', 'v', 'b', 'n', 'a', 's', 'd', 'f', 'g', 'h', 'q', 'w', 'e', 'r', 't', 'y'};
bool oldValues[NUMBER_OF_PINS];
unsigned long timeTriggered[NUMBER_OF_PINS];

void setup() {
  for(int i = 0; i < NUMBER_OF_PINS; i++) {
    pinMode(i + START_PIN, INPUT_PULLUP);
  }

  memset(oldValues, 0, sizeof(oldValues));
  memset(timeTriggered, 0, sizeof(timeTriggered));

  //pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long t = millis();

  for(int i = 0; i < NUMBER_OF_PINS; i++) {
    bool isPressed = (digitalRead(i + START_PIN) == LOW);
    bool oldValueIsPressed = oldValues[i];
    if(isPressed && !oldValueIsPressed && (t - timeTriggered[i]) > DEBOUNCE_TIME) {
      Serial.print(characters[i]);
      timeTriggered[i] = t;
    }
    oldValues[i] = isPressed;
  }
  
}

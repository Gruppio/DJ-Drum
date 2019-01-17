#include <Arduino.h>

#define START_PIN 36
#define NUMBER_OF_PINS 18
#define DEBOUNCE_TIME 100

char characters[] = { 'q', 'w', 'e', 'r', 't', 'y', 'a', 's', 'd', 'f', 'g', 'h', 'z', 'x', 'c', 'v', 'b', 'n'};
unsigned long lastPressTime[NUMBER_OF_PINS];

void setup() {
  for(int i = 0; i < NUMBER_OF_PINS; i++) {
    pinMode(i + START_PIN, INPUT_PULLUP);
  }

  memset(lastPressTime, 0, sizeof(lastPressTime));

  //pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  for(int i = 0; i < NUMBER_OF_PINS; i++) {
    bool isPressed = (digitalRead(i + START_PIN) == LOW);
	if (isPressed) {
		unsigned long t = millis();
		if(t - lastPressTime[i] > DEBOUNCE_TIME) {
			Serial.print(characters[i]);
		}
		lastPressTime[i] = t;
	}
  }
}

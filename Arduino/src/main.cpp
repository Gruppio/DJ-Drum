#include <Arduino.h>
#include <Bounce2.h>

#define START_PIN 36
#define NUMBER_OF_PINS 18
#define DEBOUNCE_TIME 3

char startCharacters[] = { 'Q', 'W', 'E', 'R', 'T', 'Y', 'A', 'S', 'D', 'F', 'G', 'H', 'Z', 'X', 'C', 'V', 'B', 'N'};
char stopCharacters[] =  { 'q', 'w', 'e', 'r', 't', 'y', 'a', 's', 'd', 'f', 'g', 'h', 'z', 'x', 'c', 'v', 'b', 'n'};
Bounce * buttons = new Bounce[NUMBER_OF_PINS];

void setup() {
  for(int i = 0; i < NUMBER_OF_PINS; i++) {
    buttons[i].attach(i + START_PIN, INPUT_PULLUP);
    buttons[i].interval(DEBOUNCE_TIME);
  }

  //pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  for(int i = 0; i < NUMBER_OF_PINS; i++) {
    buttons[i].update();
    if(buttons[i].fell()) {
      Serial.print(startCharacters[i]);
    } else if(buttons[i].rose()) {
      Serial.print(stopCharacters[i]);
    }
  }
}

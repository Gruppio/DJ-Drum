#include <Arduino.h>
#include <Keyboard.h>

void setup() {
  Keyboard.begin();
}

void loop() {
  Keyboard.print("ciao");
  // Keyboard.press('a');
  // delay(100);
  // Keyboard.release('a');
  delay(1000);
}
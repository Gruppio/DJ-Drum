//#include <Arduino.h>
#include<Keyboard.h>

#define START_PIN 36
#define NUMBER_OF_PINS 18
#define DEBOUNCE_TIME 50

char startCharacters[] = {'Q', 'W', 'E', 'R', 'T', 'Y', 'A', 'S', 'D', 'F', 'G', 'H', 'Z', 'X', 'C', 'V', 'B', 'N'};
char stopCharacters[] = {'q', 'w', 'e', 'r', 't', 'y', 'a', 's', 'd', 'f', 'g', 'h', 'z', 'x', 'c', 'v', 'b', 'n'};
unsigned long lastChangedTime[NUMBER_OF_PINS];
uint8_t previousPressedState[NUMBER_OF_PINS];

void setup()
{
  for (int i = 0; i < NUMBER_OF_PINS; i++)
  {
    pinMode(i + START_PIN, INPUT_PULLUP);
  }

  memset(lastChangedTime, 0, sizeof(lastChangedTime));
  memset(previousPressedState, 0, sizeof(previousPressedState));

  //pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  for (int i = 0; i < NUMBER_OF_PINS; i++)
  {
    unsigned long t = millis();
    if (t - lastChangedTime[i] > DEBOUNCE_TIME)
    {
      bool isPressedState = (digitalRead(i + START_PIN) == LOW);

      if (isPressedState == previousPressedState[i])
        continue;
      Serial.print(isPressedState ? startCharacters[i] : stopCharacters[i]);
      lastChangedTime[i] = t;
      previousPressedState[i] = isPressedState;
    }
  }
}

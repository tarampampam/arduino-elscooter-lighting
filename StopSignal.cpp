#include <Arduino.h>
#include "StopSignal.h"

void StopSignal::init()
{
  pinMode(buttonPin, INPUT);
  pinMode(lightPin, OUTPUT);
}

bool StopSignal::buttonIsPressed()
{
  return digitalRead(buttonPin) == LOW;
}

/// Do the main stop signal logic here.
void StopSignal::tick()
{
  if (buttonIsPressed())
  {
    uint32_t currentTimeMs = millis();

    if (currentTimeMs >= timers.enableLightAt)
    {
      timers.enableLightAt = currentTimeMs + powerOnTime + blinkingInterval;
      timers.disableLightAt = currentTimeMs + powerOnTime;

      digitalWrite(lightPin, HIGH);
    }
    else if (currentTimeMs >= timers.disableLightAt)
    {
      digitalWrite(lightPin, LOW);
    }
  }
  else
  {
    digitalWrite(lightPin, LOW);

    // reset timers state
    if (timers.enableLightAt != 0 || timers.disableLightAt != 0)
    {
      timers.enableLightAt = 0;
      timers.disableLightAt = 0;
    }
  }
}

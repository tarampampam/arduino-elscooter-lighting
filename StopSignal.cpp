#include <Arduino.h>
#include "StopSignal.h"

void StopSignal::init()
{
  pinMode(lightPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

bool StopSignal::buttonIsPressed()
{
  return digitalRead(buttonPin) == LOW;
}

/// Do the main stop signal logic here.
void StopSignal::tick()
{
  // internal timers state
  static struct
  {
    uint32_t enableLightAt, disableLightAt;
  } timers;

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
    if (digitalRead(lightPin) != LOW)
    {
      digitalWrite(lightPin, LOW);
    }

    // reset timers state
    if (timers.enableLightAt != 0 || timers.disableLightAt != 0)
    {
      timers.enableLightAt = 0;
      timers.disableLightAt = 0;
    }
  }
}

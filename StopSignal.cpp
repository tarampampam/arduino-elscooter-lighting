#include <Arduino.h>
#include "StopSignal.h"

StopSignal::StopSignal(uint8_t bPin, uint8_t lPin)
{
  pinMode(lightPin = lPin, OUTPUT);
  pinMode(buttonPin = bPin, INPUT);
}

bool StopSignal::buttonIsOn()
{
  return digitalRead(buttonPin) == LOW;
}

/// Do the main stop signal logic here.
void StopSignal::tick()
{
  if (buttonIsOn())
  {
    uint32_t currentTimeMs = millis();

    if (currentTimeMs >= enableLightAt)
    {
      enableLightAt = currentTimeMs + powerOnTime + blinkingInterval;
      disableLightAt = currentTimeMs + powerOnTime;

      digitalWrite(lightPin, HIGH);
    }
    else if (currentTimeMs >= disableLightAt)
    {
      digitalWrite(lightPin, LOW);
    }
  }
  else
  {
    digitalWrite(lightPin, LOW);

    // reset timers state
    if (enableLightAt != 0 || disableLightAt != 0)
    {
      enableLightAt = 0;
      disableLightAt = 0;
    }
  }
}

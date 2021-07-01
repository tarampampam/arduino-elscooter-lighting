#include <Arduino.h>
#include "TurningLights.h"

void TurningLights::init()
{
  pinMode(leftLightPin, OUTPUT);
  pinMode(rightLightPin, OUTPUT);

  pinMode(leftButtonPin, INPUT);
  pinMode(rightButtonPin, INPUT);
}

bool TurningLights::leftButtonIsPressed()
{
  return digitalRead(leftButtonPin) == LOW;
}

bool TurningLights::rightButtonIsPressed()
{
  return digitalRead(rightButtonPin) == LOW;
}

/// Do the main turning lights logic here.
void TurningLights::tick()
{
  bool lBtnPressed = leftButtonIsPressed(), rBtnPressed = rightButtonIsPressed();

  // if any button is pressed
  if (lBtnPressed || rBtnPressed)
  {
    uint32_t currentTimeMs = millis();

    if (currentTimeMs >= timers.enableLightAt)
    {
      timers.enableLightAt = currentTimeMs + powerOnTime + blinkingInterval;
      timers.disableLightAt = currentTimeMs + powerOnTime;

      if (lBtnPressed)
      {
        digitalWrite(leftLightPin, HIGH);
      }
      if (rBtnPressed)
      {
        digitalWrite(rightLightPin, HIGH);
      }
    }

    if (currentTimeMs >= timers.disableLightAt)
    {
      digitalWrite(rightLightPin, LOW);
      digitalWrite(leftLightPin, LOW);
    }
  }
  else
  {
    if (digitalRead(rightLightPin) != LOW)
    {
      digitalWrite(rightLightPin, LOW);
    }

    if (digitalRead(leftLightPin) != LOW)
    {
      digitalWrite(leftLightPin, LOW);
    }

    // reset timers state
    if (timers.enableLightAt != 0 || timers.disableLightAt != 0)
    {
      timers.enableLightAt = 0;
      timers.disableLightAt = 0;
    }
  }
}

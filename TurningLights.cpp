#include <Arduino.h>
#include "TurningLights.h"

void TurningLights::init()
{
  pinMode(leftLightPin, OUTPUT);
  pinMode(rightLightPin, OUTPUT);

  pinMode(leftButtonPin, INPUT);
  pinMode(rightButtonPin, INPUT);
}

/// Do the main turning lights logic here.
void TurningLights::tick()
{
  // read current buttons state
  struct
  {
    bool LeftIsPressed, RightIsPressed;
  } btnState = {
    LeftIsPressed : digitalRead(leftButtonPin) == LOW,
    RightIsPressed : digitalRead(rightButtonPin) == LOW,
  };

  // internal timers state
  static struct
  {
    uint32_t enableLightAt, disableLightAt;
  } timers;

  // if any button is pressed
  if (btnState.LeftIsPressed || btnState.RightIsPressed)
  {
    uint32_t currentTimeMs = millis();

    if (currentTimeMs >= timers.enableLightAt)
    {
      timers.enableLightAt = currentTimeMs + powerOnTime + blinkingInterval;
      timers.disableLightAt = currentTimeMs + powerOnTime;

      if (btnState.LeftIsPressed)
      {
        digitalWrite(leftLightPin, HIGH);
      }
      if (btnState.RightIsPressed)
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

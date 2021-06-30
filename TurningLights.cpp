#include <Arduino.h>
#include "TurningLights.h"

TurningLights::TurningLights(uint8_t leftBtnPin, uint8_t rightBtnPin, uint8_t leftLgtPin, uint8_t rightLgtPin)
{
  pinMode(leftLightPin = leftLgtPin, OUTPUT);
  pinMode(rightLightPin = rightLgtPin, OUTPUT);

  pinMode(leftButtonPin = leftBtnPin, INPUT);
  pinMode(rightButtonPin = rightBtnPin, INPUT);
}

void TurningLights::updateButtonsState()
{
  leftButtonIsOn = digitalRead(leftButtonPin) == LOW;
  rightButtonIsOn = digitalRead(rightButtonPin) == LOW;
}

/// Do the main turning lights logic here.
void TurningLights::tick()
{
  updateButtonsState();

  if (leftButtonIsOn || rightButtonIsOn)
  {
    uint32_t currentTimeMs = millis();

    if (currentTimeMs >= enableLightAt)
    {
      enableLightAt = currentTimeMs + powerOnTime + blinkingInterval;
      disableLightAt = currentTimeMs + powerOnTime;

      if (leftButtonIsOn)
      {
        digitalWrite(leftLightPin, HIGH);
      }
      if (rightButtonIsOn)
      {
        digitalWrite(rightLightPin, HIGH);
      }
    }

    if (currentTimeMs >= disableLightAt)
    {
      digitalWrite(rightLightPin, LOW);
      digitalWrite(leftLightPin, LOW);
    }
  }
  else
  {
    digitalWrite(rightLightPin, LOW);
    digitalWrite(leftLightPin, LOW);

    // reset timers state
    if (enableLightAt != 0 || disableLightAt != 0)
    {
      enableLightAt = 0;
      disableLightAt = 0;
    }
  }
}

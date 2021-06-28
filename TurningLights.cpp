#include <Arduino.h>
#include "TurningLights.h"

TurningLights::TurningLights(uint8_t leftBtnPin, uint8_t rightBtnPin, uint8_t leftLgtPin, uint8_t rightLgtPin)
{
  leftButtonPin = leftBtnPin;
  rightButtonPin = rightBtnPin;
  leftLightPin = leftLgtPin;
  rightLightPin = rightLgtPin;

  pinMode(leftLightPin, OUTPUT);
  pinMode(rightLightPin, OUTPUT);

  pinMode(leftButtonPin, INPUT_PULLUP);
  pinMode(rightButtonPin, INPUT_PULLUP);
}

void TurningLights::updateButtonsState()
{
  leftButtonIsOn = digitalRead(leftButtonPin) == LOW;
  rightButtonIsOn = digitalRead(rightButtonPin) == LOW;

  if (debugModeEnabled)
  {
    Serial.println("[debug] LEFT|RIGHT turning button is " + String(leftButtonIsOn ? "ON" : "OFF") + "|" + String(rightButtonIsOn ? "ON" : "OFF"));
  }
}

/// Do the main turning lights logic.
void TurningLights::tick()
{
  updateButtonsState();

  uint32_t currentTimeMs = millis();

  if (leftButtonIsOn || rightButtonIsOn)
  {
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
    enableLightAt = 0;
    disableLightAt = 0;
  }
}

#include <Arduino.h>
#include "TurningLights.h"

#define LEFT_TURNING_IN_PIN 2    // D2
#define RIGHT_TURNING_IN_PIN 3   // D3
#define LEFT_TURNING_OUT_PIN 11  // D11
#define RIGHT_TURNING_OUT_PIN 12 // D12

TurningLights turnings(LEFT_TURNING_IN_PIN, RIGHT_TURNING_IN_PIN, LEFT_TURNING_OUT_PIN, RIGHT_TURNING_OUT_PIN);

void setup()
{
  // do nothing
}

void loop()
{
  turnings.tick();
}

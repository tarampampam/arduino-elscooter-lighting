#include <Arduino.h>
#include "TurningLights.h"
#include "StopSignal.h"

#define LEFT_TURNING_IN_PIN 2    // D2
#define RIGHT_TURNING_IN_PIN 3   // D3
#define LEFT_TURNING_OUT_PIN 11  // D11
#define RIGHT_TURNING_OUT_PIN 12 // D12

#define STOP_SIGNAL_IN_PIN 4   // D4
#define STOP_SIGNAL_OUT_PIN 10 // D10

TurningLights turnings(LEFT_TURNING_IN_PIN, RIGHT_TURNING_IN_PIN, LEFT_TURNING_OUT_PIN, RIGHT_TURNING_OUT_PIN);
StopSignal stopSignal(STOP_SIGNAL_IN_PIN, STOP_SIGNAL_OUT_PIN);

void setup()
{
  turnings.init();
  stopSignal.init();
}

void loop()
{
  turnings.tick();
  stopSignal.tick();
}

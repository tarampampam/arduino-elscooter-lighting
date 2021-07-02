#include "TurningLights.h"
#include "StopSignal.h"
#include "DRL.h"

#define LEFT_TURNING_IN_PIN 2    // phisical pin #5
#define RIGHT_TURNING_IN_PIN 3   // phisical pin #6
#define LEFT_TURNING_OUT_PIN 11  // phisical pin #14
#define RIGHT_TURNING_OUT_PIN 12 // phisical pin #15

#define STOP_SIGNAL_IN_PIN 4   // phisical pin #7
#define STOP_SIGNAL_OUT_PIN 10 // phisical pin #13

#define DRL_IN_PIN 5        // phisical pin #8
#define DRL_FRONT_OUT_PIN 9 // phisical pin #12
#define DRL_BACK_OUT_PIN 8  // phisical pin #11

TurningLights turnings(LEFT_TURNING_IN_PIN, RIGHT_TURNING_IN_PIN, LEFT_TURNING_OUT_PIN, RIGHT_TURNING_OUT_PIN);
StopSignal stopSignal(STOP_SIGNAL_IN_PIN, STOP_SIGNAL_OUT_PIN);
DRL drl(DRL_IN_PIN, DRL_FRONT_OUT_PIN, DRL_BACK_OUT_PIN, STOP_SIGNAL_IN_PIN);

void setup()
{
  // turnings.blinkingInterval = 400;
  // turnings.powerOnTime = 500;
  turnings.init();

  // stopSignal.blinkingInterval = 100;
  // stopSignal.powerOnTime = 150;
  stopSignal.init();

  // drl.blinkingInterval = 100;
  // drl.powerOnTime = 150;
  drl.init();
}

void loop()
{
  turnings.tick();
  stopSignal.tick();
  drl.tick();
}

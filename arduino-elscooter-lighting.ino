#include "IO.h"
#include "TurningLights.h"
#include "StopSignal.h"
// #include "DRL.h"

InputSwitch leftTurningButton(2);  // phisical pin #5
InputSwitch rightTurningButton(3); // phisical pin #6
InputSwitch stopSignalButton(4);   // phisical pin #7
InputSwitch drlSwitch(5);          // phisical pin #8
OutputKey backDrlKey(8);           // phisical pin #11
OutputKey frontDrlKey(9);          // phisical pin #12
OutputKey stopSignalKey(10);       // phisical pin #13
OutputKey leftTurningKey(11);      // phisical pin #14
OutputKey rightTurningKey(12);     // phisical pin #15

TurningLights turnings(&leftTurningButton, &rightTurningButton, &leftTurningKey, &rightTurningKey);
StopSignal stopSignal(&stopSignalButton, &stopSignalKey);
// DRL drl(DRL_IN_PIN, DRL_FRONT_OUT_PIN, DRL_BACK_OUT_PIN, STOP_SIGNAL_IN_PIN);

void setup()
{
  leftTurningButton.init();
  rightTurningButton.init();
  stopSignalButton.init();
  drlSwitch.init();
  backDrlKey.init();
  frontDrlKey.init();
  stopSignalKey.init();
  leftTurningKey.init();
  rightTurningKey.init();
}

void loop()
{
  unsigned long currentTimeMs = millis();

  turnings.tick(currentTimeMs);
  stopSignal.tick(currentTimeMs);
  // drl.tick(currentTimeMs);
}

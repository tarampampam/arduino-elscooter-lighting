#include "TurningLights.h"
#include "PWM.h"
#include "IO.h"

TurningLights::TurningLights(InputSwitch *leftSw, InputSwitch *rightSw, OutputKey *leftKey, OutputKey *rightKey)
{
  leftInput = leftSw;
  rightInput = rightSw;
  leftOutput = leftKey;
  rightOutput = rightKey;

  pwm = new PWM(500 + 400, 400);
}

void TurningLights::setBlinkingInterval(unsigned int on, unsigned int off)
{
  pwm->setPeriodTime(on + off);
  pwm->setImpulseTime(off);
}

/// Do the main stop signal logic here.
void TurningLights::tick(unsigned long currentTimeMs)
{
  bool leftInputIsOn = leftInput->isOn(), rightInputIsOn = rightInput->isOn();

  if (leftInputIsOn || rightInputIsOn)
  {
    switch (pwm->tick(currentTimeMs))
    {
    case PWM_HIGH:
      if (leftInputIsOn)
      {
        leftOutput->open();
      }
      if (rightInputIsOn)
      {
        rightOutput->open();
      }
      break;

    case PWM_LOW:
      leftOutput->close();
      rightOutput->close();
      break;
    }
  }
  else
  {
    leftOutput->close();
    rightOutput->close();
    pwm->reset();
  }
}

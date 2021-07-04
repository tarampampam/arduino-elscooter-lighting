#include "TurningLights.h"
#include "PWM.h"
#include "IO.h"

TurningLights::TurningLights(InputSwitch *leftSw, InputSwitch *rightSw, OutputKey *leftKey, OutputKey *rightKey)
{
  leftInput = leftSw, rightInput = rightSw;
  leftOutput = leftKey, rightOutput = rightKey;

  pwm = new PWM;
  pwm->setFrequency(NORMAL);
}

void TurningLights::setBlinkingFrequency(Frequency f)
{
  pwm->setFrequency(f);
}

/// Do the main stop signal logic here.
void TurningLights::tick(unsigned long int currentTimeMicros)
{
  bool leftInputIsOn = leftInput->isOn(), rightInputIsOn = rightInput->isOn();

  if (leftInputIsOn || rightInputIsOn)
  {
    switch (pwm->tick(currentTimeMicros))
    {
    case PWM_HIGH:
      leftInputIsOn ? leftOutput->open() : leftOutput->close();
      rightInputIsOn ? rightOutput->open() : rightOutput->close();
      break;

    case PWM_LOW:
      leftOutput->close();
      rightOutput->close();
      break;

    case PWM_NONE:
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

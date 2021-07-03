#include "StopSignal.h"
#include "PWM.h"
#include "IO.h"

StopSignal::StopSignal(InputSwitch *sw, OutputKey *key)
{
  input = sw, output = key;

  pwm = new PWM(320000, 250000);
}

void StopSignal::setBlinkingInterval(unsigned long int on, unsigned long int off)
{
  pwm->setPeriodTime(on + off);
  pwm->setImpulseTime(off);
}

/// Do the main stop signal logic here.
void StopSignal::tick(unsigned long int currentTimeMicros)
{
  if (input->isOn())
  {
    switch (pwm->tick(currentTimeMicros))
    {
    case PWM_HIGH:
      output->open();
      break;

    case PWM_LOW:
      output->close();
      break;

    case PWM_NONE:
      break;
    }
  }
  else
  {
    output->close();
    pwm->reset();
  }
}

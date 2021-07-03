#include "StopSignal.h"
#include "PWM.h"
#include "IO.h"

StopSignal::StopSignal(InputSwitch *sw, OutputKey *key)
{
  input = sw, output = key;

  pwm = new PWM(150 + 100, 100);
}

void StopSignal::setBlinkingInterval(unsigned int on, unsigned int off)
{
  pwm->setPeriodTime(on + off);
  pwm->setImpulseTime(off);
}

/// Do the main stop signal logic here.
void StopSignal::tick(unsigned long currentTimeMs)
{
  if (input->isOn())
  {
    switch (pwm->tick(currentTimeMs))
    {
    case PWM_HIGH:
      output->open();
      break;

    case PWM_LOW:
      output->close();
      break;
    }
  }
  else
  {
    output->close();
    pwm->reset();
  }
}

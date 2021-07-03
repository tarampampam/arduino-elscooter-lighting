#include "PWM.h"

PWM::PWM(unsigned int period, unsigned int impulse)
{
  setPeriodTime(period);
  setImpulseTime(impulse);
}

void PWM::setPeriodTime(unsigned int t)
{
  period = (t < impulse) ? impulse : t; // period time cannot be less than impulse time
}

void PWM::setImpulseTime(unsigned int t)
{
  impulse = (t > period) ? period : t; // impulse time cannot be greater than period time
}

Signal PWM::tick(unsigned long currentTimeMs)
{
  if (started)
  {
    if (currentTimeMs >= highSignalAt)
    {
      highSignalAt = currentTimeMs + period; // set time for the NEXT high signal
      lowSignalAt = currentTimeMs + impulse;

      return PWM_HIGH;
    }

    if (currentTimeMs >= lowSignalAt)
    {
      return PWM_LOW;
    }
  }

  return PWM_NONE;
}

void PWM::reset()
{
  highSignalAt = 0;
  lowSignalAt = 0;
}

bool PWM::isStarted()
{
  return started;
}

void PWM::start()
{
  started = true;
}

void PWM::stop()
{
  started = false;
}

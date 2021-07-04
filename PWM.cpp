#include "PWM.h"

PWM::PWM()
{
  setFrequency(NORMAL);
}

PWM::PWM(unsigned long int period, unsigned long int impulse)
{
  setPeriodTime(period);
  setImpulseTime(impulse);
}

void PWM::setFrequency(Frequency f)
{
  switch (f)
  {
  case ALWAYS:
    setPeriodTime(10000), setImpulseTime(10000);
    break;

  case VERY_SLOW:
    setPeriodTime(2560000), setImpulseTime(1280000);
    break;

  case SLOW:
    setPeriodTime(1280000), setImpulseTime(640000);
    break;

  case NORMAL:
    setPeriodTime(640000), setImpulseTime(320000);
    break;

  case FAST:
    setPeriodTime(320000), setImpulseTime(160000);
    break;

  case FAST_SMALL_DELAY:
    setPeriodTime(320000), setImpulseTime(220000);
    break;

  case VERY_FAST:
    setPeriodTime(160000), setImpulseTime(80000);
    break;

  case VERY_VERY_FAST:
    setPeriodTime(80000), setImpulseTime(40000);
    break;

  case NEVER:
    setPeriodTime(10000), setImpulseTime(0);
    break;
  }
}

void PWM::setPeriodTime(unsigned long int t)
{
  period = (t < impulse) ? impulse : t; // period time cannot be less than impulse time
}

void PWM::setImpulseTime(unsigned long int t)
{
  impulse = (t > period) ? period : t; // impulse time cannot be greater than period time
}

Signal PWM::tick(unsigned long int currentTimeMicros)
{
  if (started)
  {
    if (period == impulse)
    {
      return PWM_HIGH;
    }

    if (impulse == 0)
    {
      return PWM_LOW;
    }

    if (currentTimeMicros >= highSignalAt)
    {
      highSignalAt = currentTimeMicros + period; // set time for the NEXT high signal
      lowSignalAt = currentTimeMicros + impulse;

      return PWM_HIGH;
    }

    if (currentTimeMicros >= lowSignalAt)
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

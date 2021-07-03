#include "DRL.h"
#include "PWM.h"
#include "IO.h"

DRL::DRL(InputSwitch *sw, InputSwitch *stopSw, OutputKey *frontKey, OutputKey *backKey)
{
  input = sw, stopInput = stopSw;
  outputFront = frontKey, outputBack = backKey;

  pwm = new PWM();
  pwm->setFrequency(FAST_SMALL_DELAY);
}

void DRL::setBlinkingFrequency(Frequency f)
{
  pwm->setFrequency(f);
}

void DRL::setBlinkingInterval(unsigned long int on, unsigned long int off)
{
  pwm->setPeriodTime(on + off);
  pwm->setImpulseTime(off);
}

/// Do the main stop signal logic here.
void DRL::tick(unsigned long int currentTimeMicros)
{
  bool switchIsOn = input->isOn();

  // front key logic is very simple
  switchIsOn ? outputFront->open() : outputFront->close();

  if (stopInput->isOn())
  {
    switch (pwm->tick(currentTimeMicros))
    {
    case PWM_HIGH:
      outputBack->open();
      break;

    case PWM_LOW:
      outputBack->close();
      break;

    case PWM_NONE:
      break;
    }
  }
  else
  {
    pwm->reset();

    // keep back light logis simple
    switchIsOn ? outputBack->open() : outputBack->close();
  }
}

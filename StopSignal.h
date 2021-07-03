
#ifndef StopSignal_h
#define StopSignal_h
#include "PWM.h"
#include "IO.h"

class StopSignal
{
public:
  StopSignal() = delete;
  StopSignal(InputSwitch *sw, OutputKey *key);
  void setBlinkingInterval(unsigned int on, unsigned int off);
  void tick(unsigned long /* millis() */);

private:
  InputSwitch *input;
  OutputKey *output;
  PWM *pwm;
};

#endif

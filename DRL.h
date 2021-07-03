#ifndef DRL_h
#define DRL_h
#include "PWM.h"
#include "IO.h"

class DRL
{
public:
  DRL() = delete;
  DRL(InputSwitch *sw, OutputKey *frontKey, OutputKey *backKey);
  void setBlinkingInterval(unsigned long int on, unsigned long int off);
  void tick(unsigned long int /* micros() */);

private:
  InputSwitch *input;
  OutputKey *outputFront, *outputBack;
  PWM *pwm;
};

#endif

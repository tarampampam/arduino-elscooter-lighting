
#ifndef StopSignal_h
#define StopSignal_h
#include "PWM.h"
#include "IO.h"

class StopSignal
{
public:
  StopSignal() = delete;
  StopSignal(InputSwitch *sw, OutputKey *key);
  void setBlinkingFrequency(Frequency);
  void setBlinkingInterval(unsigned long int on, unsigned long int off);
  void tick(unsigned long int /* micros() */);

private:
  InputSwitch *input;
  OutputKey *output;
  PWM *pwm;
};

#endif

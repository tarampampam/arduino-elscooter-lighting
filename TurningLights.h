#ifndef TurningLights_h
#define TurningLights_h
#include "PWM.h"
#include "IO.h"

class TurningLights
{
public:
  TurningLights() = delete;
  TurningLights(InputSwitch *leftSw, InputSwitch *rightSw, OutputKey *leftKey, OutputKey *rightKey);
  void setBlinkingInterval(unsigned int on, unsigned int off);
  void tick(unsigned long /* millis() */);

private:
  InputSwitch *leftInput, *rightInput;
  OutputKey *leftOutput, *rightOutput;
  PWM *pwm;
};

#endif

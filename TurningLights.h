#ifndef TurningLights_h
#define TurningLights_h
#include "PWM.h"
#include "IO.h"

class TurningLights
{
public:
  TurningLights() = delete;
  TurningLights(InputSwitch *leftSw, InputSwitch *rightSw, OutputKey *leftKey, OutputKey *rightKey);
  void setBlinkingFrequency(Frequency);
  void tick(unsigned long int /* micros() */);

private:
  InputSwitch *leftInput, *rightInput;
  OutputKey *leftOutput, *rightOutput;
  PWM *pwm;
};

#endif

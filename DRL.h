#ifndef DRL_h
#define DRL_h
#include "PWM.h"
#include "Clicker.h"
#include "IO.h"

// DRL is a "Daytime running lights".
class DRL
{
public:
  DRL() = delete;
  DRL(InputSwitch *sw, InputSwitch *stopSw, OutputKey *frontKey, OutputKey *backKey);
  void setFrontBlinkingFrequency(Frequency);
  void setBackBlinkingFrequency(Frequency);
  void tick(unsigned long int /* micros() */);

private:
  InputSwitch *input, *stopInput;
  OutputKey *outputFront, *outputBack;
  PWM *pwmFront, *pwmBack; // back PWM is pluggable
  Clicker *clicker;
  bool frontBlinkingEnabled = false;
};

#endif

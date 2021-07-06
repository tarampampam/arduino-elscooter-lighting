#ifndef DRL_h
#define DRL_h
#include "PWM.h"
#include "Clicker.h"
#include "IO.h"

#define DRL_EEPROM_SETTINGS_FRONT_BLINKING_ENABLED_ADDR 0b00000001 // 1 byte (bool)
#define DRL_EEPROM_SETTINGS_LIGHTS_ENABLED_ADDR 0b00000010         // 1 byte (bool)

// DRL is a "Daytime running lights".
class DRL
{
public:
  DRL() = delete;
  DRL(InputSwitch *sw, InputSwitch *stopSw, OutputKey *frontKey, OutputKey *backKey);
  void setFrontBlinkingFrequency(Frequency);
  void setBackBlinkingFrequency(Frequency);
  void init();
  void tick(unsigned long int /* micros() */);

private:
  InputSwitch *input, *stopInput;
  OutputKey *outputFront, *outputBack;
  PWM *pwmFront, *pwmBack; // back PWM is pluggable
  Clicker *clicker;
  volatile struct
  {
    bool frontBlinkingEnabled = false;
    bool lightsEnabled = false;
  } settings;

  void readSettings();
  void writeSettings();
};

#endif

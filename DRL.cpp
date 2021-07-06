#include <avr/eeprom.h>
#include "Clicker.h"
#include "DRL.h"
#include "PWM.h"
#include "IO.h"

DRL::DRL(InputSwitch *sw, InputSwitch *stopSw, OutputKey *frontKey, OutputKey *backKey)
{
  input = sw, stopInput = stopSw;
  outputFront = frontKey, outputBack = backKey;

  pwmFront = new PWM();
  pwmFront->setFrequency(VERY_VERY_FAST);

  pwmBack = new PWM();
  pwmBack->setFrequency(FAST_SMALL_DELAY);

  clicker = new Clicker(stopInput);
}

void DRL::setFrontBlinkingFrequency(Frequency f)
{
  pwmFront->setFrequency(f);
}

void DRL::setBackBlinkingFrequency(Frequency f)
{
  pwmBack->setFrequency(f);
}

void DRL::init()
{
  readSettings();
}

/// Do the main stop signal logic here.
void DRL::tick(unsigned long int currentTimeMicros)
{
  clicker->tick(currentTimeMicros);

  switch (clicker->count())
  {
  case 3:
    clicker->reset();
    settings.frontBlinkingEnabled = !settings.frontBlinkingEnabled;
    writeSettings();
    break;

  case 5:
    clicker->reset();
    settings.lightsEnabled = !settings.lightsEnabled;
    writeSettings();
    break;
  }

  if ((input->isOn() || settings.lightsEnabled) && settings.frontBlinkingEnabled)
  {
    switch (pwmFront->tick(currentTimeMicros))
    {
    case PWM_HIGH:
      outputFront->open();
      break;

    case PWM_LOW:
      outputFront->close();
      break;

    case PWM_NONE:
      break;
    }
  }
  else
  {
    (input->isOn() || settings.lightsEnabled) ? outputFront->open() : outputFront->close();

    pwmFront->reset();
  }

  if (stopInput->isOn()) // stop signal button is pressed?
  {
    switch (pwmBack->tick(currentTimeMicros)) // use PWM for back light blinking
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
  else // just enable or disable back lightnings
  {
    (input->isOn() || settings.lightsEnabled) ? outputBack->open() : outputBack->close();

    pwmBack->reset();
  }
}

void DRL::readSettings()
{
  // For booleans: 255 = false, any another = true
  settings.frontBlinkingEnabled = eeprom_read_byte((const uint8_t *)DRL_EEPROM_SETTINGS_FRONT_BLINKING_ENABLED_ADDR) != 255;
  settings.lightsEnabled = eeprom_read_byte((const uint8_t *)DRL_EEPROM_SETTINGS_LIGHTS_ENABLED_ADDR) != 255;
}

void DRL::writeSettings()
{
  eeprom_update_byte((uint8_t *)DRL_EEPROM_SETTINGS_FRONT_BLINKING_ENABLED_ADDR, settings.frontBlinkingEnabled ? 1 : 255);
  eeprom_update_byte((uint8_t *)DRL_EEPROM_SETTINGS_LIGHTS_ENABLED_ADDR, settings.lightsEnabled ? 1 : 255);
}

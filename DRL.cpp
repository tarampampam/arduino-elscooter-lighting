
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

  if (clicker->count() == 3)
  {
    clicker->reset();
    settings.frontBlinkingEnabled = !settings.frontBlinkingEnabled;
    writeSettings();
  }

  if (input->isOn() && settings.frontBlinkingEnabled)
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
    input->isOn() ? outputFront->open() : outputFront->close();

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
    input->isOn() ? outputBack->open() : outputBack->close();

    pwmBack->reset();
  }
}

void DRL::readSettings()
{
  settings.frontBlinkingEnabled = eeprom_read_byte((const uint8_t *)DRL_EEPROM_SETTINGS_FRONT_BLINKING_ENABLED_ADDR) != 255; // 255 = false, any another = true
}

void DRL::writeSettings()
{
  eeprom_write_byte((uint8_t *)DRL_EEPROM_SETTINGS_FRONT_BLINKING_ENABLED_ADDR, settings.frontBlinkingEnabled ? 1 : 255);
}

#include "DRL.h"
#include "PWM.h"
#include "IO.h"

DRL::DRL(InputSwitch *sw, OutputKey *frontKey, OutputKey *backKey)
{
  input = sw;
  outputFront = frontKey, outputBack = backKey;

  pwm = new PWM(300, 200);
}

void DRL::setBlinkingInterval(unsigned long int on, unsigned long int off)
{
  pwm->setPeriodTime(on + off);
  pwm->setImpulseTime(off);
}

/// Do the main stop signal logic here.
void DRL::tick(unsigned long int currentTimeMicros)
{
  if (input->isOn())
  {
    outputFront->open();
    outputBack->open();
  }
  else
  {
    outputFront->close();
    outputBack->close();
    // pwm->reset();
  }
}

// /// Do the main turning lights logic here.
// void DRL::tick()
// {
//   bool switchState = switchIsOn();

//   // FRONT LIGHT LOGIC
//   if (switchIsOn())
//   {
//     digitalWrite(frontLightPin, HIGH);
//   }
//   else
//   {
//     digitalWrite(frontLightPin, LOW);
//   }

//   // BACK LIGHT LOGIC
//   // if the stop signal pin is defined
//   if (stopSignalButtonPin != DRL::UNUSED_PIN)
//   {
//     // if the stop signal button is pressed
//     if (stopSignalButtonIsPressed())
//     {
//       // do the timer logic
//       uint32_t currentTimeMs = millis();

//       if (currentTimeMs >= timers.enableLightAt)
//       {
//         timers.enableLightAt = currentTimeMs + powerOnTime + blinkingInterval;
//         timers.disableLightAt = currentTimeMs + powerOnTime;

//         digitalWrite(backLightPin, HIGH);
//       }
//       else if (currentTimeMs >= timers.disableLightAt)
//       {
//         digitalWrite(backLightPin, LOW);
//       }
//     }
//     else // the stop signal button is unpressed
//     {
//       if (switchIsOn())
//       {
//         digitalWrite(backLightPin, HIGH);
//       }
//       else
//       {
//         digitalWrite(backLightPin, LOW);
//       }

//       // reset timers state
//       if (timers.enableLightAt != 0 || timers.disableLightAt != 0)
//       {
//         timers.enableLightAt = 0;
//         timers.disableLightAt = 0;
//       }
//     }
//   }
//   else
//   {
//     // the stop signal button pin is not defined - do simple
//     if (switchIsOn())
//     {
//       digitalWrite(backLightPin, HIGH);
//     }
//     else
//     {
//       digitalWrite(backLightPin, LOW);
//     }
//   }
// }

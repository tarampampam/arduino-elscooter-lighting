#include "Clicker.h"

Clicker::Clicker(InputSwitch *in)
{
  input = in;
}

unsigned short int Clicker::count()
{
  return clicks;
}

void Clicker::reset()
{
  clicks = 0;
}

void Clicker::tick(unsigned long int currentTimeMicros)
{
  if (input->isOn())
  {
    lastClickAt = currentTimeMicros;

    return;
  }

  if (input->isOff() && lastClickAt != 0 && currentTimeMicros >= lastClickAt + filterBetweenClicksMicros) // button was released
  {
    clicksbuf++;
    lastClickAt = 0;
    completeClicksCollectingAt = currentTimeMicros + filterBetweenClicksMicros * 3;

    return;
  }

  if (completeClicksCollectingAt != 0 && currentTimeMicros >= completeClicksCollectingAt)
  {
    clicks = clicksbuf;
    clicksbuf = 0;
    completeClicksCollectingAt = 0;
  }
}

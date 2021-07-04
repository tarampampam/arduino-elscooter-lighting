#ifndef Clicker_h
#define Clicker_h
#include "IO.h"

class Clicker
{
public:
  Clicker() = delete;
  Clicker(InputSwitch *in);
  unsigned short int count();
  void reset();
  void tick(unsigned long int /* micros() */);

private:
  InputSwitch *input;
  static const unsigned long int filterBetweenClicksMicros = 160000;
  unsigned long int lastClickAt, completeClicksCollectingAt;
  unsigned short int clicks, clicksbuf;
};

#endif

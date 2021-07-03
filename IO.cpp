#include "IO.h"
#include "Arduino.h"

InputSwitch::InputSwitch(unsigned short int p)
{
  pinNumber = p;
}

void InputSwitch::init()
{
  if (!inited)
  {
    pinMode(pinNumber, INPUT);
    inited = true;
  }
}

bool InputSwitch::isOn()
{
  init();

  return digitalRead(pinNumber) == LOW;
}

bool InputSwitch::isOff()
{
  return !isOn();
}

unsigned short int InputSwitch::pin()
{
  return pinNumber;
}

OutputKey::OutputKey(unsigned short int p)
{
  pinNumber = p;
}

void OutputKey::init()
{
  if (!inited)
  {
    pinMode(pinNumber, OUTPUT);
    inited = true;
  }
}

void OutputKey::open()
{
  init();

  digitalWrite(pinNumber, HIGH);
}

void OutputKey::close()
{
  init();

  digitalWrite(pinNumber, LOW);
}

unsigned short int OutputKey::pin()
{
  return pinNumber;
}

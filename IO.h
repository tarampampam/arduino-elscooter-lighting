#ifndef IO_h
#define IO_h

class InputSwitch
{
public:
  InputSwitch() = delete;
  InputSwitch(unsigned short int);
  void init();
  bool isOn();
  bool isOff();

private:
  bool inited = false;
  unsigned short int pinNumber;
};

class OutputKey
{
public:
  OutputKey() = delete;
  OutputKey(unsigned short int);
  void init();
  void open();
  void close();

private:
  bool inited = false;
  unsigned short int pinNumber;
};

#endif

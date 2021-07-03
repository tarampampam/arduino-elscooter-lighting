#ifndef PWM_h
#define PWM_h

/**
 *
 * PWM modulation glossary:
 *
 *    /-----\               /-----\               /-----\      <-- high signal (PWM_HIGH)
 *    |     |               |     |               |     |
 *    |     |               |     |               |     |
 *    |     |               |     |               |     |
 * ---/     \---------------/     \---------------/     \---   <-- low signal (PWM_LOW)
 *
 *    ^---------------------^ -- period
 *    ^-----^ -- impulse
 */

enum Signal
{
  PWM_NONE,
  PWM_HIGH,
  PWM_LOW
};

class PWM
{
public:
  PWM(unsigned int period, unsigned int impulse);
  void setPeriodTime(unsigned int);
  void setImpulseTime(unsigned int);
  Signal tick(unsigned long currentTimeMs /* millis() */);
  void reset();
  void start();
  void stop();
  bool isStarted();

private:
  bool started = true;
  unsigned int period = 1000, impulse = 500; // the period always must be greater than impulse
  unsigned long highSignalAt = 0, lowSignalAt = 0;
};

#endif

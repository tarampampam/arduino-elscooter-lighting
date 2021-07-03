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

enum Frequency // sugar for easy period/impulse management
{
  ALWAYS,
  VERY_SLOW,
  SLOW,
  NORMAL,
  FAST,
  FAST_SMALL_DELAY,
  VERY_FAST,
  VERY_VERY_FAST,
  NEVER
};

class PWM
{
public:
  PWM();
  PWM(unsigned long int period, unsigned long int impulse);
  void setPeriodTime(unsigned long int);
  void setImpulseTime(unsigned long int);
  void setFrequency(Frequency);
  Signal tick(unsigned long int /* micros() */);
  void reset();
  void start();
  void stop();
  bool isStarted();

private:
  bool started = true;
  unsigned long int period = 1000000, impulse = 500000; // the period always must be greater than impulse
  unsigned long int highSignalAt = 0, lowSignalAt = 0;
};

#endif

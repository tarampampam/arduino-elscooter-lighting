#ifndef StopSignal_h
#define StopSignal_h

class StopSignal
{
public:
  StopSignal() = delete; // disable default constructor

  // Create new StopSignal instance.
  StopSignal(
      uint8_t bPin /* button pin (in) */,
      uint8_t lPin /* light pin (out) */
  )
  {
    lightPin = lPin;
    buttonPin = bPin;
  };

  // Make initialization.
  void init();

  // Call this function in the main loop.
  void tick();

  // Get button state.
  bool buttonIsPressed();

  // Timeout defaults.
  static const uint16_t DEFAULT_POWER_ON_TIME = 150, DEFAULT_BLINKING_INTERVAL = 100;

  // How long stop signal must be on.
  uint16_t powerOnTime = DEFAULT_POWER_ON_TIME;

  // Delay between stop signal blinks.
  uint16_t blinkingInterval = DEFAULT_BLINKING_INTERVAL;

private:
  // Button and light pins.
  uint8_t buttonPin, lightPin;

  // Timer states.
  struct
  {
    uint32_t enableLightAt, disableLightAt;
  } timers;
};

#endif

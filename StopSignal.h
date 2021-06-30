#ifndef StopSignal_h
#define StopSignal_h

class StopSignal
{
public:
  StopSignal() = delete; // disable default constructor

  // Create new StopSignal instance.
  StopSignal(
      uint8_t bPin /* button bin (in) */,
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

  // How long stop signal must be on.
  uint16_t powerOnTime = 150;

  // Delay between stop signal blinks.
  uint16_t blinkingInterval = 100;

private:
  // Button and light pins.
  uint8_t buttonPin, lightPin;

  // Get button state.
  bool buttonIsPressed();
};

#endif

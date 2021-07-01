#ifndef TurningLights_h
#define TurningLights_h

class TurningLights
{
public:
  TurningLights() = delete; // disable default constructor

  // Create new TurningLights instance.
  TurningLights(
      uint8_t lbPin /* left button bin (in) */,
      uint8_t rbPin /* right button pin (in) */,
      uint8_t llPin /* left light pin (out) */,
      uint8_t rlPin /* right light pin (out) */
  )
  {
    leftLightPin = llPin;
    rightLightPin = rlPin;

    leftButtonPin = lbPin;
    rightButtonPin = rbPin;
  };

  // Make initialization.
  void init();

  // Call this function in the main loop.
  void tick();

  // Get left turning button state.
  bool leftButtonIsPressed();

  // Get right turning button state.
  bool rightButtonIsPressed();

  // How long turning signal must be on.
  uint16_t powerOnTime = 500;

  // Delay between turning signals.
  uint16_t blinkingInterval = 400;

private:
  // Button and light pins.
  uint8_t leftButtonPin, rightButtonPin;
  uint8_t leftLightPin, rightLightPin;

  // Timer states.
  struct
  {
    uint32_t enableLightAt, disableLightAt;
  } timers;
};

#endif

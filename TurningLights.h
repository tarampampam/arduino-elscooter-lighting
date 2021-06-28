#ifndef TurningLights_h
#define TurningLights_h

class TurningLights
{
public:
  // Create new TurningLights instance.
  TurningLights(
      uint8_t /* left button bin (in) */,
      uint8_t /* right button pin (in) */,
      uint8_t /* left light pin (out) */,
      uint8_t /* right light pin (out) */
  );

  // Call this function in the main loop.
  void tick();

  // Debug mode state.
  bool debugModeEnabled;

  // How long turning signal must be on.
  uint16_t powerOnTime = 500;

  // Delay between turning signals.
  uint16_t blinkingInterval = 400;

private:
  // Button and light pins.
  uint8_t leftButtonPin, rightButtonPin;
  uint8_t leftLightPin, rightLightPin;

  // Buttons state.
  bool leftButtonIsOn, rightButtonIsOn;

  // Internal timer states.
  uint32_t enableLightAt, disableLightAt;

  // Update turning buttons state.
  void updateButtonsState();
};

#endif

// #include <Arduino.h>

// #ifndef DRL_h
// #define DRL_h

// #include "StopSignal.h"

// class DRL
// {
// public:
//   DRL() = delete;

//   DRL(
//       uint8_t swPin /* switcher pin (in) */,
//       uint8_t fPin /* front pin (out) */,
//       uint8_t bPin /* back pin (out) */,
//       uint8_t stopBtnPin = UNUSED_PIN /* stop signal button pin (in); if defined - on stop btn pressing back DRL light will blinks */
//   )
//   {
//     switchPin = swPin;
//     frontLightPin = fPin;
//     backLightPin = bPin;

//     if (stopBtnPin != UNUSED_PIN)
//     {
//       stopSignalButtonPin = stopBtnPin;
//     }
//   };

//   // Make initialization.
//   void init();

//   // Call this function in the main loop.
//   void tick();

//   // Get switch state.
//   bool switchIsOn();

//   // How long stop signal must be on.
//   uint16_t powerOnTime = StopSignal::DEFAULT_POWER_ON_TIME;

//   // Delay between stop signal blinks.
//   uint16_t blinkingInterval = StopSignal::DEFAULT_BLINKING_INTERVAL;

// private:
//   static const uint8_t UNUSED_PIN = 0;

//   // Switcher, button and light pins.
//   uint8_t switchPin, stopSignalButtonPin, frontLightPin, backLightPin;

//   // Get stop signal button state,
//   bool stopSignalButtonIsPressed();

//   // Timer states.
//   struct
//   {
//     uint32_t enableLightAt, disableLightAt;
//   } timers;
// };

// #endif

#ifndef _H_CONFIG
#define _H_CONFIG
#include <Arduino.h>

#if defined(ARDUINO_ARCH_AVR) || defined(__AVR__)
#define ANALOG_MAX 1023
#elif defined(ARDUINO_ARCH_SAMD)
#define ANALOG_MAX 4095
#else
#error "ANALOG_MAX: Unsupported board"
#endif

// Pin that controls whether Arduino should act as a USB HID device.
// In order to reflash a board, disconnect the pin from the ground.
#define PIN_KBD_JUMPER PIN2

// Pin that toggles space key press send sequence to on or off.
#define PIN_BHOP_TOGGLE PIN3

// Pin to indicate bunny hop keypress event through LED (optional).
#define PIN_STATUS_LED PIN7

// Controls how long space button should remain pressed.
// Ideal value is be between 5-20 milliseconds.
#define BHOP_KEYPRESS_DURATION_MS 15

// Pin for a potentiometer to control jump key press interval.
// Optional.
#define PIN_BHOP_INTERVAL_CTRL A0

// Default interval for keypress events.
// Used if PIN_BHOP_INTERVAL_CTRL is not defined.
#define BHOP_DEFAULT_INTERVAL_MS 100

// Minimal and maximal interval ranges.
// Have effect only if PIN_BHOP_INTERVAL_CTRL is defined.
#define BHOP_INTERVAL_MIN 50
#define BHOP_INTERVAL_MAX 1000

#endif

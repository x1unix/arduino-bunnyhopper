#include <Arduino.h>
#include "toggle.h"
#include "config.h"

#define BHOP_TOGGLE_DEBOUNCE 5

namespace bhop::toggle {
  static volatile int g_updatedAt = 0;
  static volatile bool g_isChanged = false;
  static volatile bool g_isEnabled = false;

  static void (*g_onChange)() = nullptr;

  void onToggleButtonPressed() {
    // Split change detection and flag update
    // to avoid switch bounce on key release.
    g_updatedAt = millis(); 
    g_isChanged = true;
  }

  void detectChanges() {
    if (!g_isChanged) {
      return;
    }

    // Skip ghost interrupt events on key release caused by bouncing.
    int val = digitalRead(PIN_BHOP_TOGGLE);
    if (val == LOW) {
      g_isChanged = false;
      return;
    }

    int now = millis();
    if (now - g_updatedAt >= BHOP_TOGGLE_DEBOUNCE) {
      if (g_onChange != nullptr) {
        g_onChange();
      }

      g_isChanged = false;
      g_isEnabled = !g_isEnabled;
    }
  }

  bool isEnabled() {
    detectChanges();
    return g_isEnabled;
  }

  void onChange(void (*handler)()) {
    g_onChange = handler;
  }

  bool setup() {
    g_updatedAt = millis();
    pinMode(PIN_BHOP_TOGGLE, INPUT_PULLUP);
    int interrupt = digitalPinToInterrupt(PIN_BHOP_TOGGLE);
    if (interrupt == NOT_AN_INTERRUPT) {
      return false;
    }

    attachInterrupt(interrupt, onToggleButtonPressed, RISING);
    return true;
  }
}

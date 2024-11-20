#include <Arduino.h>
#include "config.h"
#include "timer.h"

namespace bhop::timer {
static int g_previousMillis = 0;

bool ticked() {
  if (g_previousMillis == 0) {
    g_previousMillis = millis();
    return true;
  }

  int delay = getInterval();
  int delta = millis() - g_previousMillis;
  // Serial.print("delay:");
  // Serial.print(delay);
  // Serial.print(" delta:");
  // Serial.println(delta);
  bool ok = delta >= delay;
  if (ok) {
    g_previousMillis = millis();
  }

  return ok;
}

void reset() {
  g_previousMillis = 0;
}

#ifdef PIN_BHOP_INTERVAL_CTRL
static int g_prevCtrlPinValue = 0;
static int g_bhopDelay = BHOP_DEFAULT_INTERVAL_MS;

int getInterval() {
  int pinValue = analogRead(PIN_BHOP_INTERVAL_CTRL);
  if (pinValue == g_prevCtrlPinValue) {
    return g_bhopDelay;
  }

  g_prevCtrlPinValue = pinValue;
  pinValue = analogRead(PIN_BHOP_INTERVAL_CTRL);
  g_bhopDelay = map(pinValue, 0, ANALOG_MAX, BHOP_INTERVAL_MIN, BHOP_INTERVAL_MAX);
  return g_bhopDelay;
}

void setup() {
  pinMode(PIN_BHOP_INTERVAL_CTRL, INPUT_PULLUP);
}

#else
void setup() {}

int getInterval() {
  return BHOP_DEFAULT_INTERVAL_MS;
}
#endif
}

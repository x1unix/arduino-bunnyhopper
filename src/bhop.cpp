#include <Arduino.h>
#include "bhop.h"

namespace bhop {
enum BoardState {
  Disabled,
  Enabled,
  Error
};

static BoardState g_boardStatus = BoardState::Disabled;

bool isBoardDisabled() {
  pinMode(PIN_KBD_JUMPER, INPUT_PULLUP);
  int val = digitalRead(PIN_KBD_JUMPER);
  return val == HIGH;
}

bool hasError() {
  return g_boardStatus == BoardState::Error;
}

bool setup() {
  pinMode(PIN_STATUS_LED, OUTPUT);
  if (isBoardDisabled()) {
    g_boardStatus = BoardState::Disabled;
    digitalWrite(PIN_STATUS_LED, HIGH);
    return false;
  }

  timer::setup();
  toggle::onChange([]() {
    timer::reset();
    setLedStatus(LOW);
  });

  if (!toggle::setup()) {
    g_boardStatus = BoardState::Error;
    return false;
  }

  setLedStatus(LOW);
  g_boardStatus = BoardState::Enabled;
  return true;
}

bool tick() {
  switch (g_boardStatus) {
    case BoardState::Enabled:
      return toggle::isEnabled() && timer::ticked();
    case BoardState::Disabled:
      return false;
    case BoardState::Error:
      // Blink to notify about wiring error.
      digitalWrite(PIN_STATUS_LED, HIGH);
      delay(100);
      digitalWrite(PIN_STATUS_LED, LOW);
      return false;
  }

  return true;
}

void setLedStatus(uint8_t val) {
  digitalWrite(PIN_STATUS_LED, val);
}
}

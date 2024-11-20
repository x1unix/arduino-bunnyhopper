#include <Arduino.h>
#include <Keyboard.h>
#include "bhop.h"

bool g_isDisabled = false;
bool g_val = false;



volatile int g_delta = 0;
int g_prevDelta = 0;
int g_prevMillis = 0;

void onKeyPress() {
  g_prevDelta = g_delta;
  g_delta++;
}

void setup() {
  if (bhop::setup()) {
    Keyboard.begin();
    return;
  }
  
  Serial.begin(9600);
  delay(1000);

  if (bhop::hasError()) {
    Serial.println(F("Error: can't initialize, wiring issue?"));
  } else {
    Serial.println(F("== Recovery mode =="));
  }
}

void loop() {
  if (bhop::tick()) {
    bhop::setLedStatus(HIGH);
    Keyboard.press(' ');
    delay(BHOP_KEYPRESS_DURATION_MS);
    Keyboard.release(' ');
    bhop::setLedStatus(LOW);
  }
}

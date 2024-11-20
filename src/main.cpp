#include <Arduino.h>
#include "HID-Project.h"
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
  Serial.begin(9600);
  delay(1000);

  if (!bhop::setup()) {
    if (bhop::hasError()) {
      Serial.println("Error: can't initialize, wiring issue?");
    } else {
      Serial.println("== Recovery mode ==");
    }

    return;
  }

  // Keyboard.begin();
}

void loop() {
  if (bhop::tick()) {
    bhop::setLedStatus(HIGH);
    delay(50);
    bhop::setLedStatus(LOW);
  }
}

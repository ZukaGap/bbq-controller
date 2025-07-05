#include <Arduino.h>
#include "constants.h"

extern bool fanState;         // Tell the compiler it's defined elsewhere
extern bool fanManualControl; // Manual fan control flag

void setupFan() {
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);
}

bool isFanOn() {
  return fanState;
}

void controlFan(float temperature) {
  // If manual control is OFF, force fan OFF regardless of temperature
  if (!fanManualControl) {
    if (fanState) {
      digitalWrite(FAN_PIN, LOW);
      fanState = false;
    }
    return;
  }
  
  // Manual control is ON - use temperature-based logic
  // Fan turns ON when temperature is BELOW FAN_ON_TEMP (200°C)
  // Fan turns OFF when temperature is ABOVE FAN_OFF_TEMP (350°C)
  
  if (temperature < FAN_ON_TEMP && !fanState) {
    digitalWrite(FAN_PIN, HIGH);
    fanState = true;
  } else if (temperature >= FAN_OFF_TEMP && fanState) {
    digitalWrite(FAN_PIN, LOW);
    fanState = false;
  }
}
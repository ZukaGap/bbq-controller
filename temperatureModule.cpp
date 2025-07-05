#include <max6675.h>
#include "constants.h"

MAX6675 thermocouple(PIN_SCK, PIN_CS, PIN_SO);

void setupTemperature() {
  // Ready on startup
}

float readTemperature() {
  return thermocouple.readCelsius();
}

#ifndef CONSTANTS_H
#define CONSTANTS_H

// MAX6675 Pins
#define PIN_SO 19
#define PIN_CS 20
#define PIN_SCK 3

// LCD Config
#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 20
#define LCD_ROWS 4

// Fan Control
#define FAN_PIN 15
#define FAN_ON_TEMP 200.0
#define FAN_OFF_TEMP 350.0

// Other
#define TEMP_READ_INTERVAL 20000  // 20 seconds

#endif

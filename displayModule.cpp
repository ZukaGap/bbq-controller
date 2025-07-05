#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "constants.h"

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

void setupDisplay() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("System Starting...");
}

void updateWiFiStatus(bool connected) {
  lcd.setCursor(0, 0);
  lcd.print("WiFi: ");
  lcd.print(connected ? "Connected   " : "Connecting...");
}

void showDeviceIP(String ipAddress) {
  lcd.setCursor(0, 1);
  lcd.print("Open:");
  lcd.setCursor(0, 2);
  lcd.print(ipAddress);
}

void updateFanStatus(bool fanOn) {
  lcd.setCursor(0, 3);
  lcd.print("Fan: ");
  lcd.print(fanOn ? "ON " : "OFF");
}

void updateTemperature(float temperature) {
  lcd.setCursor(10, 3);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C ");
}

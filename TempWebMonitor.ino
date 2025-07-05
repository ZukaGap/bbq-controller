#include <WiFi.h>
#include "secrets.h"
#include "constants.h"
#include "temperatureModule.h"
#include "fanController.h"
#include "displayModule.h"
#include "webServerModule.h"

float currentTemp = 0.0;
bool fanState = false;
bool fanManualControl = false;  // NEW: Manual fan control flag - starts as OFF
unsigned long lastTempRead = 0;

void setup() {
  Serial.begin(115200);

  setupDisplay();
  updateWiFiStatus(false);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting to WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
  updateWiFiStatus(true);

  String deviceIP = "http://" + WiFi.localIP().toString();
  Serial.println("Access ESP32 at: " + deviceIP);
  showDeviceIP(deviceIP);

  setupTemperature();
  setupFan();
  setupWebServer();
  
  // Initialize manual control to OFF (fan disabled by default)
  fanManualControl = false;
  Serial.println("Fan manual control initialized to OFF");
}

void loop() {
  if (millis() - lastTempRead >= TEMP_READ_INTERVAL) {
    lastTempRead = millis();

    currentTemp = readTemperature();
    updateTemperature(currentTemp);

    controlFan(currentTemp);
    updateFanStatus(isFanOn());
    
    // Debug output to Serial Monitor
    Serial.print("Temp: ");
    Serial.print(currentTemp);
    Serial.print("°C, Fan: ");
    Serial.print(fanState ? "ON" : "OFF");
    Serial.print(", Manual Control: ");
    Serial.println(fanManualControl ? "ENABLED" : "DISABLED");
  }

  server.handleClient();
}
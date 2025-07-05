#ifndef DISPLAY_MODULE_H
#define DISPLAY_MODULE_H

void setupDisplay();
void updateWiFiStatus(bool connected);
void updateFanStatus(bool fanOn);
void updateTemperature(float temperature);
void showDeviceIP(String ipAddress);

#endif

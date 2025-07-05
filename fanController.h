#ifndef FAN_CONTROLLER_H
#define FAN_CONTROLLER_H

void setupFan();
void controlFan(float temperature);
bool isFanOn();

#endif

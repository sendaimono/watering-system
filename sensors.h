#ifndef SENSORS_H
#define SENSORS_H

const int MOISTURE_IN[] = {A0, A1};
const int MOISTURE_IN_COUNT = sizeof(MOISTURE_IN) / sizeof(MOISTURE_IN[0]);
const int MOISTURE_AirValue[] = {580, 585};
const int MOISTURE_WaterValue[] = {39, 38};
const int PUMPS[] = {7, 8};
volatile int READINGS[] = {0, 0};
volatile long LAST_TIME_SENSORS_READ = 0;
const int MOISTURE_READ_INTERVAL = 30 * 1000;

void readMoisture(unsigned long current_time);
void setupSensors();
bool shouldUpdateSensorValues(unsigned long current_time);

#endif
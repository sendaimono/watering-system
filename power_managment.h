#ifndef POWER_MANAGMENT_H
#define POWER_MANAGMENT_H

#define SENSORS_POWER A1
#define WATERING_POWER A2

struct PowerManagment
{
    void setup();
    void powerUpWatering();
    void powerDownWatering();
    void powerUpSensors();
    void powerDownSensors();
};

PowerManagment Managment;

#endif
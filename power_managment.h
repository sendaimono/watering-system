#ifndef POWER_MANAGMENT_H
#define POWER_MANAGMENT_H

#define SENSORS_POWER 4
#define WATERING_POWER 5

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
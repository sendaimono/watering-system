#ifndef POWER_MANAGMENT_H
#define POWER_MANAGMENT_H
#include <LowPower.h>

struct PowerManagment
{
    void setup();
    // void powerUpWatering();
    // void powerDownWatering();
    void powerUpSensors();
    void powerDownSensors();
    void lowPower(period_t period);
};

PowerManagment Managment;

#endif
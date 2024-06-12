#ifndef POWER_MANAGMENT_H
#define POWER_MANAGMENT_H

#define SENSORS_POWER 4
#define WATERING_POWER A2

struct PowerManagment
{
    void setup();
    void powerUpWatering();
    void powerDownWatering();
    void powerUpSensors();
    void powerDownSensors();
    bool areSensorsOn();
    bool areSensorsPoweringUp();

private:
    unsigned long _powered_sensors_on = 0;
    unsigned long _powered_water_on = 0;
};

PowerManagment Managment;

#endif
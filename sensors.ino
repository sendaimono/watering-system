
#include <stdlib.h>
#include <LowPower.h>
#include "power_managment.h"
#include "sensors.h"

int clamp(int val, int min, int max)
{
    if (val < min)
        return min;
    if (val > max)
        return max;
    return val;
}

int getMoistureInPercent(int sensor_idx)
{
    int max_val = MOISTURE_AirValue[sensor_idx] - MOISTURE_WaterValue[sensor_idx];
    int value = analogRead(MOISTURE_IN[sensor_idx]);
    Serial.print("S");
    Serial.print(sensor_idx);
    Serial.print(": ");
    Serial.print(value);
    int relative_0 = clamp(value - MOISTURE_WaterValue[sensor_idx], 0, max_val);
    float result = ceil((relative_0 * 100.0) / max_val);
    Serial.print(" | ");
    Serial.println(result);
    return 100 - (int)result;
}

// --- Sensors ---

void readMoisture(unsigned long current_time)
{
    Managment.powerUpSensors();
    Managment.lowPower(SLEEP_60MS);
    for (int channel = 0; channel < MOISTURE_IN_COUNT; channel++)
    {
        READINGS[channel] = getMoistureInPercent(channel);
    }
    LAST_TIME_SENSORS_READ = current_time;
    Managment.powerDownSensors();
}

void setupSensors()
{
    for (int channel = 0; channel < MOISTURE_IN_COUNT; channel++)
    {
        pinMode(MOISTURE_IN[channel], INPUT);
    }
}

bool shouldUpdateSensorValues(unsigned long current_time)
{
    if (LAST_TIME_SENSORS_READ == 0)
        return true;
    return current_time - LAST_TIME_SENSORS_READ >= (unsigned long)MOISTURE_READ_INTERVAL;
}
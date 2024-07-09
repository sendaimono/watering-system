#include "sensors.h"
#include "power_managment.h"
#include "pump.h"
#include "sensors.h"

void setupPumps()
{
    // Managment.powerDownWatering();
    for (int channel = 0; channel < MOISTURE_IN_COUNT; ++channel)
    {
        pinMode(PUMPS[channel], OUTPUT);
        digitalWrite(PUMPS[channel], HIGH);
    }
}

void pumpWater(unsigned long current_time)
{
    for (int channel = 0; channel < MOISTURE_IN_COUNT; ++channel)
    {
        int moisture = READINGS[channel];
        int supply = PUMPS[channel];
        Serial.print("Reading for sensor ");
        Serial.print(channel);
        Serial.print(": ");
        Serial.println(moisture);

        if (CURRENT_WATERING_PUMP == -1 && moisture < MINIMUM_START_UP)
        {
            Serial.print("Turn on pump: ");
            Serial.println(supply);
            turnOnPump(current_time, supply);
            return;
        }
        else if (CURRENT_WATERING_PUMP == supply && hasWateringSectionFinished(current_time, moisture))
        {
            Serial.print("Turn off pump: ");
            Serial.println(channel);
            turnOffActivePump();
        }
    }
    // if (CURRENT_WATERING_PUMP == -1)
    // {
    //     Managment.powerDownWatering();
    // }
}

bool hasWateringSectionFinished(unsigned long current_time, int moisture)
{
    if (moisture > MAXIMUM_CUT_OFF)
    {
        return true;
    }
    Serial.print("current_time: ");
    Serial.println(current_time);
    Serial.print("WATERING_STARTED_AT: ");
    Serial.print(WATERING_STARTED_AT);
    Serial.print("result: ");
    Serial.println(current_time - WATERING_STARTED_AT);
    Serial.print("finished: ");
    Serial.println(current_time - WATERING_STARTED_AT > (unsigned int)MAX_WATERING_DURATION);
    return current_time - WATERING_STARTED_AT > (unsigned int)MAX_WATERING_DURATION;
}

void turnOffActivePump()
{
    digitalWrite(WATERING_STARTED_AT, HIGH);
    WATERING_STARTED_AT = 0;
    CURRENT_WATERING_PUMP = -1;
}

void turnOnPump(unsigned long current_time, int section)
{
    // Managment.powerUpWatering();
    CURRENT_WATERING_PUMP = section;
    WATERING_STARTED_AT = current_time;
    digitalWrite(section, LOW);
}

#include "pump.h"

bool Pump::isRunning()
{
    return _is_running;
}

void Pump::turnOn()
{
    Managment.powerUpWatering();
}

void Pump::enableSection(section_n section)
{
    digitalWrite(section, HIGH);
}
void Pump::disableSection(section_n section)
{
    digitalWrite(section, LOW);
}

void Pump::turnOff()
{
    digitalWrite(SECTION_1, LOW);
    Managment.powerDownWatering();
}

bool Watering::shouldStartWatering(Sensors sensors)
{
    if (sensors.moisture_readings == NULL || !sensors.moisture_readings->size)
        return false;
    if (sensors.moisture_readings->values[0] < 30)
        return;
}
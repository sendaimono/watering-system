#include "power_managment.h";

void PowerManagment::setup()
{
    pinMode(SENSORS_POWER, OUTPUT);
    digitalWrite(SENSORS_POWER, LOW);
    pinMode(WATERING_POWER, OUTPUT);
    digitalWrite(WATERING_POWER, LOW);
}
void PowerManagment::powerUpWatering()
{
    digitalWrite(WATERING_POWER, HIGH);
    delay(100);
}

void PowerManagment::powerDownWatering()
{
    digitalWrite(WATERING_POWER, LOW);
}

void PowerManagment::powerUpSensors()
{
    digitalWrite(SENSORS_POWER, HIGH);
    delay(200);
}

void PowerManagment::powerDownSensors()
{
    digitalWrite(SENSORS_POWER, LOW);
}
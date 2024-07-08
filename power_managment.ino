#include "power_managment.h";

unsigned const int SENSOR_POWER_UP_TIME = 5000;

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
    delay(1000);
}

void PowerManagment::powerDownWatering()
{
    digitalWrite(WATERING_POWER, LOW);
}

void PowerManagment::powerUpSensors()
{
    Serial.println("Power up sensors");

    digitalWrite(SENSORS_POWER, HIGH);
}

void PowerManagment::powerDownSensors()
{
    Serial.println("Power down sensors");
    digitalWrite(SENSORS_POWER, LOW);
}
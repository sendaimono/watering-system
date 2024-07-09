#define SENSORS_POWER 4
#define WATERING_POWER 5
#include "power_managment.h"

void PowerManagment::setup()
{
    pinMode(SENSORS_POWER, OUTPUT);
    digitalWrite(SENSORS_POWER, LOW);
    // pinMode(WATERING_POWER, OUTPUT);
    // digitalWrite(WATERING_POWER, LOW);
}
// void PowerManagment::powerUpWatering()
// {
//     Serial.println("Power up pump");
//     digitalWrite(WATERING_POWER, HIGH);
// }

// void PowerManagment::powerDownWatering()
// {
//     Serial.println("Power down pump");
//     digitalWrite(WATERING_POWER, LOW);
// }

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

void PowerManagment::lowPower(period_t period)
{
    LowPower.powerDown(period, ADC_OFF, BOD_ON);
    power_adc_enable();
}

void power_adc_enable()
{
    ADCSRA |= (1 << ADEN);
}
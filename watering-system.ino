#include <LowPower.h>
#include "sensors.h"
#include "bluetooth.h"
#include "lcd.h"
#include "power_managment.h"

#define SWITCH_PIN 2

Sensors sensors;
LCD lcd;

void power_down()
{
    delay(1000);
}

// void power_down()
// {
//     Serial.flush();
//     Bluetooth::flush();
//     LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);

//     Serial.begin(9600);
//     Bluetooth::setup();
// }

void setup()
{
    Serial.begin(9600);
    Bluetooth::setup();
    Serial.println("BT is ready.");
    lcd.setup();
    Serial.println("LCD is ready.");
    attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), wakeUp, RISING);
    Serial.println("Interrupts are ready.");
    sensors.setup();
    Serial.println("Sensors are ready.");
    Managment.setup();
    Serial.println("Power managment is ready.");
    Serial.println("Arduino is ready!");
}

void loop()
{
    unsigned long current_time = millis();

    if (sensors.shouldUpdate(current_time))
    {
        sensors.read();
        auto formatted_readings = sensors.toString();
        Serial.println(formatted_readings);
        Bluetooth::send(formatted_readings);
    }

    if (lcd.isActive())
    {
        if (lcd.shouldPowerDown(current_time))
        {
            lcd.turn_off();
        }
        else
        {
            lcd.displaySensors(sensors);
        }
    }

    power_down();
}

void wakeUp()
{
    lcd.wakeUp();
}
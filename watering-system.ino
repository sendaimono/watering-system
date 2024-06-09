#include <LowPower.h>
#include "sensors.h"
#include "bluetooth.h"
#include "lcd.h"

Sensors sensors;
LCD lcd;

const int switchPin = 2;

void power_down()
{
    delay(1000);
}
// void power_down() {
//   Serial.flush();
//   Bluetooth::flush();
//   LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);

//   Serial.begin(9600);
//   Bluetooth::setup();

// }

void setup()
{
    Serial.begin(9600);
    Bluetooth::setup();
    lcd.setup();
    attachInterrupt(digitalPinToInterrupt(switchPin), wakeUp, RISING);

    Serial.println("Arduino is ready.");
}

void loop()
{
    unsigned long current_time = millis();

    if (sensors.should_update(current_time))
    {
        sensors.read();
        auto formatted_readings = sensors.to_string();
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
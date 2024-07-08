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
    delay(100);
}

void power_down_hard()
{
    Serial.flush();
    Bluetooth::flush();
    LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);

    Serial.begin(9600);
}

void setup()
{
    Serial.begin(9600);
    // Bluetooth::setup();
    // Serial.println("BT is setup.");

    lcd.setup();
    Serial.println("LCD is setup.");

    pinMode(SWITCH_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), wakeUp, FALLING);
    Serial.println("Interrupts are ready.");

    sensors.setup();
    Serial.println("Sensors are ready.");

    Managment.setup();
    Serial.println("Power managment is ready.");

    Serial.println("Arduino is ready!");
}

void handle_lcd(unsigned long current_time)
{
    if (lcd.wokeUp())
    {
        lcd.turn_on();
        lcd.displaySensors(sensors);
    }

    if (lcd.shouldPowerDown(current_time))
    {
        lcd.turn_off();
    }
}

void handle_sensors(unsigned long current_time)
{
    if (sensors.shouldUpdate(current_time))
    {
        auto areUpdated = sensors.read(current_time);
        if (areUpdated)
        {
            if (lcd.isActive())
            {
                lcd.displaySensors(sensors);
            }
            auto formatted_readings = sensors.toString();
            Serial.println(formatted_readings);
        }
    }
}

void loop()
{
    Serial.println("I'm awake");
    unsigned long current_time = millis();
    handle_lcd(current_time);
    handle_sensors(current_time);

    // power_down();
    power_down_hard();
}

void wakeUp()
{
    lcd.wakeUp();
}
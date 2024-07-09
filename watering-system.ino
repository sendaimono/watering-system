#include "sensors.h"
#include "power_managment.h"
#include "pump.h"
#define SWITCH_PIN 2

unsigned long loop_count = 0;

void sleep()
{
    Serial.flush();
    // Bluetooth::flush();
    Managment.lowPower(SLEEP_8S);

    Serial.begin(9600);
    loop_count++;
}

void setup()
{
    Serial.begin(9600);
    // Bluetooth::setup();
    // Serial.println("BT is setup.");

    // lcd.setup();
    // Serial.println("LCD is setup.");

    // pinMode(SWITCH_PIN, INPUT_PULLUP);
    // attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), wakeUp, FALLING);
    // Serial.println("Interrupts are ready.");

    setupPumps();
    Serial.println("Pumps are ready.");

    setupSensors();
    Serial.println("Sensors are ready.");

    Managment.setup();
    Serial.println("Power managment is ready.");

    Serial.println("Arduino is ready!");
}

// void handle_lcd(unsigned long current_time)
// {
//     if (lcd.wokeUp())
//     {
//         lcd.turn_on();
//         lcd.displaySensors(sensors);
//     }

//     if (lcd.shouldPowerDown(current_time))
//     {
//         lcd.turn_off();
//     }
// }

// void handle_sensors(unsigned long current_time)
// {
//     if (sensors.shouldUpdate(current_time))
//     {
//         auto areUpdated = sensors.read(current_time);
//         if (areUpdated)
//         {
//             if (lcd.isActive())
//             {
//                 lcd.displaySensors(sensors);
//             }
//             auto formatted_readings = sensors.toString();
//             Serial.println(formatted_readings);
//         }
//     }
// }

void handleSensors(unsigned long current_time)
{
    if (shouldUpdateSensorValues(current_time))
    {
        Serial.println("Reading sensors...");
        readMoisture(current_time);
    }
}

void loop()
{
    Serial.println("--------------");
    // + 8 second to cope with low power mode;
    unsigned long current_time = millis() + (loop_count * 8000);

    Serial.print("Loop started at: ");
    Serial.println((unsigned long)current_time);

    // handle_lcd(current_time);
    handleSensors(current_time);
    pumpWater(current_time);
    sleep();
}

// void wakeUp()
// {
//     lcd.wakeUp();
// }
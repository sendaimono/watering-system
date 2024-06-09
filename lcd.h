#ifndef LCD_H
#define LCD_H
#include "sensors.h";

struct LCD
{
    void setup();
    void turn_on();
    void turn_off();
    void wakeUp();
    bool isActive();
    bool shouldPowerDown(unsigned int current_time);
    void displaySensors(Sensors sensors);

private:
    bool isLCDPluggedIn();
};

#endif
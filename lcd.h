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
    bool shouldPowerDown(unsigned long current_time);
    void displaySensors(Sensors sensors);
    bool wokeUp();

private:
    bool isLCDPluggedIn();
    bool _enabled;
    bool _should_activate = false;
    bool _is_activated = false;
    volatile unsigned long _display_started_on = 0;
};

#endif
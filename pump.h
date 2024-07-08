#ifndef LCD_H
#define LCD_H
#include "power_managment.h"
#include "sensors.h"

enum section_n
{
    SECTION_1 = 6
};

class Pump
{
    bool _is_running;

public:
    bool isRunning();
    void turnOn();
    void turnOff();
    void enableSection(section_n section);
    void disableSection(section_n section);
};

class Watering
{
    unsigned long _started_on = 0;

public:
    bool shouldStartWatering(Sensors sensors);
    bool startWatering(unsigned long current);
    bool decideIfShouldStop(unsigned long current);
};

Watering WateringSystem;

#endif
#ifndef PUMP_H
#define PUMP_H
#define MINIMUM_START_UP 40
#define MAXIMUM_CUT_OFF 50

bool IS_WATERING = false;
int CURRENT_WATERING_PUMP = -1;
const int MAX_WATERING_DURATION = 30 * 1000;
unsigned long WATERING_STARTED_AT = 0;

void pumpWater(unsigned long current_time);
void setupPumps();

#endif
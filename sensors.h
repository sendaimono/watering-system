#ifndef SENSORS_H
#define SENSORS_H

struct SensorReadings {
    int* values;
    int size;
};

SensorReadings read_sensors();
void setup_sensors();

String format_sensor_reading(SensorReadings readings);

#endif
#ifndef SENSORS_H
#define SENSORS_H

#define MOISTURE_READ_INTERVAL 10000;

struct MoistureSensorReadings
{
    ~MoistureSensorReadings();
    int *values;
    int size = 0;

    String toString();
};

struct DHTSensorReadings
{
    float temperature = 0;
    float humidity = 0;

    String toString();
};

class Sensors
{
public:
    void setup();
    bool shouldUpdate(unsigned int current_time);
    void read();
    String toString();
    MoistureSensorReadings readMoisture();
    DHTSensorReadings readDht();

    MoistureSensorReadings moisture_readings;
    DHTSensorReadings dht_readings;

private:
    unsigned long last_sensor_read_time = 0;
};

#endif
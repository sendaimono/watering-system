#ifndef SENSORS_H
#define SENSORS_H

unsigned const int MOISTURE_READ_INTERVAL = 1000;

struct MoistureSensorReadings
{
    int *values;
    int size;

    MoistureSensorReadings(int s) : size(s)
    {
        values = (int *)malloc(s * sizeof(int));
    };

    ~MoistureSensorReadings();

    String toString(bool);
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
    bool shouldUpdate(unsigned long current_time);
    bool read(unsigned long current_time);
    String toString();
    MoistureSensorReadings *readMoisture();
    DHTSensorReadings *readDht();

    MoistureSensorReadings *moisture_readings;
    DHTSensorReadings *dht_readings;

private:
    unsigned long _last_sensor_read_time = 0;
};

#endif
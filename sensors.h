#ifndef SENSORS_H
#define SENSORS_H

#define MOISTURE_READ_INTERVAL 10000;

struct MoistureSensorReadings
{
    ~MoistureSensorReadings();
    int *values;
    int size = 0;

    String to_string();
};

struct DHTSensorReadings
{
    float temperature = 0;
    float humidity = 0;

    String to_string();
};

class Sensors
{
public:
    bool should_update(unsigned int current_time);
    void read();
    String to_string();
    MoistureSensorReadings read_moisture();
    DHTSensorReadings read_dht();

    MoistureSensorReadings moisture_readings;
    DHTSensorReadings dht_readings;

private:
    unsigned long last_sensor_read_time = 0;
};

#endif
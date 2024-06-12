
#include <stdlib.h>
#include <DHT.h>
#include "sensors.h"
#include "mux.h"
#include "power_managment.h"
#define DHTTYPE DHT22

const int MOISTURE_IN[] = {0, 1, 2};
const int MOISTURE_IN_COUNT = sizeof(MOISTURE_IN) / sizeof(MOISTURE_IN[0]);
const int MOISTURE_AirValue[] = {580, 585, 583};
const int MOISTURE_WaterValue[] = {39, 38, 23};

DHT dht(MUX_SIG_PIN, DHTTYPE);

int clamp(int val, int min, int max)
{
    if (val < min)
        return min;
    if (val > max)
        return max;
    return val;
}

int getMoistureInPercent(int sensor_idx)
{
    int max_val = MOISTURE_AirValue[sensor_idx] - MOISTURE_WaterValue[sensor_idx];
    int value = Mux.readMux(MOISTURE_IN[sensor_idx]);
    Serial.print("S");
    Serial.print(sensor_idx);
    Serial.print(": ");
    Serial.print(value);
    int relative_0 = clamp(value - MOISTURE_WaterValue[sensor_idx], 0, max_val);
    float result = ceil((relative_0 * 100.0) / max_val);
    Serial.print(" | ");
    Serial.println(result);
    return 100 - (int)result;
}

// --- MoistureSensorReadings ---

MoistureSensorReadings::~MoistureSensorReadings()
{
    if (values != nullptr)
    {
        free(values);
    }
    size = 0;
}

String MoistureSensorReadings::toString()
{
    String output = "";
    for (int i = 0; i < size; i++)
    {
        char buffer[20];
        sprintf(buffer, "S%d: %d%%, ", i + 1, values[i]);
        output += buffer;
    }

    if (output.length() > 2)
    {
        output = output.substring(0, output.length() - 2);
    }
    return output;
}

// --- DHTSensorReadings ---

DHTSensorReadings Sensors::readDht()
{
    // Mux.selectChannel(3, INPUT_PULLUP);
    // dht_readings.humidity = dht.readHumidity();
    // dht_readings.temperature = dht.readTemperature();
    // return dht_readings;
}

// --- Sensors ---

MoistureSensorReadings *Sensors::readMoisture()
{
    moisture_readings = new MoistureSensorReadings(MOISTURE_IN_COUNT);
    moisture_readings->size = MOISTURE_IN_COUNT;
    if (moisture_readings->values == NULL)
    {
        // Handle memory allocation failure
        moisture_readings->size = 0;
        return moisture_readings;
    }

    for (int channel = 0; channel < MOISTURE_IN_COUNT; channel++)
    {
        moisture_readings->values[channel] = getMoistureInPercent(channel);
    }
    return moisture_readings;
}

bool Sensors::read()
{
    Managment.powerUpSensors();
    readMoisture();
    // readDht();
    _last_sensor_read_time = millis();
    Managment.powerDownSensors();
    return true;
    // if (sensors_on)
    // {
    //     readMoisture();
    //     // readDht();
    //     _last_sensor_read_time = millis();
    //     Managment.powerDownSensors();
    //     return true;
    // }

    // auto sensors_powering_up = Managment.areSensorsPoweringUp();
    // if (!sensors_on && !sensors_powering_up)
    // {
    //     Managment.powerUpSensors();
    // }
    // return false;
}

void Sensors::setup()
{
    dht.begin();
}

String Sensors::toString()
{
    return moisture_readings->toString();
}

bool Sensors::shouldUpdate(unsigned long current_time)
{
    if (_last_sensor_read_time == 0)
        return true;
    return current_time - _last_sensor_read_time >= MOISTURE_READ_INTERVAL;
}
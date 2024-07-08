
#include <stdlib.h>
#include <DHT.h>
#include <LowPower.h>
#include "sensors.h"
#include "power_managment.h"
#define DHTPIN 11
#define DHTTYPE DHT22

const int MOISTURE_IN[] = {A0, A1, A2};
const int MOISTURE_IN_COUNT = sizeof(MOISTURE_IN) / sizeof(MOISTURE_IN[0]);
const int MOISTURE_AirValue[] = {580, 585, 583};
const int MOISTURE_WaterValue[] = {39, 38, 23};

DHT dht(DHTPIN, DHTTYPE);

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
    int value = analogRead(MOISTURE_IN[sensor_idx]);
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

String MoistureSensorReadings::toString(bool debug)
{
    if (debug)
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
    String result = "";
    for (int i = 0; i < size; i++)
    {
        result += "rH" + String(i + 1) + ": " + String(values[i]) + "%";
        if (i < size - 1)
        {
            result += " | ";
        }
    }
    return result;
}

String DHTSensorReadings::toString()
{
    String output = "";
    output += "Humidity: ";
    output += humidity;
    output += " % ";
    output += "Temp: ";
    output += temperature;
    output += " *C";
    return output;
}

// --- DHTSensorReadings ---

DHTSensorReadings *Sensors::readDht()
{
    if (dht_readings != NULL)
        free(dht_readings);
    dht_readings = new DHTSensorReadings();
    dht_readings->humidity = dht.readHumidity();
    dht_readings->temperature = dht.readTemperature();
    return dht_readings;
}

// --- Sensors ---

MoistureSensorReadings *Sensors::readMoisture()
{
    if (moisture_readings != NULL)
        free(moisture_readings);
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

bool Sensors::read(unsigned long current_time)
{
    Managment.powerUpSensors();
    LowPower.powerDown(SLEEP_120MS, ADC_OFF, BOD_OFF);
    readMoisture();
    readDht();
    _last_sensor_read_time = current_time;
    Managment.powerDownSensors();
    return true;
}

void Sensors::setup()
{
    dht.begin();
}

String Sensors::toString()
{
    Serial.print(dht_readings->toString());
    return moisture_readings->toString(true);
}

bool Sensors::shouldUpdate(unsigned long current_time)
{
    if (_last_sensor_read_time == 0)
        return true;
    Serial.print(current_time);
    Serial.print(" - ");
    Serial.print(_last_sensor_read_time);
    Serial.print(" = ");
    Serial.println(current_time - _last_sensor_read_time);
    return current_time - _last_sensor_read_time >= MOISTURE_READ_INTERVAL;
}
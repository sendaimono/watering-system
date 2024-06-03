
#include <stdlib.h> 

const int MOISTURE_IN[] = {A0, A1, A2};
const int MOISTURE_IN_COUNT = sizeof(MOISTURE_IN) / sizeof(MOISTURE_IN[0]);
const int SWITCHES[] = {2,3,4};
bool connectionStatus[] = {true, true, true}; 

int clamp(int val, int min, int max) {
  if (val < min) return min;
  if (val > max) return max;
  return val;
}

int getMoistureInPercent(int PIN) {
  return clamp(analogRead(PIN), 0, 800) / 8;
}

void setup_sensors() {
  for (int i = 0; i < MOISTURE_IN_COUNT; i++) {
    pinMode(MOISTURE_IN[i], INPUT);
    pinMode(SWITCHES[i], OUTPUT);
  }
}

SensorReadings read_sensors() {
  SensorReadings readings;
  readings.size = MOISTURE_IN_COUNT;
  readings.values = (int*)malloc(readings.size * sizeof(int));
  if (readings.values == NULL) {
        // Handle memory allocation failure
        readings.size = 0;
        return readings;
  }


  for (int i = 0; i < MOISTURE_IN_COUNT; i++) {
    readings.values[i] = getMoistureInPercent(MOISTURE_IN[i]);
  }
  return readings;
}

String format_sensor_reading(SensorReadings readings) {
  String output = "";
  for (int i = 0; i < readings.size; i++) {
    char buffer[20];
    sprintf(buffer, "S%d: %d%% | ", i+1, readings.values[i]);
    output += buffer;
  }

  if (output.length() > 2) {
        output = output.substring(0, output.length() - 3);
    }
  return output;
}
#include "sensors.h"
#include "bluetooth.h"


void setup() {
  Serial.begin(9600);
  setup_bluetooth();
  Serial.println("Arduino is ready.");
}

void loop() {
  // Wysyłanie danych do serial monitor oraz przez Bluetooth
  auto readings = read_sensors();
  auto formatted_readings = format_sensor_reading(readings);
  Serial.println(formatted_readings);
  send_BT_msg(formatted_readings);
  

  free(readings.values);
  // Czekanie 1 sekundę przed wysłaniem kolejnej wiadomości
  delay(1000);
}

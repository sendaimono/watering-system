#include <SoftwareSerial.h>
SoftwareSerial bluetooth(10, 11); // RX, TX

int is_BT_connected = false;

void send_BT_msg(String msg) {
  // Serial.print("Sending BT message: ");
  // Serial.println(msg);
  bluetooth.println(msg);
}

void send_AT_cmd(String cmd) {
  // Serial.print("Sending command: ");
  // Serial.println(cmd);
  send_BT_msg(cmd);
  delay(1000);
  while (bluetooth.available()) {
    Serial.write(bluetooth.read());
  }
}

void setup_bluetooth() {
  bluetooth.begin(9600);
  delay(1000);
  // send_BT_msg("AT");
  // delay(5000);
  // int available = bluetooth.available();
  // Serial.println(available);
  // if (!bluetooth.available()) {
  //   Serial.println("Module is not responding.");
  //   return;
  // }
  // is_BT_connected = true;
  // Serial.println("Module is responding to AT commands.");

  // send_AT_cmd("AT+NAME=mkp_v1");
  // send_AT_cmd("AT+PIN=9871"); // Set PIN code
}
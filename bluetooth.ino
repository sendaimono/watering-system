#include <SoftwareSerial.h>
#include "bluetooth.h";

SoftwareSerial bluetooth(10, 11); // RX, TX

int is_BT_connected = false;

void Bluetooth::send(String msg)
{
    // Serial.print("Sending BT message: ");
    // Serial.println(msg);
    bluetooth.println(msg);
}

void Bluetooth::setup()
{
    bluetooth.begin(9600);
    delay(1000);
}

void Bluetooth::flush()
{
    bluetooth.flush();
    delay(1000);
}
#ifndef BLUETOOTH_H
#define BLUETOOTH_H

class Bluetooth
{
public:
    static void setup();
    static void flush();
    static void send(String msg);
};

#endif
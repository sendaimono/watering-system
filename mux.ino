#include "mux.h";

void MUX::selectChannel(int channel)
{
    digitalWrite(MUX_1, channel & 0x01);
    digitalWrite(MUX_2, (channel >> 1) & 0x01);
    digitalWrite(MUX_3, (channel >> 2) & 0x01);
    digitalWrite(MUX_4, (channel >> 3) & 0x01);
    pinMode(MUX_SIG_PIN, INPUT);
}

int MUX::readMux(int channel)
{
    selectChannel(channel);
    delay(10);
    return analogRead(MUX_SIG_PIN);
}
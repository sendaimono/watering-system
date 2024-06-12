#include "mux.h";

void MUX::_selectChannel(int channel)
{
    Serial.print("Switch to sensor:");
    Serial.println(channel);
    digitalWrite(MUX_1, channel & 0x01);
    digitalWrite(MUX_2, (channel >> 1) & 0x01);
    digitalWrite(MUX_3, (channel >> 2) & 0x01);
    digitalWrite(MUX_4, (channel >> 3) & 0x01);
}

void MUX::selectChannel(int channel)
{
    _selectChannel(channel);
    pinMode(MUX_SIG_PIN, INPUT);
    delay(300);
}

void MUX::selectChannel(int channel, uint8_t mode)
{
    _selectChannel(channel);
    pinMode(MUX_SIG_PIN, mode);
    delay(300);
}

int MUX::readMux(int channel)
{
    selectChannel(channel);
    return analogRead(MUX_SIG_PIN);
}

void MUX::clearMux()
{
    digitalWrite(MUX_1, LOW);
    digitalWrite(MUX_2, LOW);
    digitalWrite(MUX_3, LOW);
    digitalWrite(MUX_4, LOW);
    pinMode(MUX_SIG_PIN, INPUT);
}
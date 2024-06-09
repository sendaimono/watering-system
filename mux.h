#ifndef MUX_H
#define MUX_H

#define MUX_1 8
#define MUX_2 9
#define MUX_3 10
#define MUX_4 11
#define MUX_SIG_PIN A0

struct MUX
{
    void selectChannel(int channel);
    void selectChannel(int channel, uint8_t mode);
    int readMux(int channel);
    void clearMux();

private:
    void _selectChannel(int channel);
};

MUX Mux;

#endif
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
    int readMux(int channel);
};

MUX Mux;

#endif
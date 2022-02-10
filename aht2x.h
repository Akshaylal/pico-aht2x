#ifndef AHT2x_H
#define AHT2x_H

#include "hardware/i2c.h"

class AHT2x{
    private:
        i2c_inst *i2cInst;
        uint16_t address;
        uint8_t buff[6] = {};

        float t, h;

        void measure();
        bool isBusy();

    public:
        AHT2x(i2c_inst *i2cInst, uint16_t address);
        float temperature();
        float humidity();
};

#endif
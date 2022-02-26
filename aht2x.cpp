#include "aht2x.h"

AHT2x::AHT2x(i2c_inst *i2cInst, uint16_t address = 0x38){
    this->i2cInst = i2cInst;
    this->address = address;
}

float AHT2x::temperature(){
    measure();
    return t;
}

float AHT2x::humidity(){
    measure();
    return h;
}

void AHT2x::measure(){
    buff[0] = 0xAC; // command to trigger measurement
    buff[1] = 0x33; // command parameters
    buff[2] = 0x00; // command parameters

    i2c_write_blocking(i2cInst, address, buff, 3, false);
    
    sleep_ms(80); // wait 80ms to complete measurement
    
    while(isBusy()){  // wait if busy
        sleep_ms(10);
    }
    
    i2c_read_blocking(i2cInst, address, buff, 6, false);
    
    h = (buff[1] << 12) | (buff[2] << 4) | (buff[3] >> 4);
    t = ((buff[3] & 0xF) << 16) | (buff[4] << 8) | (buff[5]);

    h = (h / 0x100000) * 100;
    t = ((t / 0x100000) * 200) - 50;
}

bool AHT2x::isBusy(){
    i2c_read_blocking(i2cInst, address, buff, 1, false);
    return (buff[0] >> 7) & 0x1;
}
#include "aht2x.h"

AHT2x::AHT2x(i2c_inst *i2cInst, uint16_t address = 0x38){
    this->i2cInst = i2cInst;
    this->address = address;
}

float AHT2x::temperature(){
    this->measure();
    return this->t;
}

float AHT2x::humidity(){
    this->measure();
    return this->h;
}

void AHT2x::measure(){
    buff[0] = 0xAC; // command to trigger measurement
    buff[1] = 0x33; // command parameters
    buff[2] = 0x00; // command parameters

    i2c_write_blocking(this->i2cInst, this->address, this->buff, 3, false);
    
    sleep_ms(80); // wait 80ms to complete measurement
    
    while(this->isBusy()){  // wait if busy
        sleep_ms(10);
    }
    
    i2c_read_blocking(this->i2cInst, this->address, this->buff, 6, false);
    
    this->h = (this->buff[1] << 12) | (this->buff[2] << 4) | (this->buff[3] >> 4);
    this->t = ((this->buff[3] & 0xF) << 16) | (this->buff[4] << 8) | (this->buff[5]);

    this->h = (this->h / 0x100000) * 100;
    this->t = ((this->t / 0x100000) * 200) - 50;
}

bool AHT2x::isBusy(){
    i2c_read_blocking(this->i2cInst, this->address, this->buff, 1, false);
    return (this->buff[0] >> 7) & 0x1;
}
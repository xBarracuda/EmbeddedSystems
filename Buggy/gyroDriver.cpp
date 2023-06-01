#include "gyroDriver.h"
#include <bcm2835.h>

int Gyro::readGyroAxis(int axis){
    bcm2835_i2c_begin();
    bcm2835_i2c_setSlaveAddress(0x68);

    char * buffer[1];
    buffer[0] = gyroAxisAddr + axis*2;
    bcm2835_i2c_write(buffer, 1);
    bcm2835_i2c_read(buffer, 1);

    int value = buffer[0] << 8;

    buffer[0] = gyroAxisAddr + axis*2 + 1;
    bcm2835_i2c_write(buffer, 1);
    bcm2835_i2c_read(buffer, 1);
    bcm2835_i2c_end();

    value |=  buffer[0];
    return value
}
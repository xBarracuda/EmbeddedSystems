#include "gyroDriver.h"
#include <iostream>
#include <bcm2835.h>

short Gyro::readGyroAxis(int axis){
    //Gyroscope Measurements 
    short value = read16bitRegister(gyroAxisAddr + axis * 2);

    switch (axis)
    {
    case 0:
        value -= x_offset; break;
    case 1:
        value -= y_offset; break;
    case 2:
        value -= z_offset; break;
    default:
        break;
    }
    
    return value;
}

void Gyro::initializeGyro()
{
    bcm2835_i2c_begin();
    bcm2835_i2c_setSlaveAddress(0x68);
   // bcm2835_i2c_setClockDivider(10000);

    // Power Management
    char buffer[2];
    buffer[0] = 0x6B; // Power Management Register
    buffer[1] = 0x00; // Aktiviere das Gyroskop (Wakeup)
    bcm2835_i2c_write(buffer, 2);

    // Konfiguration des Gyroskops
    buffer[0] = 0x1B; // Gyroskop-Konfigurationsregister
    buffer[1] = 0x08; // ±500 Grad/Sekunde Messbereich
    bcm2835_i2c_write(buffer, 2);

    int x;
    int y;
    int z;
    for (int i = 0; i < 500; i++)
    {
        x += (int)readGyroAxis(xAxis);
        y += (int)readGyroAxis(yAxis);
        z += (int)readGyroAxis(zAxis);
    }
    x_offset = (short)(x/500);
    y_offset = (short)(y/500);
    z_offset = (short)(z/500);
    
    std::cout << "x: " << std::dec << x_offset << ", y: " << std::dec << y_offset << ", z: " << std::dec << z_offset << std::endl;

    bcm2835_i2c_end();

}

short Gyro::read16bitRegister(int adress)
{
    bcm2835_i2c_begin();
    bcm2835_i2c_setSlaveAddress(0x68);
   // bcm2835_i2c_setClockDivider(10000);

    char buffer[1];
    buffer[0] = (char)adress;
    bcm2835_i2c_write(buffer, 1);
    bcm2835_i2c_read(buffer, 1);

    short value = (short)(buffer[0] << 8);
    buffer[0] = (char)(adress + 1);
    bcm2835_i2c_write(buffer, 1);
    bcm2835_i2c_read(buffer, 1);
    bcm2835_i2c_end();

    value |= (short)(buffer[0]);

    return value;

}

//Buffer Gyro::readAxis()
//{
//    return Buffer();
//}

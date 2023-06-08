#include "gyroDriver.h"
#include <iostream>
#include <bcm2835.h>
#include <chrono>
#include <thread>

Gyro::Gyro() {}

Gyro::Gyro(std::mutex *i2c_mutex)
{
    this->i2c_mutex = i2c_mutex;
    std::cout << "mutex assigende" << std::endl;
    initializeGyro();
}

float Gyro::readGyroAxis(int axis){
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
    if (value >= 0) {
        return value * BitToDegree;
    }
    else {
        return value * BitToDegreeNegative;
    }
}

void Gyro::initializeGyro()
{
    std::cout << "waiting for lock" << std::endl;
    i2c_mutex->lock();
    std::cout << "lock claimed" << std::endl;
    bcm2835_i2c_begin();
    bcm2835_i2c_setSlaveAddress(0x68);

    // Power Management
    char buffer[2];
    buffer[0] = 0x6B; // Power Management Register
    buffer[1] = 0x00; // Aktiviere das Gyroskop (Wakeup)
    bcm2835_i2c_write(buffer, 2);

    // Konfiguration des Gyroskops
    buffer[0] = 0x1B; // Gyroskop-Konfigurationsregister
    buffer[1] = 0x08; // ±500 Grad/Sekunde Messbereich
    bcm2835_i2c_write(buffer, 2);
    bcm2835_i2c_end();
    i2c_mutex->unlock();

    int x, y, z;
    
    for (int i = 0; i < KalibirierungsIteration; i++)
    {
        x += (int)read16bitRegister(gyroAxisAddr + xAxis * 2);
        y += (int)read16bitRegister(gyroAxisAddr + yAxis * 2);
        z += (int)read16bitRegister(gyroAxisAddr + zAxis * 2);
    }

    x_offset = (short)(x/KalibirierungsIteration);
    y_offset = (short)(y/KalibirierungsIteration);
    z_offset = (short)(z/KalibirierungsIteration);

}

short Gyro::read16bitRegister(int adress)
{
    i2c_mutex->lock();
    bcm2835_i2c_begin();
    bcm2835_i2c_setSlaveAddress(0x68);
   // bcm2835_i2c_setClockDivider(10000);

    char buffer[1];
    buffer[0] = (char)adress;
    bcm2835_i2c_write(buffer, 1);
    bcm2835_i2c_read(buffer, 1); 
    //bcm2835_i2c_read(buffer, 2); 

    short value = (short)(buffer[0] << 8);
    buffer[0] = (char)(adress + 1);
    bcm2835_i2c_write(buffer, 1);
    bcm2835_i2c_read(buffer, 1);
    bcm2835_i2c_end();
    i2c_mutex->unlock();
    value |= (short)(buffer[0]);

    return value;
}

void Gyro::startMeasurement()
{
    this->isMeasuring = true;
    for (int i = 0; i < 3; i++)
    {
        this->relativeAngle[i] = 0;
    }
    std::thread updateThread(&Gyro::updateMeasurement, this);
    updateThread.detach();
    std::cout << "Gyro thread detached" << std::endl;
}

void Gyro::updateMeasurement()
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    bool firstMeasurment = true;
    float GradProSekunde[3];
    while (isMeasuring) {
        std::chrono::steady_clock::time_point oldbegin = begin;
        GradProSekunde[0] = readGyroAxis(xAxis);
        GradProSekunde[1] = readGyroAxis(yAxis);
        GradProSekunde[2] = readGyroAxis(zAxis);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        begin = std::chrono::steady_clock::now();
        float duration = (float)(std::chrono::duration_cast<std::chrono::microseconds>(end - oldbegin).count());
        if (!firstMeasurment) {
            for (int i = 0; i < 3; i++)
            {
                relativeAngle[i] += GradProSekunde[i] * (duration * 1e-6f);

            }
        }
        else {
            firstMeasurment = false;
        }
    }
}

void Gyro::endMeasurement()
{
    this->isMeasuring = false;
}

float Gyro::getRelativeAngle(int axis)
{
    return this->relativeAngle[axis];
}



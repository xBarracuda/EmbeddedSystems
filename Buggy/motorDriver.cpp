#include "motorDriver.h"
#include <iostream>

Motor::Motor(int motorIndex){
   switch (motorIndex)
    {
        case 0:
            pwmPin = 8;
            in2Pin = 9;
            in1Pin = 10;
            break;
        case 1:
            pwmPin = 13;
            in2Pin = 12;
            in1Pin = 11;
            break;
        case 2:
            pwmPin = 2;
            in2Pin = 3;
            in1Pin = 4;
            break;
        case 3:
            pwmPin = 7;
            in2Pin = 6;
            in1Pin = 5;
            break;
        default:
            std::out("Motor index out-of-range. Must be between 0 and 3.");
            break;
    } 
}

void Motor::setCommand(int command){
    switch (command)
    {
        case FORWARD:
            setLEDPin(in1Pin, LED_ENABLE, LED_DISABLE);
            setLEDPin(in2Pin, LED_DISABLE, LED_ENABLE);
            break;
        case BACKWARD:
            setLEDPin(in1Pin, LED_DISABLE, LED_ENABLE);
            setLEDPin(in2Pin, LED_ENABLE, LED_DISABLE);
            break;
        case BREAK:
            setLEDPin(in1Pin, LED_ENABLE, LED_DISABLE);
            setLEDPin(in2Pin, LED_ENABLE, LED_DISABLE);
            break;
        case RELEASE:
            setLEDPin(in1Pin, LED_DISABLE, LED_ENABLE);
            setLEDPin(in2Pin, LED_DISABLE, LED_ENABLE);
            break;
        default:
            break;
    }
}

void Motor::setSpeed(float speed){
    int value = (int)(speed * 40.96);
    setLEDPin(pwmPin,0,value);
}

void setLEDPin(int number, int valueOn, int valueOff){
    bcm2835_i2c_begin();
    bcm2835_i2c_setSlaveAddress(0x60);
    char * buffer[2];

    buffer[0] = LED_Base + 4*(number);
    buffer[1] = valueOn;
    bcm2835_i2c_write(buffer, 2);

    buffer[0] = LED_Base + 4*(number)+1;
    buffer[1] = valueOn >> 8;
    bcm2835_i2c_write(buffer, 2);

    buffer[0] = LED_Base + 4*(number)+2;
    buffer[1] = valueOff;
    bcm2835_i2c_write(buffer, 2);

    buffer[0] = LED_Base + 4*(number)+3;
    buffer[1] = valueOff >> 8;
    bcm2835_i2c_write(buffer, 2);

    bcm2835_i2c_end();
}
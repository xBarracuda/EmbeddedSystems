#include "motorDriver.h"
#include <bcm2835.h>
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
    std::cout << "Hier0\n";
    char buffer[2];

    std::cout << "Hier1\n";

    buffer[0] = (char)(LED_Base + 4*(number));
    std::cout << "Hier2\n";
    buffer[1] = (char)valueOn;
    std::cout << "Hier3\n";
    bcm2835_i2c_write(buffer, 2);
    std::cout << "Hier4\n";
    buffer[0] = (char)(LED_Base + 4*(number)+1);
    buffer[1] = (char)(valueOn >> 8);
    bcm2835_i2c_write(buffer, 2);

    buffer[0] = (char)(LED_Base + 4*(number)+2);
    buffer[1] = (char)valueOff;
    bcm2835_i2c_write(buffer, 2);

    buffer[0] = (char)(LED_Base + 4*(number)+3);
    buffer[1] = (char)(valueOff >> 8);
    bcm2835_i2c_write(buffer, 2);

    bcm2835_i2c_end();
}
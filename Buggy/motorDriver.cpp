#include "motorDriver.h"
#include <bcm2835.h>
#include <iostream>
#include <iomanip>

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

    std::cout << "number: " << number << std::endl;
    std::cout << "valueon: " << valueOn   << std::endl;

    std::cout << "valueoff: " << valueOff << std::endl;
    if (!bcm2835_i2c_begin())
    {
        std::cout << "begin failed";
       
    }
    
    bcm2835_i2c_setSlaveAddress(0x60);
    bcm2835_i2c_setClockDivider(1000);

    
    char buffer[2];

    buffer[0] = (char)(LED_Base + 4*(number));
    buffer[1] = (char)valueOn;
    std::cout << "Buffer 0: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(buffer[0])<< std::endl;
    std::cout << "Buffer 1: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(buffer[1]) << std::endl;
    bcm2835_i2c_write(buffer, 2);
    
    buffer[0] = (char)(LED_Base + 4*(number)+1);
    buffer[1] = (char)(valueOn >> 8);
    std::cout << "Buffer 0: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(buffer[0]) << std::endl;
    std::cout << "Buffer 1: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(buffer[1]) << std::endl;
    bcm2835_i2c_write(buffer, 2);

    buffer[0] = (char)(LED_Base + 4*(number)+2);
    buffer[1] = (char)valueOff;
    std::cout << "Buffer 0: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(buffer[0]) << std::endl;
    std::cout << "Buffer 1: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(buffer[1]) << std::endl;
    bcm2835_i2c_write(buffer, 2);

    buffer[0] = (char)(LED_Base + 4*(number)+3);
    buffer[1] = (char)(valueOff >> 8);
    std::cout << "Buffer 0: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(buffer[0]) << std::endl;
    std::cout << "Buffer 1: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(buffer[1]) << std::endl;
    bcm2835_i2c_write(buffer, 2);

    bcm2835_i2c_end();
}
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
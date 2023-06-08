#include "gyroDriver.h"
#include "adafruit-motor-hat-cpp-library/source/adafruitmotorhat.h"
#include "adafruit-motor-hat-cpp-library/source/adafruitdcmotor.h"
#include "UltraSchallDriver.h"

class Buggy{
    private:
    AdafruitMotorHAT hat;
    Gyro gyroskop;
    UltraSchall ultraschall;

    public:
    Buggy();
    void drive(float speed, AdafruitDCMotor::Command command= AdafruitDCMotor::kForward, float angle=0, float curveSpeed=0);
};
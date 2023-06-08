#include "gyroDriver.h"
#include "adafruit-motor-hat-cpp-library/source/adafruitmotorhat.h"
#include "adafruit-motor-hat-cpp-library/source/adafruitdcmotor.h"
#include "UltraSchallDriver.h"

class Buggy{
    private:
    AdafruitMotorHAT hat;
    Gyro gyroskop;
    UltraSchall ultraschall;
    int motorLeft;
    int motorRight;

    public:
    Buggy(int leftMotor, int rightMotor);
    void drive(float speed, float angle=0, float curveSpeed=0);
    void stopBuggy();
};
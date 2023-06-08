#include "gyroDriver.h"
#include "adafruit-motor-hat-cpp-library/source/adafruitmotorhat.h"
#include "adafruit-motor-hat-cpp-library/source/adafruitdcmotor.h"
#include "UltraSchallDriver.h"
#define deltaAngle 0.2f
class Buggy{
    private:
    AdafruitMotorHAT hat;
    //Gyro gyroskop;
    //UltraSchall ultraschall;
    int motorLeft;
    int motorRight;
    void setMotors(int leftSpeed, int rightSpeed);

    public:
    Buggy(int leftMotor, int rightMotor);
    void drive(float speed);
    void curve(float speed, float angle, float curveSpeed);
};
void releaseMotors();
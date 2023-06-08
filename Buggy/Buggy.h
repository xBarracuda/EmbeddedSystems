#include "gyroDriver.h"
#include "adafruit-motor-hat-cpp-library/source/adafruitmotorhat.h"
#include "adafruit-motor-hat-cpp-library/source/adafruitdcmotor.h"
#include "UltraSchallDriver.h"
#define deltaAngle 0.2f
class Buggy{
    private:
    //Gyro gyroskop;
    //UltraSchall ultraschall;
    int motorLeft;
    int motorRight;
    

    public:
    void setMotors(int leftSpeed, int rightSpeed);
    Buggy(int motorLeft, int motorRight);
    void drive(float speed);
    void curve(float speed, float angle, float curveSpeed);
};
void releaseMotors();
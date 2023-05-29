#include "motorDriver.h"
#include "gyroDriver.h"

class Buggy{
    private:
    Motor motorRechts = Motor(0);
    Motor motorLinks = Motor(1);

    Gyro gyroskop = Gyro();

    public:
    Buggy();
    void drive(float speed, int command);
    void turn(float angle, float speed);
};
#include "Buggy.h"
#include "adafruit-motor-hat-cpp-library/source/adafruitmotorhat.h"
#include "adafruit-motor-hat-cpp-library/source/adafruitdcmotor.h"

Buggy::Buggy()
{
	gyroskop = Gyro();
	ultraschall = UltraSchall(18, 27);
}

void Buggy::drive(float speed, AdafruitDCMotor::Command command, float angle, float curveSpeed)
{
}

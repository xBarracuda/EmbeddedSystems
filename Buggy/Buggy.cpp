#include "Buggy.h"
#include "adafruit-motor-hat-cpp-library/source/adafruitmotorhat.h"
#include "adafruit-motor-hat-cpp-library/source/adafruitdcmotor.h"

Buggy::Buggy(int motorLeft, int motorRight)
{
	this->motorLeft = motorLeft;
	this->motorRight = motorRight;

	gyroskop = Gyro();
	ultraschall = UltraSchall(18, 27);
}

void Buggy::drive(float speed, float angle, float curveSpeed)
{
	int speedLeft = speed;
	int speedRight = speed;

	if (angle < 0)speedLeft -= curveSpeed;
	if (angle > 0)speedRight -= curveSpeed;

	if (auto motor{ hat.getMotor(this->motorLeft) })
	{
		motor->setSpeed(speedLeft);
		if (speedLeft > 0) motor->run(AdafruitDCMotor::kForward);
		if (speedLeft < 0) motor->run(AdafruitDCMotor::kBackward);
		if (speedLeft == 0) motor->run(AdafruitDCMotor::kRelease);
	}

	if (auto motor{ hat.getMotor(this->motorRight) })
	{
		motor->setSpeed(speedRight);
		if (speedRight > 0) motor->run(AdafruitDCMotor::kForward);
		if (speedRight < 0) motor->run(AdafruitDCMotor::kBackward);
		if (speedRight == 0) motor->run(AdafruitDCMotor::kRelease);
	}
}

void Buggy::stopBuggy() {
	if (auto motor{ hat.getMotor(this->motorLeft) })
	{
		motor->run(AdafruitDCMotor::kRelease);
	}
	if (auto motor{ hat.getMotor(this->motorRight) })
	{
		motor->run(AdafruitDCMotor::kRelease);
	}
}

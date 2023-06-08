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

void Buggy::drive(float speed)
{
	if (auto motor{ hat.getMotor(this->motorLeft) })
	{
		motor->setSpeed(speed);
		if (speed > 0) motor->run(AdafruitDCMotor::kForward);
		if (speed < 0) motor->run(AdafruitDCMotor::kBackward);
		if (speed == 0) motor->run(AdafruitDCMotor::kRelease);
	}

	if (auto motor{ hat.getMotor(this->motorRight) })
	{
		motor->setSpeed(speed);
		if (speed > 0) motor->run(AdafruitDCMotor::kBackward);
		if (speed < 0) motor->run(AdafruitDCMotor::kForward);
		if (speed == 0) motor->run(AdafruitDCMotor::kRelease);
	}
}

void Buggy::curve(float speed, float angle, float curveSpeed)
{
	gyroskop.startMeasurement();
	int speedLeft = speed;
	int speedRight = speed;

	bool isRotating = true;

	while (isRotating) {
		if (gyroskop.getRelativeAngle(zAxis) > (angle+deltaAngle))speedLeft -= curveSpeed;
		else if (gyroskop.getRelativeAngle(zAxis) < (angle-deltaAngle))speedRight -= curveSpeed;
		else isRotating = false;

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
			if (speedRight > 0) motor->run(AdafruitDCMotor::kBackward);
			if (speedRight < 0) motor->run(AdafruitDCMotor::kForward);
			if (speedRight == 0) motor->run(AdafruitDCMotor::kRelease);
		}
	}
	releaseMotors();
}

void Buggy::releaseMotors() {
	if (auto motor{ hat.getMotor(this->motorLeft) })
	{
		motor->run(AdafruitDCMotor::kRelease);
	}
	if (auto motor{ hat.getMotor(this->motorRight) })
	{
		motor->run(AdafruitDCMotor::kRelease);
	}
}

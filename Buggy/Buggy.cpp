#include "Buggy.h"
#include "adafruit-motor-hat-cpp-library/source/adafruitmotorhat.h"
#include "adafruit-motor-hat-cpp-library/source/adafruitdcmotor.h"
#include <iostream>

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

void Buggy::setMotors(int leftSpeed, int rightSpeed)
{
	if (auto motor{ hat.getMotor(this->motorLeft) })
	{
		motor->setSpeed(leftSpeed);
		if (leftSpeed > 0) motor->run(AdafruitDCMotor::kForward);
		if (leftSpeed < 0) motor->run(AdafruitDCMotor::kBackward);
		if (leftSpeed == 0) motor->run(AdafruitDCMotor::kRelease);
	}

	if (auto motor{ hat.getMotor(this->motorRight) })
	{
		motor->setSpeed(rightSpeed);
		if (rightSpeed > 0) motor->run(AdafruitDCMotor::kBackward);
		if (rightSpeed < 0) motor->run(AdafruitDCMotor::kForward);
		if (rightSpeed == 0) motor->run(AdafruitDCMotor::kRelease);
	}
}

void Buggy::curve(float speed, float angle, float curveSpeed)
{
	gyroskop.startMeasurement();
	std::cout << "Gyro gestartet" << std::endl;
	int speedLeft = speed;
	int speedRight = speed;

	bool isRotating = true;
	bool isTurningLeft = false;
	bool isTurningRight = false;

	while (isRotating) {
		std::cout << "Gyro: " << gyroskop.getRelativeAngle(zAxis) << std::endl;
		if (gyroskop.getRelativeAngle(zAxis) > (angle + deltaAngle) && !isTurningLeft) {
			speedLeft -= curveSpeed;
			isTurningLeft = true;
			isTurningRight = false;
			setMotors(speedLeft, speedRight);
		}
		else if (gyroskop.getRelativeAngle(zAxis) < (angle - deltaAngle) && !isTurningRight) {
			speedRight -= curveSpeed;
			isTurningLeft = false;
			isTurningRight = true;
			setMotors(speedLeft, speedRight);
		}
		else if(gyroskop.getRelativeAngle(zAxis) > (angle - deltaAngle) && gyroskop.getRelativeAngle(zAxis) < (angle + deltaAngle)) isRotating = false;
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

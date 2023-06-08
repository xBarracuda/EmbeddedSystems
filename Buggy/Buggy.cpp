#include "Buggy.h"
#include "adafruit-motor-hat-cpp-library/source/adafruitmotorhat.h"
#include "adafruit-motor-hat-cpp-library/source/adafruitdcmotor.h"
#include <iostream>

void Buggy::init(int motorLeft, int motorRight)
{
	this->motorLeft = motorLeft;
	this->motorRight = motorRight;
	//ultraschall = UltraSchall(18, 27);
	std::cout << "init gyro" << std::endl;
	gyroskop = Gyro(&i2c_mutex);
	std::cout << "done" << std::endl;
}

void Buggy::drive(float speed)
{
	setMotors(speed, speed);
}

void Buggy::setMotors(int leftSpeed, int rightSpeed)
{
	i2c_mutex.lock();
	AdafruitMotorHAT hat;
	if (auto motor{ hat.getMotor(1) })
	{
		motor->setSpeed(leftSpeed);
		if (leftSpeed > 0) motor->run(AdafruitDCMotor::kForward);
		if (leftSpeed < 0) motor->run(AdafruitDCMotor::kBackward);
		if (leftSpeed == 0) motor->run(AdafruitDCMotor::kRelease);
	}

	if (auto motor{ hat.getMotor(4) })
	{
		motor->setSpeed(rightSpeed);
		if (rightSpeed > 0) motor->run(AdafruitDCMotor::kBackward);
		if (rightSpeed < 0) motor->run(AdafruitDCMotor::kForward);
		if (rightSpeed == 0) motor->run(AdafruitDCMotor::kRelease);
	}
	i2c_mutex.unlock();
}

void Buggy::curve(float speed, float angle, float curveSpeed)
{
	/*gyroskop.startMeasurement();
	std::cout << "Gyro gestartet" << std::endl;
	int speedLeft = speed;
	int speedRight = speed;

	bool isRotating = true;
	bool isTurningLeft = false;
	bool isTurningRight = false;

	while (isRotating) {
		//std::cout << "Gyro: " << gyroskop.getRelativeAngle(zAxis) << std::endl;
		if (gyroskop.getRelativeAngle(zAxis) > (angle + deltaAngle) && !isTurningLeft) {
			std::cout << "Dreh links" << std::endl;
			speedLeft -= curveSpeed;
			isTurningLeft = true;
			isTurningRight = false;
			setMotors(speedLeft, speedRight);
		}
		else if (gyroskop.getRelativeAngle(zAxis) < (angle - deltaAngle) && !isTurningRight) {
			std::cout << "Dreh rechts" << std::endl;
			speedRight -= curveSpeed;
			isTurningLeft = false;
			isTurningRight = true;
			setMotors(speedLeft, speedRight);
		}
		else if (gyroskop.getRelativeAngle(zAxis) > (angle - deltaAngle) && gyroskop.getRelativeAngle(zAxis) < (angle + deltaAngle)) {
			isRotating = false;
			std::cout << "fertig" << std::endl;
		}
	}*/
}

void Buggy::releaseMotors() {
	i2c_mutex.lock();
	AdafruitMotorHAT hat;
	for (int i = 1; i <= 4; i++) {
		if (auto motor{ hat.getMotor(i) })
		{
			motor->run(AdafruitDCMotor::kRelease);
		}
	}
	i2c_mutex.unlock();
}

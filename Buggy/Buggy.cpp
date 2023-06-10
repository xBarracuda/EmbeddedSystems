#include "Buggy.h"
#include "adafruit-motor-hat-cpp-library/source/adafruitmotorhat.h"
#include "adafruit-motor-hat-cpp-library/source/adafruitdcmotor.h"
#include <iostream>
#include <bcm2835.h>

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
	std::cout << "before mutex lock in setmotor" << std::endl;
	i2c_mutex.lock();
	bcm2835_delay(1);
	std::cout << "mutex locked in setmotor" << std::endl;			
	
	if (auto motor{ hat.getMotor(this->motorLeft) })
	{
		motor->setSpeed(leftSpeed);
		std::cout << "speed left set" << std::endl;
		if (leftSpeed > 0) motor->run(AdafruitDCMotor::kForward);
		if (leftSpeed < 0) motor->run(AdafruitDCMotor::kBackward);
		if (leftSpeed == 0) motor->run(AdafruitDCMotor::kRelease);
	}
	else {
		std::cout << "Motor konnte nicht gesetzt werden" << std::endl;
	}

	if (auto motor{ hat.getMotor(this->motorRight) })
	{
		motor->setSpeed(rightSpeed);
		std::cout << "speed right set" << std::endl;

		if (rightSpeed > 0) motor->run(AdafruitDCMotor::kBackward);
		if (rightSpeed < 0) motor->run(AdafruitDCMotor::kForward);
		if (rightSpeed == 0) motor->run(AdafruitDCMotor::kRelease);
	}
	else {
		std::cout << "Motor konnte nicht gesetzt werden" << std::endl;
	}
	i2c_mutex.unlock();
	std::cout << "mutex unlocked in setmotor" << std::endl;
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
	}
}

void Buggy::releaseMotors() {
	i2c_mutex.lock();
	bcm2835_delay(1);
	for (int i = 1; i <= 4; i++) {
		if (auto motor{ hat.getMotor(i) })
		{
			motor->run(AdafruitDCMotor::kRelease);
		}
	}
	i2c_mutex.unlock();
}

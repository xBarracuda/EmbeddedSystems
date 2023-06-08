///
/// Project main
///
/*
/// Includes
#include <signal.h>
#include <iostream>
#include <bcm2835.h>

#include "Buggy.h"
#include "gyroDriver.h"
#include "UltraSchallDriver.h"

using namespace std;

/// Interrupt Routine for STRG-C
void signalHandler(int signum)
{
    cout << "\n Strg-C Programmende" << endl;
	// Beenden Sie hier bitte alle Verbindung zu den Sensoren etc.
    releaseMotors();
    bcm2835_close();
    exit(signum);
}

int main()
{   
    signal(SIGINT, signalHandler);
    if (!bcm2835_init())
        return 1;

    Buggy buggy(1, 4);

    
    Gyro gyro;
    //gyro.initializeGyro();
    gyro.startMeasurement();
    while (true) {
        std::cout << "xAxis: " << std::dec << gyro.getRelativeAngle(xAxis) ;
        std::cout << " yAxis: " << std::dec << gyro.getRelativeAngle(yAxis) ;
        std::cout << " zAxis: " << std::dec << gyro.getRelativeAngle(zAxis) << endl;
    }
    
  
    UltraSchall ultraSchall(18, 27);

    while (true) {
        std::cout << "Abstand: " << std::dec << ultraSchall.getDistance() << "cm" << std::endl;
        bcm2835_delay(20);
    }
    
    
    buggy.drive(100);
    //std::cout << "Geerade aus" << std::endl;
    bcm2835_delay(1000);
    std::cout << "Starte Kurve" << std::endl;
    buggy.curve(100,90,100);
    std::cout << "Kurve fertig" << std::endl;
    
    // Csignal für Abbruch über STRG-C
    for (;;);
    return 0;
}*/

#include <thread>
#include <chrono>
#include "adafruit-motor-hat-cpp-library/source/adafruitmotorhat.h"

int main()
{
    using namespace std::chrono_literals;

    // connect using the default device address 0x60
    AdafruitMotorHAT hat;

    // get the motor connected to port 1
    if (auto motor{ hat.getMotor(1) })
    {
        // speed must be set before running commands
        motor->setSpeed(255);

        motor->run(AdafruitDCMotor::kForward);
        std::this_thread::sleep_for(1s);

        motor->run(AdafruitDCMotor::kBackward);
        std::this_thread::sleep_for(1s);

        // release the motor after use
        motor->run(AdafruitDCMotor::kRelease);
    }

    return 0;
}
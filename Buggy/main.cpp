///
/// Project main
///

/// Includes
#include <signal.h>
#include <iostream>
#include <bcm2835.h>

#include "gyroDriver.h"
#include "motorDriver.h"
using namespace std;
/// Interrupt Routine for STRG-C
void signalHandler(int signum)
{
    cout << "\n Strg-C Programmende" << endl;
	// Beenden Sie hier bitte alle Verbindung zu den Sensoren etc.
    bcm2835_close();
    exit(signum);
}

int main()
{
    if (!bcm2835_init())
        return 1;

    Motor newMotor(0);
    Motor newMotor1(1);
    Motor newMotor2(2);
    Motor newMotor3(3);

    newMotor.setCommand(FORWARD);
    newMotor1.setCommand(FORWARD);
    newMotor2.setCommand(FORWARD);
    newMotor3.setCommand(FORWARD);

    newMotor.setSpeed(50);
    newMotor1.setSpeed(50);
    newMotor2.setSpeed(50);
    newMotor3.setSpeed(50);

    Gyro gyro;
    std::cout << "xAxis: " << gyro.readGyroAxis(xAxis);
    std::cout << "yAxis: " << gyro.readGyroAxis(yAxis);
    std::cout << "zAxis: " << gyro.readGyroAxis(zAxis);


    bcm2835_close();
    // Csignal für Abbruch über STRG-C
    signal(SIGINT, signalHandler);
    for (;;);
    return 0;
}

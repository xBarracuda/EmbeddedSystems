///
/// Project main
///

/// Includes
#include <signal.h>
#include <iostream>
#include <bcm2835.h>

#include "Buggy.h"
#include "gyroDriver.h"
#include "UltraSchallDriver.h"

using namespace std;
Buggy buggy(1, 4);
/// Interrupt Routine for STRG-C
void signalHandler(int signum)
{
    cout << "\n Strg-C Programmende" << endl;
    buggy.releaseMotors();
	// Beenden Sie hier bitte alle Verbindung zu den Sensoren etc.
    bcm2835_close();
    exit(signum);
}

int main()
{    
    signal(SIGINT, signalHandler);

    if (!bcm2835_init())
        return 1;
    
    /*Gyro gyro;
    gyro.initializeGyro();
    gyro.startMeasurement();
    while (true) {
        std::cout << "xAxis: " << std::dec << gyro.getRelativeAngle(xAxis) ;
        std::cout << " yAxis: " << std::dec << gyro.getRelativeAngle(yAxis) ;
        std::cout << " zAxis: " << std::dec << gyro.getRelativeAngle(zAxis) << endl;
    }*/
    
    /*
    UltraSchall ultraSchall(18, 27);

    while (true) {
        std::cout << "Abstand: " << std::dec << ultraSchall.getDistance() << "cm" << std::endl;
        bcm2835_delay(20);
    }
    */
    buggy.drive(100);
    bcm2835_delay(1000);
    buggy.curve(100,90,100);

    // Csignal für Abbruch über STRG-C
    for (;;);
    return 0;
}

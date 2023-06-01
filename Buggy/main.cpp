///
/// Project main
///

/// Includes
#include <signal.h>
#include <iostream>
#include "motorDriver.h"
using namespace std;
/// Interrupt Routine for STRG-C
void signalHandler(int signum)
{
    cout << "Strg-C Programmende" << endl;
	// Beenden Sie hier bitte alle Verbindung zu den Sensoren etc.
    exit(signum);
}

int main()
{
    if (!bcm2835_init())
        return 1;

    std::cout << "start\n";
    Motor newMotor(0);
    std::cout << "new motor\n";
    Motor newMotor1(1);
    Motor newMotor2(2);
    Motor newMotor3(3);
    std::cout << "all motors\n";

    newMotor.setCommand(FORWARD);
    std::cout << "first commdn\n";
    newMotor1.setCommand(BACKWARD);
    newMotor2.setCommand(BREAK);
    newMotor3.setCommand(RELEASE);
    // Csignal für Abbruch über STRG-C
    signal(SIGINT, signalHandler);

    return 0;
}

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
    Motor newMotor(0);
    Motor newMotor1(1);
    Motor newMotor2(2);
    Motor newMotor3(3);

    newMotor.setCommand(FORWARD);
    newMotor1.setCommand(BACKWARD);
    newMotor2.setCommand(BREAK);
    newMotor3.setCommand(RELEASE);
    // Csignal für Abbruch über STRG-C
    signal(SIGINT, signalHandler);

    return 0;
}

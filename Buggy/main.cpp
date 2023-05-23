///
/// Project main
///

/// Includes
#include <signal.h>
#include <iostream>
#include <wiringPi.h>
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
    wiringPiSetup () ;
    pinMode (0, OUTPUT) ;
    for (;;)
    {
        digitalWrite (0, HIGH) ; delay (500) ;
        digitalWrite (0,  LOW) ; delay (500) ;
    }
    // Csignal für Abbruch über STRG-C
    signal(SIGINT, signalHandler);

    return 0;
}

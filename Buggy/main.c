///
/// Project main
///

/// Includes
#include <signal.h>
#include <iostream>

/// Interrupt Routine for STRG-C
void signalHandler(int signum)
{
    std::cout << "Strg-C Programmende" << std::endl;
	// Beenden Sie hier bitte alle Verbindung zu den Sensoren etc.
    exit(signum);
}

int main()
{
    // Csignal für Abbruch über STRG-C
    signal(SIGINT, signalHandler);

    return 0;
}

#pragma once
#define CMproMikrosekunde 0.03432f //Schallgeschwindigkeit (343.2m/s) in CM pro Sekunde dividiert durch 10^6 um auf CM pro Mikrosekunde zu kommen

class UltraSchall {
private:
	int Trigger;
	int Echo;

public:
	UltraSchall();
	UltraSchall(int PinTrigger, int PinEcho);
	int getDistance();
};
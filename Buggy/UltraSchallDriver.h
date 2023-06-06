#pragma once
#define CMproMikrosekunde 0.003432f

class UltraSchall {
private:
	int Trigger;
	int Echo;

public:
	UltraSchall(int PinTrigger, int PinEcho);
	int getDistance();
};
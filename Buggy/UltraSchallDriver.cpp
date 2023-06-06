#include "UltraSchallDriver.h"
#include <bcm2835.h>
#include <chrono>

UltraSchall::UltraSchall(int PinTrigger, int PinEcho)
{
	this->Echo = PinEcho;
	this->Trigger = PinTrigger;
}

int UltraSchall::getDistance()
{
	bcm2835_gpio_write(Trigger, HIGH);

	bcm2835_gpio_write(Trigger, LOW);

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now(); 
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	while (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() < 450) {
		end = std::chrono::steady_clock::now();
	}
	begin = std::chrono::steady_clock::now();

	while (bcm2835_gpio_lev(Echo) > 0) {

	}

	 end = std::chrono::steady_clock::now();

	int duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

	if (duration > 190) {
		return -1;
	}
	else {
		return (int)(duration / 2.0f * CMproMikrosekunde);
	}
}

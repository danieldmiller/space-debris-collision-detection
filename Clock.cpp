#include "Clock.h"



void Clock::startClock()
{
	startTime = std::chrono::high_resolution_clock::now();
}

void Clock::endClock()
{
	endTime = std::chrono::high_resolution_clock::now();
}



std::ostream& operator<<(std::ostream& out, const Clock& time)
{

	out << "Time elapsed " << std::chrono::duration_cast<std::chrono::nanoseconds>(time.endTime - time.startTime).count() << "ns";
		return out;
}

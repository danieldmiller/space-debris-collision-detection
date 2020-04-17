#include "Clock.h"



void Clock::startClock()
{
	startTime = std::chrono::high_resolution_clock::now();
}

void Clock::endClock()
{
	endTime = std::chrono::high_resolution_clock::now();
}

long long Clock::returnParallelTime()
{
	return (std::chrono::duration_cast<std::chrono::nanoseconds>((endTime - startTime)).count() /  (long long)std::thread::hardware_concurrency());
}

long long Clock::returnSingleTime()
{
	return std::chrono::duration_cast<std::chrono::nanoseconds>((endTime - startTime)).count();
}

std::ostream& operator<<(std::ostream& out, const Clock& time)
{

	out << "Time elapsed " << std::chrono::duration_cast<std::chrono::nanoseconds>(time.endTime - time.startTime).count() << "ns";
		return out;
}

#pragma once
#ifndef CLOCK_H
#define CLOCK_H

#include <thread>
#include <chrono>
#include <iostream>

class Clock {
	friend std::ostream& operator<<(std::ostream& out, const Clock& time);
public:
	void startClock();
	void endClock();
	
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> startTime, endTime;/* = std::chrono::high_resolution_clock::now();*/
};

#endif /* !CLOCK_H*/
#pragma once
#ifndef CLOCK_H
#define CLOCK_H

#include <thread>
#include <chrono>
#include <iostream>
//using namespace std::chrono;
/*for (int i = 1; i <= 10; i++) {
	time_point<high_resolution_clock> start = high_resolution_clock::now();
	this_thread::sleep_for(milliseconds(10 * i));
	time_point<high_resolution_clock> end = high_resolution_clock::now();
	cout << "Time elapsed "
		<< duration_cast<nanoseconds>(end - start).count()
		<< "ns”
		<< endl;
}*/
class Clock {
	friend std::ostream& operator<<(std::ostream& out, const Clock& time);
public:
	void startClock();
	void endClock();
	long long returnParallelTime();
	long long returnSingleTime();
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> startTime, endTime;/* = std::chrono::high_resolution_clock::now();*/
};

#endif /* !CLOCK_H*/
#pragma once
#ifndef SPACE_H
#define SPACE_H

#include "SpaceObject.h"
#include "SpaceWriter.h"
#include "Clock.h"
#include <thread>
#include <mutex>
#include <vector>


class Space {
public:
	Space(int amountOfDebris0 = 0, bool printObjects = false);
	Space(const Space& rf);
	~Space();
	void initializeObjects();
    void updateObjects();

	//functions to run initialization/updating via multithreading, can compare the time with clock
	void initializeObjectsThreads();
	void updateObjectsThreads();

private:
	std::vector<SpaceObject> debris;
	std::vector <std::thread> threads;
	SpacePoint limit[7];
	SpaceWriter* output;
    SpaceWriter* collisionOutput;
	int amountOfDebris;
	static double time;
	const int nThreads = std::thread::hardware_concurrency();
	std::mutex m;
	Clock singleP, multiP;

	//void initializeObjectsForThreads(int begin, int end);
	void updateForceForThreads(int begin, int end);
};

#endif /* !SPACE_H*/

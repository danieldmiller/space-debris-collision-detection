#pragma once
#ifndef SPACE_H
#define SPACE_H

#include "SpaceObject.h"
#include "SpaceWriter.h"
#include "Clock.h"
#include <thread>
#include <mutex>
#include <vector>
#include <set>


class Space {
public:
	Space(int _amountOfDebris = 0, bool printObjects = false, int _threadCount = 1, int seed = 0);
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
    int threadCount;
    int seed;
	std::mutex m;
	Clock singleP, multiP;

    void updateForceForThreads(int begin, int end, std::set<int> &collisionIndexes);
    void task(int number);
};

#endif /* !SPACE_H*/

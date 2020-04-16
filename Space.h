#pragma once
#ifndef SPACE_H
#define SPACE_H

#include <vector>
#include "SpaceObject.h"
#include "SpaceWriter.h"

class Space {
public:
	Space(int amountOfDebris0 = 0);
	Space(const Space& rf);
	~Space();
	void initializeObjects();
    void updateObjects();

private:
	std::vector<SpaceObject> debris;
	SpacePoint limit[7];
	SpaceWriter *output;
	int amountOfDebris;
	static double time;
};

#endif /* !SPACE_H*/

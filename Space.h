#pragma once
#ifndef SPACE_H
#define SPACE_H

#include "SpaceObject.h"
#include <vector>

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
	int amountOfDebris;
	static double time;
};

#endif /* !SPACE_H*/

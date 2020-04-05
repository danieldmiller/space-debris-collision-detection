#pragma once
#ifndef SPACE_H
#define SPACE_H

#include "SpaceObject.h"
class Space {
public:
	Space(int amountOfDebris0 = 0);
	Space(const Space& rf);
	~Space();
	void initializeObjects();

private:
	SpaceObject *debris;
	SpacePoint limit[7];
	int amountOfDebris;
};

#endif /* !SPACE_H*/
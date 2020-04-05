//#include "SpaceObject.h"
#include "Space.h"

Space::Space(int amountOfDebris0)
{
	amountOfDebris = amountOfDebris0;
	debris = new SpaceObject[amountOfDebris];

	//initialize the limits for the space
	//for(int i = 0; i < 8 ; i++){
	//do something with limit[7]
	//}
}

Space::Space(const Space& rf) {
	amountOfDebris = rf.amountOfDebris;
	debris = new SpaceObject[amountOfDebris];
	*debris = *rf.debris;
}

Space::~Space()
{
	delete[] debris;
}

void Space::initializeObjects()
{
}

#include "Space.h"
#include "SpaceObject.h"
#include <random>

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
    double lower_bound = 2;
    double upper_bound = 5;
    std::uniform_real_distribution<double> uniform(lower_bound,upper_bound);
    std::default_random_engine re;
    double a_random_double = uniform(re);

    for(int i=0; i<amountOfDebris; i++) {
        double mass = uniform(re);
        double radius = uniform(re);
        double x = uniform(re);
        double y = uniform(re);
        double z = uniform(re);
        *(debris + i) = SpaceObject(mass, radius, x, y, z);
    }
}

void Space::updateObjects()
{
    for (int i = 0; i < amountOfDebris; i++) {
        for(int j = i + 1; j < amountOfDebris; j++) {
            SpaceObject obj_i = *(debris + i);
            SpaceObject obj_j = *(debris + j);
            obj_i.getGravitationalForceX(obj_j);
            obj_i.getGravitationalForceY(obj_j);
            obj_i.getGravitationalForceZ(obj_j);
        }
   }

    for (int i = 0; i < amountOfDebris; i++) {
        SpaceObject obj = *(debris + i);
        obj.getGravitationalForceR();
        obj.recordDirection();
        obj.recordVelocity();
    }
}
#include "Space.h"
#include "SpaceObject.h"
#include <random>

double Space::time = 0.0;

Space::Space(int amountOfDebris0)
{
	amountOfDebris = amountOfDebris0;
	// debris = new SpaceObject[amountOfDebris];

	//initialize the limits for the space
	//for(int i = 0; i < 8 ; i++){
	//do something with limit[7]
	//}
}

Space::Space(const Space& rf) {
	amountOfDebris = rf.amountOfDebris;
	debris = rf.debris;
}

Space::~Space()
{
}

void Space::initializeObjects()
{
    double lower_bound = 2;
    double upper_bound = 5;
    std::uniform_real_distribution<double> uniform(lower_bound,upper_bound);
    std::default_random_engine re;
    double a_random_double = uniform(re);

    for (int i = 0; i < amountOfDebris; i++) {
        double mass = uniform(re);
        double radius = uniform(re);
        double x = uniform(re);
        double y = uniform(re);
        double z = uniform(re);
        debris.emplace_back(mass, radius, x, y, z);
    }
}

void Space::updateObjects()
{

    for (int i = 0; i < amountOfDebris; i++) {
        SpaceObject &obj_i = debris[i];
        for(int j = 0; j < amountOfDebris; j++) {
            if (i == j)
                continue;

            SpaceObject &obj_j = debris[j];
            obj_i.getGravitationalForceX(obj_j);
            obj_i.getGravitationalForceY(obj_j);
            obj_i.getGravitationalForceZ(obj_j);
        }
   }

    for (int i = 0; i < amountOfDebris; i++) {
        SpaceObject &obj = debris[i];
        obj.getAllGravitationalForces(time);
        obj.recordDirection();
    }

    for (int i = 0; i < amountOfDebris; i++) {
        debris[i].updateLocation();
    }

    time = time + 0.000001; // add time in nanoseconds
}



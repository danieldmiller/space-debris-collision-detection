#include "SpaceObject.h"
#include <iostream>

SpaceObject::SpaceObject(double mass0 = 0, double r0 = 0) {
	mass = mass0;
	r = r0;
}

SpaceObject::SpaceObject(const SpaceObject& rf) :  mass(rf.mass), r(rf.r){

}

SpaceObject::~SpaceObject() {

}

const SpaceObject& SpaceObject::operator=(const SpaceObject& sp)
{
	mass = sp.mass;
	r = sp.r;
}

int SpaceObject::getSpace()
{
	return 0;
}

int SpaceObject::getArea() {

	return 0;
}

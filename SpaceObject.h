#pragma once
#ifndef SPACEOBJECT_H
#define SPACEOBJECT_H

#include <iostream>

class SpaceObject {
public:
	SpaceObject(double mass0 = 0, double r0 = 0, ); // constructor
	SpaceObject(const SpaceObject& rf); // copy constructor
	~SpaceObject(); // destructor
	const SpaceObject& operator=(const SpaceObject& sp); //overloading operator for redefining objects
	static double getPi(); // calculate pi
	double getSpace() const; // get the size of the object 4/3*pi*r^3
	double getArea() const; // get the area 4*pi*r^2
	
private:
	double mass; // mass of the planetary object
	double r; // r of the planetary object
};

#endif // !SPACEOBJECT_H

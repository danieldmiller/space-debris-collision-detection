#pragma once
#ifndef SPACEOBJECT_H
#define SPACEOBJECT_H

#include <iostream>
#include "SpacePoint.h"

class SpaceObject{
	friend ostream& operator<<(ostream& out, const SpaceObject& obj); // cout overloading operator
    public:
        SpaceObject(double mass0 = 0.0, double r0 = 0.0, double x0 = 0.0, double y0 = 0.0, double z0 = 0.0); // constructor
        SpaceObject(const SpaceObject& rf); // copy constructor
        ~SpaceObject(); // destructor

        const SpaceObject& operator=(const SpaceObject& sp); //overloading operator for redefining objects

        //calculates the gravitational force of the object and saves the current value
        void updateGravitationalForce(const SpaceObject& object);
        void updateVelocity(double deltaTime);
        void updateLocation();
        SpacePoint returnPoint() const;

        //(ax-bx)2+(ay-by)2+(az-bz)2 < (ar+br)2         if true objects collide
        bool colliciondetection(const SpaceObject& check);

        //test functions to get values of objects
        double getMass() const;
        double getR() const;
        double getGX() const;

        static double getPi(); // calculate pi
        double getSpace() const; // get the size of the object 4/3*pi*r^3
        double getArea() const; // get the area 4*pi*r^2

    private:
        double mass, r, g, bigG; // mass of the planetary object r of the object, g=9,81 and bigG =6.6*10^-11
        // SpacePoint gForce; //records the gravitational force of the object in XYZ direction
        double gX;	//records the gravitational force of the object in X direction
        double gY; //records the gravitational force of the object in Y direction
        double gZ; //records the gravitational force of the object in Z direction
        double gR; //records the full gravitational force of the object
        double velocity; // records the velocity of the object
        SpacePoint location; // gets the location of the object
};

#endif // !SPACEOBJECT_H

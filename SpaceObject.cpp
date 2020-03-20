#include "SpacePoint.h"
#include "SpaceObject.h"
#include <iostream>

SpaceObject::SpaceObject(double mass0, double r0, double x0, double y0, double z0) : p(x0,y0,z0)  {
	mass = mass0;
	r = r0;
    g = 9.81;
    bigG = 0.0000000000667408;
}

SpaceObject::SpaceObject(const SpaceObject& rf) :  mass(rf.mass), r(rf.r), g(rf.g), bigG(rf.bigG), p(rf.p){

}

SpaceObject::~SpaceObject() {

}

const SpaceObject& SpaceObject::operator=(const SpaceObject& sp)
{
    if (this != &sp) {
        mass = sp.mass;
        r = sp.r;
        p = sp.p;
    }
    return *this;
}

double SpaceObject::getGravitationalForceX(const SpaceObject& x)
{
    return 0.0;
}

double SpaceObject::getGravitationalForceY(const SpaceObject& y)
{
    return 0.0;
}

double SpaceObject::getMass() const
{
    return mass;
}

double SpaceObject::getR() const
{
    return r;
}

double SpaceObject::getPi()
{
    int max = 1000;
    double sum = 0.0;
    int sign = 1;
    for (int i = 0; i < max; ++i) {
        sum += sign / (2.0 * i + 1.0);
        sign *= -1;
    }
    return 4.0 * sum;
}

double SpaceObject::getSpace() const
{
    return (4/3*getPi()*(r*r*r));
}

double SpaceObject::getArea() const
{
    return (4*getPi()*r*r);
}

ostream& operator<<(ostream& out, const SpaceObject& obj)
{
    out << obj.p << " " << obj.bigG << " " << obj.g << " " << obj.mass << " " << obj.r << " ";
    return out;
}

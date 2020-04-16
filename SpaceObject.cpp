#include "SpaceObject.h"
#include <cmath>
#include <iostream>

SpaceObject::SpaceObject(double mass0, double r0, double x0, double y0, double z0) : location(x0,y0,z0)  {
	mass = mass0;
	r = r0;
    g = 9.81;
    bigG = 0.0000000000667408;
    gY = 0.0;
    gX = 0.0;
    gZ = 0.0;
    gR = 0.0;
    velocity = 0.0;
}

SpaceObject::SpaceObject(const SpaceObject& rf) :  mass(rf.mass), r(rf.r), g(rf.g), bigG(rf.bigG), location(rf.location){
    /*gY = 0.0;
    gX = 0.0;
    gZ = 0.0;
    gR = 0.0;
    velocity = 0.0;*/
    gZ = rf.gZ;
    gY = rf.gY;
    gX = rf.gX;
    gR = rf.gR;
    velocity = rf.velocity;
}

SpaceObject::~SpaceObject() {
}

const SpaceObject& SpaceObject::operator=(const SpaceObject& sp)
{
    if (this != &sp) {
        gY = 0.0;
        gX = 0.0;
        gR = 0.0;
        velocity = 0.0;
        gY = sp.gY;
        gX = sp.gX;
        gR = sp.gR;
        velocity = sp.velocity;
        location = sp.location;
    }
    return *this;
}

void SpaceObject::updateGravitationalForce(const SpaceObject& object)
{
    SpacePoint distVector;
    double gForce, dist;

    distVector = (object.location - location);
    dist = distVector.returnDistanceValue();

    gForce = bigG * object.mass * mass / pow(dist, 2);

    distVector.normalize();
    gX = gX + distVector.getX() * gForce;
    gY = gY + distVector.getY() * gForce;
    gZ = gZ + distVector.getZ() * gForce;
}

void SpaceObject::updateLocation()
{
    SpacePoint d = location;
    double factor = velocity / gR;

    SpacePoint velocityVector(gX * factor, gY * factor, gZ * factor); // still need the z-value
    location = velocityVector + d;
}

SpacePoint SpaceObject::returnPoint() const
{
    return location;
}

bool SpaceObject::colliciondetection(const SpaceObject& check)
{
    SpacePoint comp = check.returnPoint();
    //(ax-bx)2+(ay-by)2+(az-bz)2 < (ar+br)2
    if ((pow(location.getX() - comp.getX(), 2) + pow(location.getY() - comp.getY(), 2 ) + pow(location.getZ() - comp.getZ(), 2)) <= (pow((r + check.getR()), 2)) ) {
        return true;
    }
    else {
        return false;
    }
}

void SpaceObject::updateVelocity(double deltaTime/* add const from space class that records time*/)
{
    //records the total amount of gravitational force on the object
    gR = SpacePoint(gX, gY, gZ).returnDistanceValue();

    //records velocity
    velocity = gR / mass * deltaTime;
}

/*SpacePoint SpaceObject::returnPoint()
{
    return p;
}*/

double SpaceObject::getMass() const
{
    return mass;
}

double SpaceObject::getR() const
{
    return r;
}

double SpaceObject::getGX() const
{
    return gX;
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

std::string SpaceObject::jsonNumber(double value) {
    return isnan(value) || isinf(value) ? "undefined" : std::to_string(value);
}

const ostream& SpaceObject::toJson(ostream& out) const
{
    return out << "{"
        << "\"x\":" << jsonNumber(location.getX()) << ","
        << "\"y\":" << jsonNumber(location.getY()) << ","
        << "\"z\":" << jsonNumber(location.getZ())
    << "}";
}

ostream& operator<<(ostream& out, const SpaceObject& obj)
{
    out << obj.location << " " << obj.bigG << " " << obj.g << " " << obj.mass << " " << obj.r << " ";
    return out;
}

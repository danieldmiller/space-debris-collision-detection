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
    horizontalAngle = 0.0;
    verticalAngle = 0.0;
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
    horizontalAngle = rf.horizontalAngle;
    verticalAngle = rf.verticalAngle;
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
        horizontalAngle = 0.0;
        verticalAngle = 0.0;
        gY = sp.gY;
        gX = sp.gX;
        gR = sp.gR;
        velocity = sp.velocity;
        horizontalAngle = sp.horizontalAngle;
        verticalAngle = sp.verticalAngle;
        location = sp.location;
    }
    return *this;
}

void SpaceObject::getGravitationalForceX(const SpaceObject& x)
{
   /* if (*gX != NULL) {
        double* fX0;
        fX0 = new double;
        fX0 = gX;
    }*/
    SpacePoint dist;
    double tmpDist;
    double cosin;

    dist = location - x.location;
    tmpDist = dist.returnDistanceValue();
    cosin = location.returnPointMultiple(x.location) / (location.returnDistanceValue() * x.location.returnDistanceValue());

    double fX = 0.0;
    cout << x.location << endl;
    cout << tmpDist << endl;
    cout << location.returnPointMultiple(x.location) << endl;
    cout << location.returnDistanceValue() << endl;
    cout << x.location.returnDistanceValue() << endl;
    //cout << cosin << endl;
    //cout << cos(cosin) << endl;

    fX = gX;
    fX = fX + (bigG * x.mass * mass / tmpDist * acos(cosin));
    gX = 0.0;
    gX = fX;
}

void SpaceObject::getGravitationalForceY(const SpaceObject& y)
{
    SpacePoint dist;
    double tmpDist;
    double sine;

    dist = location - y.location;
    tmpDist = dist.returnDistanceValue();
    sine = location.returnPointMultiple(y.location) / (location.returnDistanceValue() * y.location.returnDistanceValue());

    double fY;

    //cout << tmpDist << endl;

    fY = gY;
    fY = fY + (bigG * y.mass * mass / tmpDist * asin(sine));
    gY = 0.0;
    gY = fY;
}

void SpaceObject::getGravitationalForceZ(const SpaceObject& z)
{
    SpacePoint dist;
    double tmpDist;
    double sine;

    dist = location - z.location;
    tmpDist = dist.returnDistanceValue();
    sine = location.returnPointMultiple(z.location) / (location.returnDistanceValue() * z.location.returnDistanceValue());

    double fZ;

    fZ = gZ;
    fZ = fZ + (bigG * z.mass * mass / tmpDist * asin(sine));
    gZ = 0.0;
    gZ = fZ;
}

void SpaceObject::recordDirection()
{
    horizontalAngle = atan(gY / gX);
    verticalAngle = atan(gZ / gX);
}


void SpaceObject::recordNewLocation(const SpacePoint& d)
{
    SpacePoint velocityVector(sin(horizontalAngle) * velocity, cos(horizontalAngle) * velocity, d.getZ()/* temporal */); // still need the z-value
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

void SpaceObject::getAllGravitationalForces(double time0/* add const from space class that records time*/)
{
    //records the total amount of gravitational force on the object
    gR = 0.0;
    gR = sqrt((gX * gX) + (gY * gY));

    //records velocity
    velocity = 0.0;
    velocity = gR / mass * time0;
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

ostream& operator<<(ostream& out, const SpaceObject& obj)
{
    out << obj.location << " " << obj.bigG << " " << obj.g << " " << obj.mass << " " << obj.r << " ";
    return out;
}

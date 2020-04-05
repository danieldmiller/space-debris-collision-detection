
#include "SpaceObject.h"
#include "math.h"
#include <iostream>

SpaceObject::SpaceObject(double mass0, double r0, double x0, double y0, double z0) : p(x0,y0,z0)  {
	mass = mass0;
	r = r0;
    g = 9.81;
    bigG = 0.0000000000667408;
    gY = new double;
    gX = new double;
    gR = new double;
    velocity = new double;
    angle = new double;
    *gY = NULL;
    *gX = NULL;
    *gR = NULL;
    *velocity = NULL;
    *angle = NULL;
}

SpaceObject::SpaceObject(const SpaceObject& rf) :  mass(rf.mass), r(rf.r), g(rf.g), bigG(rf.bigG), p(rf.p){
    gY = new double;
    gX = new double;
    gR = new double;
    velocity = new double;
    angle = new double;
    *gY = *rf.gY;
    *gX = *rf.gX;
    *gR = *rf.gR;
    *velocity = *rf.velocity;
    *angle = *rf.angle;

}

SpaceObject::~SpaceObject() {
    delete gY;
    delete gX;
    delete gR;
    delete velocity;
    delete angle;
    gY = NULL;
    gX = NULL;
    gR = NULL;
    velocity = NULL;
    angle = NULL;
}

const SpaceObject& SpaceObject::operator=(const SpaceObject& sp)
{
    if (this != &sp) {
        gY = new double;
        gX = new double;
        gR = new double;
        velocity = new double;
        angle = new double;
        *gY = *sp.gY;
        *gX = *sp.gX;
        *gR = *sp.gR;
        *velocity = *sp.velocity;
        *angle = *sp.angle;
        p = sp.p;
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

    dist = p - x.p;
    tmpDist = dist.returnDistanceValue();
    cosin = p.returnPointMultiple(x.p) / (p.returnDistanceValue() * x.p.returnDistanceValue());

    double* fX;
    fX = new double;
    cout << x.p << endl;
    cout << tmpDist << endl;
    cout << p.returnPointMultiple(x.p) << endl;
    cout << p.returnDistanceValue() << endl;
    cout << x.p.returnDistanceValue() << endl;
    //cout << cosin << endl;
   // cout << cos(cosin) << endl;

    if (gX != NULL) {
        *fX = *gX;
        *fX = *fX + (bigG * x.mass * mass / tmpDist * acos(cosin));
    }
    else {
        *fX = bigG * x.mass * mass / tmpDist * acos(cosin);
    }
    gX = new double;

    *gX = *fX;
    delete fX;
}

void SpaceObject::getGravitationalForceY(const SpaceObject& y)
{
    SpacePoint dist;
    double tmpDist;
    double sine;

    dist = p - y.p;
    tmpDist = dist.returnDistanceValue();
    sine = p.returnPointMultiple(y.p) / (p.returnDistanceValue() * y.p.returnDistanceValue());

    double* fY;
    fY = new double;

    //cout << tmpDist << endl;

    if (*gY != NULL) {
        *fY = *gY;
        *fY = *fY + (bigG * y.mass * mass / tmpDist * asin(sine));
    }
    else {
        *fY = bigG * y.mass * mass / tmpDist * asin(sine);
    }

    gY = new double;

    *gY = *fY;
    delete fY;
    
}

void SpaceObject::recordAngle()
{
    angle = new double;
    *angle = atan(*gY / *gX);
}

void SpaceObject::recordVelocity()
{
    velocity = new double;
    *velocity = *gR / mass /* (* time)*/;
}

void SpaceObject::getGravitationalForceR()
{
    gR = new double;
    *gR = sqrt((*gX * *gX) + (*gY * *gY));
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
    return *gX;
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

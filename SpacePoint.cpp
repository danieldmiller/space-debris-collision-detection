#include "SpacePoint.h"
#include <cmath>

SpacePoint::SpacePoint(double x0, double y0, double z0)
{
	x = x0;
	y = y0;
	z = z0;
}

SpacePoint::SpacePoint(const SpacePoint& rf) : x(rf.x), y(rf.y), z(rf.z)
{
}

SpacePoint::~SpacePoint()
{
}

double SpacePoint::returnDistanceValue() const
{
	double d = sqrt(sqrt((x*x) + (y*y)) + (z*z));
	return d;
}

double SpacePoint::returnPointMultiple(const SpacePoint& mul) const
{
	double mult = x * mul.x + y * mul.y + z * mul.z;
	return mult;
}

double SpacePoint::getX() const
{
	return x;
}

double SpacePoint::getY() const
{
	return y;
}

double SpacePoint::getZ() const
{
	return z;
}

void SpacePoint::normalize() {
	double dist = returnDistanceValue();

	x /= dist;
	y /= dist;
	z /= dist;
}

const SpacePoint& SpacePoint::operator=(const SpacePoint& sp)
{
	if (this != &sp) {
		x = sp.x;
		y = sp.y;
		z = sp.z;
	}
	return *this;
}

SpacePoint SpacePoint::operator+(const SpacePoint& delta) const
{
	SpacePoint destination;
	destination.x = x + delta.x;
	destination.y = y + delta.y;
	destination.z = z + delta.z;

	return destination;
}

SpacePoint SpacePoint::operator-(const SpacePoint& alpha) const
{
	SpacePoint distance;
	distance.x = x - alpha.x;
	distance.y = y - alpha.y;
	distance.z = z - alpha.z;
	return distance;
}


std::ostream& operator<<(std::ostream& out, const SpacePoint& point)
{
	out << "(" << point.x << " , " << point.y << " , " << point.z << ")";
	return out;
}

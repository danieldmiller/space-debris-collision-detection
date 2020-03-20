#include "SpacePoint.h"


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


ostream& operator<<(ostream& out, const SpacePoint& point)
{
	out << "(" << point.x << " , " << point.y << " , " << point.z << ")";
	return out;
}

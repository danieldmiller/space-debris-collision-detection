#pragma once
#ifndef SPACEPOINT_H
#define SPACEPOINT_H

#include <iostream>

class SpacePoint {
	friend std::ostream &operator<<(std::ostream& out, const SpacePoint &point);
public:
	SpacePoint(double x0 = 0, double y0 = 0, double z0 = 0);
	SpacePoint(const SpacePoint& rf);
	~SpacePoint();

	double returnDistanceValue() const;
	double returnPointMultiple(const SpacePoint& mul) const;

	double getX() const;
	double getY() const;
	double getZ() const;
	void normalize();
	const SpacePoint& operator=(const SpacePoint& sp);
	SpacePoint operator+(const SpacePoint& delta) const; //Space object1,object2, displacement (object1 = displacement+object2)
	SpacePoint operator-(const SpacePoint& alpha) const;


private:
	double x, y, z;
};

#endif // !SPACEPOINT_H

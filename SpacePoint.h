#pragma once
#ifndef SPACEPOINt_H
#define SPACEPOINT_H

#include <iostream>

class SpacePoint {
public:
	SpacePoint(double x0 = 0, double y0 = 0, double z0 = 0);
	SpacePoint(const Space& rf);
	~SpacePoint();
	const SpacePoint& operator=(const Space& sp);
	SpacePoint operator+(const Space& delta) const; //Space object1,object2, displacement (object1 = displacement+object2)
	SpacePoint operator-(const Space& alpha) const;


private:
	double x, y, z;
};

#endif // !SPACEPOINT_H
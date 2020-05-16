#pragma once
#ifndef SPACE_WRITER_H
#define SPACE_WRITER_H

#include <iostream>
#include <fstream>
#include <vector>
#include "SpaceObject.h"

class SpaceWriter {
public:
    SpaceWriter(std::string collisionOutputPath);
	SpaceWriter(bool printObjects);

	void writeObjects(std::vector<SpaceObject> const &debris, int amountOfDebris, double time);
	void writeCollision(SpaceObject& obj1, SpaceObject& obj2, double time, bool writeToFile);

private:
    bool printObjects;
    std::ofstream collisionOutputFile;
};

#endif /* !SPACE_WRITER_H*/

#pragma once
#ifndef SPACE_WRITER_H
#define SPACE_WRITER_H

#include <iostream>
#include <fstream>
#include <vector>
#include "SpaceObject.h"

class SpaceWriter {
public:
	SpaceWriter(bool printObjects);

	void writeObjects(std::vector<SpaceObject> const &debris, int amountOfDebris, double time);

private:
    bool printObjects;
};

#endif /* !SPACE_WRITER_H*/

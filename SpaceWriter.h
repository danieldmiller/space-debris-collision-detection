#pragma once
#ifndef SPACE_WRITER_H
#define SPACE_WRITER_H

#include <iostream>
#include <fstream>
#include <vector>
#include "SpaceObject.h"

class SpaceWriter {
public:
	SpaceWriter(std::string filename);
	~SpaceWriter();

	void writeObjects(std::vector<SpaceObject> const &debris, int amountOfDebris, double time);

private:
    ofstream outputFile;
    bool hasWrittenAlready = false;
};

#endif /* !SPACE_WRITER_H*/

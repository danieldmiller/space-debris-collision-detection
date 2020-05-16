#include <cmath>
#include "SpaceWriter.h"
#include <iostream>
#include <fstream>

SpaceWriter::SpaceWriter(std::string collisionOutputPath) {
    collisionOutputFile.open(collisionOutputPath);
};

SpaceWriter::SpaceWriter(bool _printObjects) {
	printObjects = _printObjects;
}

void SpaceWriter::writeObjects(std::vector<SpaceObject> const &debris, int amountOfDebris, double time) {
	if (!printObjects)
		return;

	std::cout << "{\"time\":" << time << ",\"objects\":[";
	for (int i = 0; i < amountOfDebris; i++) {
		SpaceObject const &obj = debris[i];
		obj.toJson(std::cout);

		if (i != amountOfDebris - 1)
			std::cout << ",";
	}
	std::cout << "]}" << std::endl;
}

void SpaceWriter::writeCollision(SpaceObject& obj1, SpaceObject& obj2, double time, bool writeToFile) {
    if (writeToFile) {
        collisionOutputFile << "{\"time\":" << time << ",\"objects\":[";
        obj1.toJson(collisionOutputFile);
        collisionOutputFile << ",";
        obj2.toJson(collisionOutputFile);
        collisionOutputFile << "]}" << std::endl;
    }
}
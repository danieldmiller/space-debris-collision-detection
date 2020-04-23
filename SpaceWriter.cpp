#include <cmath>
#include "SpaceWriter.h"

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

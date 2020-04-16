#include <cmath>
#include "SpaceWriter.h"

SpaceWriter::SpaceWriter(std::string filename) {
	outputFile.open(filename, ios::out | ios::trunc);
	outputFile << "window.spaceHistory = [";
}

SpaceWriter::~SpaceWriter() {
	outputFile << "]";
	outputFile.close();
}

void SpaceWriter::writeObjects(std::vector<SpaceObject> const &debris, int amountOfDebris, double time) {
	if (hasWrittenAlready)
		outputFile << ",";
	else
		hasWrittenAlready = true;

	outputFile << "{time:" << time << ",objects:[";
	for (int i = 0; i < amountOfDebris; i++) {
		SpaceObject const &obj = debris[i];
		obj.toJson(outputFile);

		if (i != amountOfDebris - 1)
			outputFile << ",";
	}
	outputFile << "]}";
}

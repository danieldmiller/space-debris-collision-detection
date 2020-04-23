#include "SpaceObject.h"
#include "Space.h"
#include "SpacePoint.h"

#include <stdio.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK ,__FILE__, __LINE__)
#define new DBG_NEW
#endif
#endif // _DEBUG

#include <getopt.h>
#include <iostream>

using namespace std;

bool printObjects = false;
int objectsToSpawn = 20;
int cyclesToCompute = 5000;
bool interactive = false;

void printHelp(int exitCode) {
    cout <<
        "-p --print-objects:    Print the objects information at each cycle" << endl <<
        "-o --objects <n>:      Number of objects to spawn" << endl <<
        "-c --cycles <n>:       Number of cycles to compute" << endl <<
        "-i --interactive:      Wait user input before computing next cycle" << endl <<
        "-h --help:             Show help" << endl;
    exit(exitCode);
}

void processArgs(int argc, char** argv) {
    const char* const short_opts = "po:c:ih";
    const option long_opts[] = {
            {"print-objects", no_argument, nullptr, 'p'},
            {"objects", required_argument, nullptr, 'o'},
            {"cycles", required_argument, nullptr, 'c'},
            {"interactive", no_argument, nullptr, 'i'},
            {"help", no_argument, nullptr, 'h'},
            {nullptr, no_argument, nullptr, 0}
    };

    while (true) {
        const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);

        if (opt == -1)
            break;

        switch (opt) {
	        case 'p':
	            printObjects = true;
	            break;
	        case 'o':
	            objectsToSpawn = stoi(optarg);
	            break;
	        case 'c':
	            cyclesToCompute = stoi(optarg);
	            break;
	        case 'i':
	            interactive = true;
	            break;
	        case 'h':
	            printHelp(0);
	            break;
	        default: // Unrecognized option
	            printHelp(1);
	            break;
        }
    }
}

int main (int argc, char *argv[]) {
	processArgs(argc, argv);
	cout << objectsToSpawn << " objects during " << cyclesToCompute << " cycles." << endl;

    Space space(objectsToSpawn, printObjects);
    space.initializeObjects();

	for (int i = 0; i < cyclesToCompute; i++) {
		if (interactive) {
			string userInput;
			cin >> userInput;
		}
		space.updateObjects();
	}

    cout << "Done updating objects" << endl;
    return EXIT_SUCCESS;
};

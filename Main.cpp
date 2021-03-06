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
#include <random>

using namespace std;

bool printObjects = false;
int threadCount = 1;
int seed = random_device()();
int objectsToSpawn = 20;
int cyclesToCompute = 5000;
bool interactive = false;

void printHelp(int exitCode) {
    cout <<
        "-t --thread-count <n>  Number of threads to utilize (1=serial execution)" << endl <<
        "-s --seed <seed>       A seed to initialize the random number generator" << endl <<
        "-p --print-objects:    Print the objects information at each cycle" << endl <<
        "-o --objects <n>:      Number of objects to spawn" << endl <<
        "-c --cycles <n>:       Number of cycles to compute" << endl <<
        "-i --interactive:      Wait user input before computing next cycle" << endl <<
        "-h --help:             Show help" << endl;
    exit(exitCode);
}

int processThreadCount(int threadCount) {
    if (threadCount < 1) return 1;
    if (threadCount > std::thread::hardware_concurrency()) return std::thread::hardware_concurrency();
    return threadCount;
}

void processArgs(int argc, char** argv) {
    const char* const short_opts = "t:s:po:c:ih";
    const option long_opts[] = {
            {"thread-count", required_argument, nullptr, 't'},
            {"seed", required_argument, nullptr, 's'},
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
            case 't':
                try {
                    threadCount = stoi(optarg);
                    threadCount = processThreadCount(threadCount);
                } catch(std::invalid_argument& e){
                    std::cout << e.what() << std::endl;
                }
                break;
            case 's':
                try {
                    seed = stoi(optarg);
                } catch(std::invalid_argument& e){
                    std::cout << e.what() << std::endl;
                }
                break;
	        case 'p':
	            printObjects = true;
	            break;
	        case 'o':
	            try {
                    objectsToSpawn = stoi(optarg);
                }  catch(std::invalid_argument& e){
                    std::cout << e.what() << std::endl;
                }
	            break;
	        case 'c':
                try {
                    cyclesToCompute = stoi(optarg);
                } catch(std::invalid_argument& e){
                    std::cout << e.what() << std::endl;
                }
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
    auto start = std::chrono::system_clock::now();
	cout << objectsToSpawn << " objects during " << cyclesToCompute << " cycles." << endl;

    Space space(objectsToSpawn, printObjects, threadCount, seed);
    space.initializeObjects();
	for (int i = 0; i < cyclesToCompute; i++) {
		if (interactive) {
			string userInput;
			cin >> userInput;
		}

        if (threadCount == 1) {
            space.updateObjects();
        } else {
            space.updateObjectsThreads();
        }
	}
    cout << "Done updating objects" << endl;

    auto end = std::chrono::system_clock::now();
    double elapsedSeconds = std::chrono::duration_cast<std::chrono::duration<double> >(end - start).count();
    cout << "Program run time: " << elapsedSeconds << " seconds" << std::endl;
    cout << "Seed: " << seed << endl;
    return EXIT_SUCCESS;
};

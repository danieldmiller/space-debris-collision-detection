#include "Space.h"
#include "SpaceObject.h"
#include <random>

double Space::time = 0.0;
double deltaTime = 3600 * 24; // 1 day

Space::Space(int amountOfDebris0, bool printObjects)
{
	amountOfDebris = amountOfDebris0;
    output = new SpaceWriter(printObjects);
    std::string collisionOutputPath = "collisions.json";
    collisionOutput = new SpaceWriter(collisionOutputPath);

	//initialize the limits for the space
	//for(int i = 0; i < 8 ; i++){
	//do something with limit[7]
	//}
}

Space::Space(const Space& rf) {
	amountOfDebris = rf.amountOfDebris;
	debris = rf.debris;
    output = rf.output;
    collisionOutput = rf.output;
}

Space::~Space()
{
    delete output;
    delete collisionOutput;
}

void Space::initializeObjects()
{
    std::uniform_real_distribution<double> uniformMass(3, 5);
    std::uniform_real_distribution<double> uniformRadius(2, 5);
    std::uniform_real_distribution<double> uniformPosition(-500, 500);
    std::random_device rd;
    std::default_random_engine re(rd());

    singleP.startClock();

    for (int i = 0; i < amountOfDebris; i++) {
        double mass = pow(10, uniformMass(re));
        double radius = uniformRadius(re);
        double x = uniformPosition(re);
        double y = uniformPosition(re);
        double z = uniformPosition(re);
        debris.emplace_back(mass, radius, x, y, z);
    }

    singleP.endClock();
    std::cout << "single initialization time: " << singleP.returnSingleTime() << "ns" << std::endl;
    output->writeObjects(debris, amountOfDebris, time);
}

void Space::updateObjects()
{
    singleP.startClock();

    for (int i = 0; i < amountOfDebris; i++) {
        SpaceObject& obj_i = debris[i];
        for (int j = 0; j < amountOfDebris; j++) {
            SpaceObject& obj_j = debris[j];

            if (i == j)
                continue;
            if (obj_i.detectCollision(obj_j)) {
                collisionOutput->writeCollision(obj_i, obj_j, time, true);

                // Remove collided objects
                debris.erase(debris.begin() + i);
                debris.erase(debris.begin() + j-1); // j-1 as list shrinks by 1 above
                amountOfDebris -= 2;
                continue;
            }

            obj_i.updateGravitationalForce(debris[j]);
        }
    }

    for (int i = 0; i < amountOfDebris; i++) {
        SpaceObject& obj = debris[i];
        obj.updateVelocity(deltaTime);
        obj.updateLocation();
    }

    singleP.endClock();
    std::cout << "single update time: " << singleP.returnSingleTime() << "ns" << std::endl;

    time = time + deltaTime;
    output->writeObjects(debris, amountOfDebris, time);
}

void Space::updateObjectsThreads()
{
    int threadBegin = 0;
    int threadEnd = 0;

    multiP.startClock();

    for (int i = 0; i < nThreads; ++i) {
        threadBegin = (i / nThreads) * amountOfDebris;
        threadEnd = ((i + 1) / nThreads) * amountOfDebris;
        threads.push_back(std::thread([threadBegin, threadEnd, this]() {

            this->updateForceForThreads(threadBegin, threadEnd);
            }));

    }
    for (auto& thread : threads) {
        thread.join();
    }
    threads.clear();
    multiP.endClock();

    //calculates the average that a single thread takes to run
    std::cout << "parallel update time: " << multiP.returnParallelTime() << "ns" << std::endl;

    time = time + deltaTime;
}

void Space::updateForceForThreads(int begin, int end)
{

    m.lock();
    for (int i = begin; i < end; i++) {
        SpaceObject& obj_i = debris[i];
        for (int j = begin; j < end; j++) {
            SpaceObject& obj_j = debris[j];
            if (i == j)
                continue;
            if (obj_i.detectCollision(obj_j)) {
                collisionOutput->writeCollision(obj_i, obj_j, time, true);
                continue;
            }
            obj_i.updateGravitationalForce(debris[j]);
        }
    }

    for (int i = begin; i < end; i++) {
        SpaceObject& obj = debris[i];
        obj.updateVelocity(deltaTime);
        obj.updateLocation();
    }
    m.unlock();
}



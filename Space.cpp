#include "Space.h"
#include <thread>
#include "SpaceObject.h"
#include <random>
#include <set>

double Space::time = 0.0;
double deltaTime = 3600 * 24; // 1 day

void Space::task(int number) {
    int s = 0;
    for(int i=0; i<number; i++) {
        s = s + 1;
    }
}

Space::Space(int _amountOfDebris, bool printObjects, int _threadCount) {
	amountOfDebris = _amountOfDebris;
    threadCount = _threadCount;

    output = new SpaceWriter(printObjects);
    std::string collisionOutputPath = "collisions.json";
    collisionOutput = new SpaceWriter(collisionOutputPath);
}

Space::Space(const Space& rf) {
	amountOfDebris = rf.amountOfDebris;
    threadCount = rf.threadCount;
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

            int a = i+j;

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
    multiP.startClock();
    std::set<int> collisionIndexes;

    for (int i = 0; i < threadCount; ++i) {
        int threadBegin = (float(i) / float(threadCount)) * amountOfDebris;
        int threadEnd = (float(i+1)/float(threadCount)) * amountOfDebris - 1;
        std::thread thread = std::thread(&Space::updateForceForThreads, this, threadBegin, threadEnd, collisionIndexes);    
        threads.push_back(std::move(thread));
    }

    for (std::thread & thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    threads.clear();

    // Remove collided objects from debris vector after threads have joined
    for (auto it = collisionIndexes.begin(); it != collisionIndexes.end(); ++it) {
        std::cout << *it << std::endl;
        debris.erase(debris.begin() + *it);
        amountOfDebris--;
    }

    for (int i = 0; i < amountOfDebris; i++) {
        SpaceObject& obj = debris[i];
        obj.updateVelocity(deltaTime);
        obj.updateLocation();
    }

    multiP.endClock();

    //calculates the average that a single thread takes to run
    std::cout << "parallel update time: " << multiP.returnParallelTime() << "ns" << std::endl;

    time = time + deltaTime;
    output->writeObjects(debris, amountOfDebris, time);
}

void Space::updateForceForThreads(int begin, int end, std::set<int> collisionIndexes)
{
    for (int i = begin; i <= end; i++) {
        SpaceObject& obj_i = debris[i];
        for (int j = 0; j < amountOfDebris; j++) {
            SpaceObject& obj_j = debris[j];
            int a = i+j;
            if (i == j)
                continue;
            if (obj_i.detectCollision(obj_j)) {
                m.lock();
                collisionOutput->writeCollision(obj_i, obj_j, time, true);
                collisionIndexes.insert(i);
                collisionIndexes.insert(j);
                m.unlock();
                continue;
            }
            obj_i.updateGravitationalForce(debris[j]);
        }
    }
}


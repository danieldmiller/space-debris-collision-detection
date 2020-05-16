#include "Space.h"
#include "SpaceObject.h"
#include <random>

double Space::time = 0.0;
double deltaTime = 3600 * 24; // 1 day

Space::Space(int amountOfDebris0, bool printObjects)
{
	amountOfDebris = amountOfDebris0;
    output = new SpaceWriter(printObjects);

	//initialize the limits for the space
	//for(int i = 0; i < 8 ; i++){
	//do something with limit[7]
	//}
}

Space::Space(const Space& rf) {
	amountOfDebris = rf.amountOfDebris;
	debris = rf.debris;
    output = rf.output;
}

Space::~Space()
{
    delete output;
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

void Space::initializeObjectsThreads()
{

    int threadBegin = 0;
    int threadEnd = 0;
    multiP.startClock();

    for (int i = 0; i < nThreads; ++i) {
        threadBegin = (i / nThreads) * amountOfDebris;
        threadEnd = ((i + 1) / nThreads) * amountOfDebris;
        threads.push_back(std::thread([threadBegin, threadEnd, this]() {
            this->initializeObjectsForThreads(threadBegin, threadEnd);
            }));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    threads.clear();

    multiP.endClock();

    //calculates the average that a single thread takes to run
    std::cout << "parallel initialization time: " << multiP.returnParallelTime() << "ns" << std::endl;
}


void Space::updateObjects()
{
    singleP.startClock();

    for (int i = 0; i < amountOfDebris; i++) {
        SpaceObject& obj_i = debris[i];
        for (int j = 0; j < amountOfDebris; j++) {
            if (i == j)
                continue;

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


void Space::initializeObjectsForThreads(int begin, int end)
{
    double lower_bound = 2;
    double upper_bound = 5;
    std::uniform_real_distribution<double> uniform(lower_bound, upper_bound);
    std::uniform_real_distribution<double> uniformPosition(-1, 1);
    std::default_random_engine re;
    //m.lock();
    for (int i = begin; i < end; i++) {
        double mass = uniform(re) * 100000;
        double radius = uniform(re);
        double x = uniformPosition(re) * 10 * amountOfDebris;
        double y = uniformPosition(re) * 10 * amountOfDebris;
        double z = uniformPosition(re) * 10 * amountOfDebris;
        debris.emplace_back(mass, radius, x, y, z);
    }
    //std::cout << std::thread::get_id() << std::endl;
   // m.unlock();
}

void Space::updateForceForThreads(int begin, int end)
{
    double deltaTime = 100000;
    m.lock();
    for (int i = begin; i < end; i++) {
        SpaceObject& obj_i = debris[i];
        for (int j = begin; j < end; j++) {
            if (i == j)
                continue;

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



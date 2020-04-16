#include "Space.h"
#include "SpaceObject.h"
#include <random>

double Space::time = 0.0;

Space::Space(int amountOfDebris0)
{
	amountOfDebris = amountOfDebris0;
    output = new SpaceWriter("web3d/space-history.js");
	// debris = new SpaceObject[amountOfDebris];

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
    double lower_bound = 2;
    double upper_bound = 5;
    std::uniform_real_distribution<double> uniform(lower_bound,upper_bound);
    std::uniform_real_distribution<double> uniformPosition(-1, 1);
    std::default_random_engine re;

    singleP.startClock();

    for (int i = 0; i < amountOfDebris; i++) {
        double mass = uniform(re) * 100000;
        double radius = uniform(re);
        double x = uniformPosition(re) * 10 * amountOfDebris;
        double y = uniformPosition(re) * 10 * amountOfDebris;
        double z = uniformPosition(re) * 10 * amountOfDebris;
        debris.emplace_back(mass, radius, x, y, z);
    }

    singleP.endClock();
    std::cout << "single initialization" << singleP << std::endl;
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
            for (int i = threadBegin; i < threadEnd; i++) {
                this->initializeObjectsForThreads(threadBegin, threadEnd);
            }

            }));

    }
    for (auto& thread : threads) {
        thread.join();
    }

    multiP.endClock();
    std::cout << "parallel initialization" << multiP << std::endl;
}


void Space::updateObjects()
{
    

    double deltaTime = 100000;


    singleP.startClock();

    for (int i = 0; i < amountOfDebris; i++) {
        SpaceObject &obj_i = debris[i];
        for(int j = 0; j < amountOfDebris; j++) {
            if (i == j)
                continue;

            obj_i.updateGravitationalForce(debris[j]);
        }
   }

    for (int i = 0; i < amountOfDebris; i++) {
        SpaceObject &obj = debris[i];
        obj.updateVelocity(deltaTime);
        obj.updateLocation();
    }

    singleP.endClock();
    std::cout << "single update" << singleP << std::endl;

    time = time + deltaTime;
    output->writeObjects(debris, amountOfDebris, time);
}

void Space::updateObjectsThreads()
{
   
    double deltaTime = 100000;

    int threadBegin = 0;
    int threadEnd = 0;
    
    multiP.startClock();
    
    for (int i = 0; i < nThreads; ++i) {
        threadBegin = (i / nThreads) * amountOfDebris;
        threadEnd = ((i + 1) / nThreads) * amountOfDebris;
        threads.push_back(std::thread([threadBegin, threadEnd, this]() {
            for (int i = threadBegin; i < threadEnd; i++) {
                this->updateForceForThreads(threadBegin, threadEnd);
            }

            }));

    }
    for (auto& thread : threads) {
        thread.join();
    }
    multiP.endClock();
    std::cout << "paralell update" << multiP << std::endl;
    
    time = time + deltaTime;
}


void Space::initializeObjectsForThreads(int begin, int end)
{
    double lower_bound = 2;
    double upper_bound = 5;
    std::uniform_real_distribution<double> uniform(lower_bound, upper_bound);
    std::uniform_real_distribution<double> uniformPosition(-1, 1);
    std::default_random_engine re;

    for (int i = begin; i < end; i++) {
        double mass = uniform(re) * 100000;
        double radius = uniform(re);
        double x = uniformPosition(re) * 10 * amountOfDebris;
        double y = uniformPosition(re) * 10 * amountOfDebris;
        double z = uniformPosition(re) * 10 * amountOfDebris;
        debris.emplace_back(mass, radius, x, y, z);
    }
}

void Space::updateForceForThreads(int begin, int end)
{
    double deltaTime = 100000;
    m.lock();
    for (int i = begin; i < end; i++) {
        SpaceObject &obj_i = debris[i];
        for (int j = begin; j < end; j++) {
            if (i == j)
                continue;

            obj_i.updateGravitationalForce(debris[j]);
        }
    }

    for (int i = begin; i < end; i++) {
        SpaceObject &obj = debris[i];
        obj.updateVelocity(deltaTime);
        obj.updateLocation();
    }
    m.unlock();
}



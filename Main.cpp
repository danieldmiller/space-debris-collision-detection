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

int main (/*int argc, char *argv[]*/) {
    Space space(20);
    space.initializeObjects();
    for(int i = 0; i < 5000; i++)
    	space.updateObjects();
    std::cout << "Done updating objects" << std::endl;
    return EXIT_SUCCESS;
};

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
    Space space;
    space.initializeObjects();
    space.updateObjects();
    cout << "Done updating objects" << endl;
    return EXIT_SUCCESS;
};
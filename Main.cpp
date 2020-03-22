#include "SpacePoint.h"

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK ,__FILE__, __LINE__)
#define new DBG_NEW
#endif
#endif // _DEBUG

int main (/*int argc, char *argv[]*/) {
    SpaceObject obj1(2, 3, 2.1, 2.2, 2.3);
    SpaceObject obj2(2, 3, 4.1, 4.2, 4.3);
    SpaceObject obj3(2, 3, 5.1, 2.5, -3.2);
    //SpaceObject obj2[2] = {(2, 3, 3.2, 3.4, 3.1), (2, 3, 4.1,4.2,4.3)};
    //for (int i = 0; i < 2; i++) {
     //   obj1.getGravitationalForceX(obj2[i]);
   // }
    obj1.getGravitationalForceX(obj2);
    obj1.getGravitationalForceX(obj3);
    cout << obj1.getGX() << endl;
    /*SpacePoint ob2(2.3, 2.3, 2.3);
    SpacePoint ob3;
    ob3 = ob2 - ob1;
    cout << ob3;*/
    cout << obj1;
    return EXIT_SUCCESS;

}
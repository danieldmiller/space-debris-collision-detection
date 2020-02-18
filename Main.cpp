#include "SpacePoint.h"

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK ,__FILE__, __LINE__)
#define new DBG_NEW
#endif
#endif // _DEBUG

int main (/*int argc, char *argv[]*/) {
    SpacePoint ob1(1.2, 1.2, 1.2);
    SpacePoint ob2(2.3, 2.3, 2.3);
    //SpacePoint ob3;
    //ob3 = ob2 - ob1;
    //cout << ob3;
    return 0;

}
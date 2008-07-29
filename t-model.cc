#include <iostream>
#include "lvvmath.h"

using namespace std;

int main () {
    double xx[] = {    1.,   2.,   3.,   4.,   5.};
    double yy[] = {   19.,  11.,  25.,  49.,   66.};  

    const int   N       = sizeof xx / sizeof *xx;
    lvv::Model<> model(xx,yy, N, 3);
    model.print();

	return 0;
}

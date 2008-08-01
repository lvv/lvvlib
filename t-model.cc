#include <iostream>
#include <iomanip>
using namespace std;

#include  "model.h"
using namespace lvv;

int main (int argc, char **argv) {

    double X[] = {1      , 2     , 3     , 4     , 5  }   ; 
    double Y[] = { 0.0645, 0.1649, 0.2814, 0.4427, 0.7616}; 

    //double X[] = {1, 2, 3, 4  , 5  };
    //double Y[] = {0, 0, 0, 0.2, 0.9};

    //double X[] = {1, 2, 3, 4  , 5  };
    //double Y[] = {0.1, 0.3, 0.4, 0.7, 0.9};
    int n = sizeof(X)/(sizeof(*X));
	Model  m(X, Y, n, 4);

	m.print("t-model.cc");

	return 0;
}

#include <iostream>
#include <iomanip>
#include <lvv/array.h>
using lvv::array;

using namespace std;

#include  "cdf-model.h"
using namespace lvv;

int main (int argc, char **argv) {

    double X[] = {1      , 2     , 3     , 4     , 5  }   ; 
    //double Y[] = { +0.0259 ,0.0693 ,0.1966 ,0.4537 ,0.8006 }; 

    //double Y[] = { 0.0645, 0.1649, 0.2814, 0.4427, 0.7616}; 
    //double Y[] = { +0.0662 ,0.2824 ,0.6288 ,0.8986 ,0.9861 }; 
    //double Y[] = {0, 0, 0, 0.2, 0.9};
    //double Y[] = {0.1, 0.3, 0.4, 0.7, 0.9};
    int n = sizeof(X)/(sizeof(*X));
	Model<4>  m(X, Y, n);
	Model<4>  m_empty;  // to test default dtor/ctor

	m.print("t-model.cc");

	return 0;
}

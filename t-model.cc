#include <iostream>
#include <iomanip>
using namespace std;

#include  "model.h"
using namespace lvv;

int main (int argc, char **argv) {

    double X[] = {1, 2, 3, 4  , 5  };
    double Y[] = {0, 0, 0, 0.2, 0.9};
    //double X[] = {1, 2, 3, 4  , 5  };
    //double Y[] = {0.1, 0.3, 0.4, 0.7, 0.9};
    int n = sizeof(X)/(sizeof(*X));
	Model<>  m(X, Y, n, 4);

    cout 
	<< "# :gnuplot: set key bottom; set ytics 0,0.5; set yrange [-0.1:1.1]; set xrange [0:6]; set grid; plot \"pipe\" using 1:2 title \"data\" with points 17 , \"pipe\" using 1:3 title \"model\" with lines 3, \"pipe\" using 4:2 title \"inv x(y)\" with point 4;\n"
	<< "#  X		Y		Y-mod		X-inv\n" << fixed << showpos ;

    for (int i=0;  i<n; ++i)                 cout << X[i]        << "\t" << Y[i]                                                       << endl;
    for (double x=0.0;  x<=6.0; x+=0.2 )     cout << x           << "\t" << "\" \"\t\t"  << m.estimate(x)                              << endl;
    for (double y=0.0;  y<=1.0; y+=0.05)     cout << "\" \"\t\t" << y    << "\t"         << "\" \"\t\t"       << m.inverse_estimate(y) << endl;

	return 0;
}

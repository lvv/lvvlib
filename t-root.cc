#include <iostream>
#include <iomanip>
using namespace std;

//#include <poly.h>
//using namespace o2scl;
//#include <gsl/gsl_poly.h> 

#include  "lvvlib.h"
#include  "model.h"
using namespace lvv;


int main (int argc, char **argv) {

		#define poly_order 4

		double X[] = {1, 2, 3, 4  , 5  };
		double Y[] = {0, 0, 0, 0.2, 0.9};
									//double X[] = {1, 2, 3, 4  , 5  };
									//double Y[] = {0.1, 0.3, 0.4, 0.7, 0.9};

		int n = sizeof(X)/(sizeof(*X));
		Model  m(X, Y, n, poly_order);

		cout 
		<< "# :gnuplot: set key bottom; set ytics 0,0.5; set yrange [-0.1:1.1]; set xrange [0:6]; set grid; plot \"pipe\" using 1:2 title \"data\" with points 17 , \"pipe\" using 1:3 title \"model\" with lines 3, \"pipe\" using 4:2 title \"inv x(y)\" with point 4;\n"
		<< "#  X		Y		Y-mod		X-inv\n" << fixed << showpos ;

		for (int i=0;  i<n; ++i)                 cout << X[i]        << "\t" << Y[i]                                                       << endl;
		for (double x=-1.;  x<=6.0; x+=0.2 )     cout << x           << "\t" << "\" \"\t\t"  << m.estimate(x)                              << endl;
		for (double y=0.0;  y<=1.0; y+=0.05)     cout << "\" \"\t\t" << y    << "\t"         << "\" \"\t\t"       << m.inverse_estimate(y) << endl;

									///////////////////////////////////////////////////////
									/*
									#include <complex>
									std::complex<double>   	 root[poly_order];
									double co[poly_order];
									co [3] =  gsl_vector_get(m.c, 0);
									co [2] =  gsl_vector_get(m.c, 1);
									co [1] =  gsl_vector_get(m.c, 2);
									co [0] =  gsl_vector_get(m.c, 3);

									gsl_poly_real_coeff  poly;
									poly.solve_rc(poly_order, co, root);
									for (int i=0;  i<poly_order-1; ++i)                 cerr << root[i] << endl;
									*/

		///////////////////////////////////////////////////////
		double y_var = 0.5;
		double c0_save = gsl_vector_get(m.c,0);
		gsl_vector_set(m.c, 0, c0_save-y_var);

		double z[(poly_order-1)*2];

		//  solve
		gsl_poly_complex_workspace * w = gsl_poly_complex_workspace_alloc (poly_order);                                                                                                            
		gsl_poly_complex_solve (gsl_vector_ptr(m.c,0), poly_order, w, z);                                                                                                                   
		gsl_poly_complex_workspace_free (w);                                                                                                                   

		//  select root
		bool got_root=false;
		double real_root;
		for (int i = 0; i < poly_order-1; i++)   {
			//printf ("z%d = %+.18f i%+.18f\n", i, z[2*i], z[2*i+1]);              PR3 (X[0], z[2*i], X[n-1]);
			if (z[2*i+1] ==  0.00000) {              //*imag part
				if ( X[0] <= z[2*i]  &&  z[2*i] <= X[n-1]) {
					real_root = z[2*i];
					got_root = true;
				}
			}
		};

		if (got_root)
			cerr << "the root = " << real_root <<endl;
		else
			cerr << "root not found\n";

		return 0;
}

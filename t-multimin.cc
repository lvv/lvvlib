#include <stdlib.h>
#include <iostream>
using std::cerr;
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_multimin.h>
#include "lvvlib.h"

/* Paraboloid centered on (p[0],p[1]), with  scale factors (p[2],p[3]) and minimum p[4] */

double my_f(const gsl_vector * v, void *params) {

	double  x, y;
	double *p = (double *) params;

	x = gsl_vector_get(v, 0);
	y = gsl_vector_get(v, 1);

	return p[2] * (x - p[0]) * (x - p[0]) + p[3] * (y - p[1]) * (y - p[1]) + p[4];
}

class FMinimizer {  public:
	FMinimizer (int N, double F(const gsl_vector*, void *), gsl_vector *x, void *p,  gsl_vector *ss,  bool _trace=false)
	:	T (gsl_multimin_fminimizer_nmsimplex), trace(_trace)
	{
		minex_func.n = N;
		minex_func.f = F;
		minex_func.params = p;

		minimizer = gsl_multimin_fminimizer_alloc(T, N);
		gsl_multimin_fminimizer_set(minimizer, &minex_func, x, ss);
		if (trace)   cout << "#  minimizer: "  <<  gsl_multimin_fminimizer_name (minimizer)  <<  endl;
	}


	~FMinimizer () { gsl_multimin_fminimizer_free(minimizer); }


	void   iterate (double characteristic_size, int max_iter) {
		int	test_status=GSL_CONTINUE;			// test_status:  GSL_SUCCESS==0; GSL_CONTINUE==-2; 

		for  ( int iter=0;  iter<max_iter && (test_status==GSL_CONTINUE);   ++iter )   {

			int  iterate_status = gsl_multimin_fminimizer_iterate(minimizer);

			if (iterate_status) {
				cerr << "error: FMinimizer: in gsl_multimin_fminimizer_iterate()\n";
				break;
			}

			double size = gsl_multimin_fminimizer_size(minimizer);
			test_status = gsl_multimin_test_size(size, characteristic_size);
			if (test_status == GSL_SUCCESS && trace )    cout  << "converged to minimum at\n";

			if (trace) FMT("%5d %10.5d %10.5d %10.5d %10.5d\n") %iter %gsl_vector_get(minimizer->x, 0)  %gsl_vector_get(minimizer->x, 1)  %(minimizer->fval)  %size;
		}
	}

	const gsl_multimin_fminimizer_type *T;
	gsl_multimin_fminimizer 	*minimizer;
	gsl_multimin_function		minex_func;
	bool				trace;
 };

int main(void)  {


	/* Starting point */
	gsl_vector *x = gsl_vector_alloc(2);
	gsl_vector_set(x, 0, 5.0);
	gsl_vector_set(x, 1, 7.0);

	/* Set initial step sizes to 1 */
	gsl_vector *ss = gsl_vector_alloc(2);
	gsl_vector_set_all(ss, 1.0);

	double  par[5] = { 1.0, 2.0, 10.0, 20.0, 30.0 };
	cout << 
		"# :gnuplot:  set view map; set dgrid3d; set key off; set contour surface; set cntrparam levels 20;   set isosample 20;"
		"set zrange  [0:1000];  p0=1; p1=2; p2=10; p3=20; p4=30;"
		"splot [-3:10] [-3:10]"
			"p2*(x - p0)*(x-p0) + p3*(y-p1)*(y-p1) + p4,"
			"\"pipe\" using 2:3:4:1 with labels;\n"
			"# X, Y,  F(x),  step_size\n";


	FMinimizer fm(2, my_f, x, par, ss, true);	
	fm.iterate(1e-2, 100);
	gsl_vector_free(x);
	gsl_vector_free(ss);

	return 0;
}

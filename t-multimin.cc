#include <stdlib.h>

#include <iostream>
using namespace std;

#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_multimin.h>

#include "lvvlib.h"


/* Paraboloid centered on (p[0],p[1]), with  scale factors (p[2],p[3]) and minimum p[4] */

double
my_f (const gsl_vector *v, void *params) {
  double x, y;
  double *p = (double *)params;
  
  x = gsl_vector_get(v, 0);
  y = gsl_vector_get(v, 1);
 
  return p[2] * (x - p[0]) * (x - p[0]) + p[3] * (y - p[1]) * (y - p[1]) + p[4]; 
}

int main(void) {

		double  par[5] = { 1.0, 2.0, 10.0, 20.0, 30.0 };

		const gsl_multimin_fminimizer_type *T = gsl_multimin_fminimizer_nmsimplex;
		gsl_multimin_fminimizer *s = NULL;
		gsl_vector *ss, *x;
		gsl_multimin_function minex_func;

		size_t  iter = 0;
		int     status;
		double  size;

		/* Starting point */
		x = gsl_vector_alloc(2);
		gsl_vector_set(x, 0, 5.0);
		gsl_vector_set(x, 1, 7.0);

		/* Set initial step sizes to 1 */
		ss = gsl_vector_alloc(2);
		gsl_vector_set_all(ss, 1.0);

		/* Initialize method and iterate */
		minex_func.n = 2;
		minex_func.f = &my_f;
		minex_func.params = (void *) &par;

		s = gsl_multimin_fminimizer_alloc(T, 2);
		gsl_multimin_fminimizer_set(s, &minex_func, x, ss);

		cout << "# :gnuplot:  set view map; set dgrid3d; set key off; set contour surface; set cntrparam levels 20;   set isosample 20; set zrange  [0:1000];"
				"p0=1; p1=2; p2=10; p3=20; p4=30;"
				"splot [-3:10] [-3:10]"
					"p2*(x - p0)*(x-p0) + p3*(y-p1)*(y-p1) + p4,"
					"\"pipe\" using 2:3:4:1 with labels;\n"
				"# X, Y,  F(x),  step_size\n";
		do {
				iter++;
				status = gsl_multimin_fminimizer_iterate(s);

				if (status) break;

				size = gsl_multimin_fminimizer_size(s);
				status = gsl_multimin_test_size(size, 1e-2);

				if (status == GSL_SUCCESS)   printf("converged to minimum at\n");

				FMT("%5d %.5f %.5f %10.5f %10.5f\n") %iter %gsl_vector_get(s->x, 0)  %gsl_vector_get(s->x, 1)  %s->fval  %size;

		}  while (status == GSL_CONTINUE && iter < 100);

		gsl_vector_free(x);
		gsl_vector_free(ss);
		gsl_multimin_fminimizer_free(s);

		return status;
}

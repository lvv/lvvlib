#include <stdlib.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_multimin.h>

/* Paraboloid centered on (p[0],p[1]), with  scale factors (p[2],p[3]) and minimum p[4] */

double my_f(const gsl_vector * v, void *params) {

		double  x, y;
		double *p = (double *) params;

		x = gsl_vector_get(v, 0);
		y = gsl_vector_get(v, 1);

		return p[2] * (x - p[0]) * (x - p[0]) + p[3] * (y - p[1]) * (y - p[1]) + p[4];
}

int main(void)  {


		/* Starting point */
		gsl_vector *x = gsl_vector_alloc(2);
		gsl_vector_set(x, 0, 5.0);
		gsl_vector_set(x, 1, 7.0);

		/* Set initial step sizes to 1 */
		gsl_vector *ss = gsl_vector_alloc(2);
		gsl_vector_set_all(ss, 1.0);

		double  par[5] = { 1.0, 2.0, 10.0, 20.0, 30.0 };

		//----------------------------------------------------------------------
		
		////////////////////////////////////////////////////////////// MEMBERS
		gsl_multimin_fminimizer 	*minimizer;
		gsl_multimin_function		minex_func;
		////////////////////////////////////////////////////////////// CTOR  (N,my_f, x, par, ss)
		int N=2;
		const gsl_multimin_fminimizer_type *T = gsl_multimin_fminimizer_nmsimplex;

		minex_func.n = N;
		minex_func.f = &my_f;
		minex_func.params = (void *) &par;

		minimizer = gsl_multimin_fminimizer_alloc(T, N);
		gsl_multimin_fminimizer_set(minimizer, &minex_func, x, ss);

		////////////////////////////////////////////////////////////// ITERATE
		size_t  iter = 0;
		int     iterate_status;
		int     test_status;
		double  size;
		do {
				iter++;
				iterate_status = gsl_multimin_fminimizer_iterate(minimizer);

				if (iterate_status) break;

				size = gsl_multimin_fminimizer_size(minimizer);
				test_status = gsl_multimin_test_size(size, 1e-2);

				if (test_status == GSL_SUCCESS) {
						printf("converged to minimum at\n");
				}

				printf("%5d %10.3e %10.3ef f() = %7.3f size = %.3f\n", int(iter), gsl_vector_get(minimizer->x, 0), gsl_vector_get(minimizer->x, 1), minimizer->fval, size);

		} while (test_status == GSL_CONTINUE && iter < 100);
		////////////////////////////////////////////////////////////// DTOR

		gsl_multimin_fminimizer_free(minimizer);
		//----------------------------------------------------------------------
		gsl_vector_free(x);
		gsl_vector_free(ss);

		return 0;
}

#include <stdlib.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_multimin.h>

/* Paraboloid centered on (p[0],p[1]), with  
   scale factors (p[2],p[3]) and minimum p[4] */

double my_f(const gsl_vector * v, void *params) {
		double  x, y;
		double *p = (double *) params;

		x = gsl_vector_get(v, 0);
		y = gsl_vector_get(v, 1);

		return p[2] * (x - p[0]) * (x - p[0]) + p[3] * (y - p[1]) * (y - p[1]) + p[4];
}

/* The gradient of f, df = (df/dx, df/dy). */
void my_df(const gsl_vector * v, void *params, gsl_vector * df) {
		double  x, y;
		double *p = (double *) params;

		x = gsl_vector_get(v, 0);
		y = gsl_vector_get(v, 1);

		gsl_vector_set(df, 0, 2.0 * p[2] * (x - p[0]));
		gsl_vector_set(df, 1, 2.0 * p[3] * (y - p[1]));
}

/* Compute both f and df together. */
void my_fdf(const gsl_vector * x, void *params, double *f, gsl_vector * df) {
		*f = my_f(x, params);
		my_df(x, params, df);
}

int main(void) {

		size_t  iter = 0;
		int     status;

		const gsl_multimin_fdfminimizer_type *T;
		gsl_multimin_fdfminimizer *s;

		/* Position of the minimum (1,2), scale factors 
		   10,20, height 30. */
		double  par[5] = { 1.0, 2.0, 10.0, 20.0, 30.0 };

		gsl_vector *x;
		gsl_multimin_function_fdf my_func;

		my_func.n = 2;
		my_func.f = &my_f;
		my_func.df = &my_df;
		my_func.fdf = &my_fdf;
		my_func.params = &par;

		/* Starting point, x = (5,7) */
		x = gsl_vector_alloc(2);
		gsl_vector_set(x, 0, 5.0);
		gsl_vector_set(x, 1, 7.0);

		T = gsl_multimin_fdfminimizer_conjugate_fr;
		s = gsl_multimin_fdfminimizer_alloc(T, 2);

		gsl_multimin_fdfminimizer_set(s, &my_func, x, 0.01, 1e-4);

		do {
				iter++;
				status = gsl_multimin_fdfminimizer_iterate(s);

				if (status)
						break;

				status = gsl_multimin_test_gradient(s->gradient, 1e-3);

				if (status == GSL_SUCCESS)
						printf("Minimum found at:\n");

				printf("%5d %.5f %.5f %10.5f\n", iter, gsl_vector_get(s->x, 0), gsl_vector_get(s->x, 1), s->f);

		}
		while (status == GSL_CONTINUE && iter < 100);

		gsl_multimin_fdfminimizer_free(s);
		gsl_vector_free(x);

		return 0;
		// TODO set label "yield point" at 0.003, 260
}

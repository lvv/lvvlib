
	#ifndef LVV_MULTIMIN_H
	#define LVV_MULTIMIN_H
	
#include <stdlib.h>
#include <iostream>
using std::cerr;
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_multimin.h>
#include <lvv/lvv.h>
#include <lvv/math.h>

namespace lvv {
 

class f_minimizer {  public:

	f_minimizer (const int N, double F(const gsl_vector*, void *), double *xa,  double *ssa, void *var, bool _trace=false)
	:	T (gsl_multimin_fminimizer_nmsimplex), trace(_trace), found(false), fmin(999999)
	{
		minex_func.n = N;
		minex_func.f = F;
		minex_func.params = var;

		mk_gsl_vector x (xa,N);// this is auto on stack(temp), will be copied in minimizer, //  so we are fine when it will go out of scope
		mk_gsl_vector ss(ssa, N);
		//gv_x  = gsl_vector_alloc(N);	for (int i=0; i<N; i++)  gsl_vector_set(gv_x,  i, xa [i]);
		//gv_ss = gsl_vector_alloc(N);	for (int i=0; i<N; i++)  gsl_vector_set(gv_ss, i, ssa[i]);


		minimizer = gsl_multimin_fminimizer_alloc(T, N);
		  gsl_multimin_fminimizer_set(minimizer, &minex_func, &x  , &ss);
		//gsl_multimin_fminimizer_set(minimizer, &minex_func, gv_x, gv_ss);
		xmin = minimizer->x->data;
		if (trace)   cout << "#  minimizer: "  <<  gsl_multimin_fminimizer_name (minimizer)  <<  endl;
	};


	~f_minimizer () { gsl_multimin_fminimizer_free(minimizer);  /* gsl_vector_free(gv_x);   gsl_vector_free(gv_ss) ;*/ };


	void   find_min (double characteristic_size, int max_iter) {
		int	test_status=GSL_CONTINUE;			// test_status:  GSL_SUCCESS==0; GSL_CONTINUE==-2; 

		if (trace)  FMT("# Itr  %10t Y   %20t Step  %30t X[0..]\n");
	
		for  ( iter=0;  iter<max_iter && (test_status==GSL_CONTINUE);   ++iter )   {

			int  iterate_status = gsl_multimin_fminimizer_iterate(minimizer);

			if (iterate_status) {
				cerr << "error: FMinimizer: in gsl_multimin_fminimizer_iterate()\n";
				break;
			}

			double size = gsl_multimin_fminimizer_size(minimizer);
			test_status = gsl_multimin_test_size(size, characteristic_size);

			if (test_status == GSL_SUCCESS)  {
				found=true;
				fmin=minimizer->fval;
				if (trace )    cout  << "converged to minimum at\n";
			}
			
			if (trace) { 
				FMT("%5d %10.5d %10.5d") %iter   %(minimizer->fval)  %size;
				for (unsigned i=0; i < minimizer->x->size; ++i) FMT("%10.5d") %gsl_vector_get(minimizer->x, i);
				cout << endl;
			}
		
		}
	}

	const gsl_multimin_fminimizer_type *T;
	gsl_multimin_fminimizer            *minimizer;
	gsl_multimin_function               minex_func;
	bool                                trace;
	bool                                found;
	double                             *xmin;
	double                              fmin;
	gsl_vector                         *gv_x;
	gsl_vector                         *gv_ss;
	int					iter;
 };
 } // namespace
 
    #endif // LVV_MULTIMIN_H

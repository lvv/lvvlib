#include <stdlib.h>
#include <iostream>
using std::cerr;
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_multimin.h>
#include "../lvv/lvv.h"
#include "../lvv/math.h"
using namespace lvv;
 
class FMinimizer {  public:
	FMinimizer (int N, double F(const gsl_vector*, void *), double *xa, void *p,  double *ssa,  bool _trace=false)
	:	T (gsl_multimin_fminimizer_nmsimplex), trace(_trace), found(false), xmin(NULL), fmin(999999)
	{
		minex_func.n = N;
		minex_func.f = F;
		minex_func.params = p;

		mk_gsl_vector x (xa,N);// this is auto on stack(temp), will be copied in minimizer, //  so we are fine when it will go out of scope
		mk_gsl_vector ss(ssa, N);

		minimizer = gsl_multimin_fminimizer_alloc(T, N);
		gsl_multimin_fminimizer_set(minimizer, &minex_func, &x, &ss);
		if (trace)   cout << "#  minimizer: "  <<  gsl_multimin_fminimizer_name (minimizer)  <<  endl;
	}

	FMinimizer (int N, double F(const gsl_vector*, void *), gsl_vector *x, void *p,  gsl_vector *ss,  bool _trace=false)
	:	T (gsl_multimin_fminimizer_nmsimplex), trace(_trace), found(false)
	{
		minex_func.n = N;
		minex_func.f = F;
		minex_func.params = p;

		minimizer = gsl_multimin_fminimizer_alloc(T, N);
		gsl_multimin_fminimizer_set(minimizer, &minex_func, x, ss);
		if (trace)   cout << "#  minimizer: "  <<  gsl_multimin_fminimizer_name (minimizer)  <<  endl;
	}


	~FMinimizer () { gsl_multimin_fminimizer_free(minimizer); }


	void   find_min (double characteristic_size, int max_iter) {
		int	test_status=GSL_CONTINUE;			// test_status:  GSL_SUCCESS==0; GSL_CONTINUE==-2; 

		if (trace)  FMT("# Itr  %10t Y   %20t Step  %30t X[0..]\n");
	
		for  ( int iter=0;  iter<max_iter && (test_status==GSL_CONTINUE);   ++iter )   {

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
				xmin = minimizer->x->data;
				if (trace )    cout  << "converged to minimum at\n";
			}
			
			if (trace) { 
				FMT("%5d %10.5d %10.5d") %iter   %(minimizer->fval)  %size;
				for (int i=0; i<2; ++i) FMT("%10.5d") %gsl_vector_get(minimizer->x, i);
				cout << endl;
			}
		
		}
	}

	const gsl_multimin_fminimizer_type *T;
	gsl_multimin_fminimizer 	*minimizer;
	gsl_multimin_function		minex_func;
	bool				trace;
	bool				found;
	double 				*xmin;
	double 				fmin;
 };


// set contour; set isosamples 30; splot [] [-3:10] (1/(0.5+((x/2)**2-y)**2))/(0.5+(x/10)**2+(y/20)**2)
double curved_trench(const gsl_vector * v, void *params) {
	/* Paraboloid centered on (p[0],p[1]), with  scale factors (p[2],p[3]) and minimum p[4] */
	double  x, y;
	double *p = (double *) params;

	x = gsl_vector_get(v, 0);
	y = gsl_vector_get(v, 1);

	return p[2] * (x - p[0]) * (x - p[0]) + p[3] * (y - p[1]) * (y - p[1]) + p[4];
}

double my_f(const gsl_vector * v, void *params) {
	/* Paraboloid centered on (p[0],p[1]), with  scale factors (p[2],p[3]) and minimum p[4] */
	double  x, y;
	double *p = (double *) params;

	x = gsl_vector_get(v, 0);
	y = gsl_vector_get(v, 1);

	return p[2] * (x - p[0]) * (x - p[0]) + p[3] * (y - p[1]) * (y - p[1]) + p[4];
}
double  par[5] = { 1.0, 2.0, 10.0, 20.0, 30.0 };

double f(const gsl_vector * gv, void *dummy) {
	/* Paraboloid centered on (p[0],p[1]), with  scale factors (p[2],p[3]) and minimum p[4] */
	double  p[5] = { 1.0, 2.0, 10.0, 20.0, 30.0 };
	double const *x   = gsl_vector_const_ptr(gv, 0);
	int static    cnt = 0;
	double        y   = p[2] *(x[0] - p[0]) *(x[0] - p[0]) + p[3] *(x[1] - p[1]) *(x[1] - p[1]) + p[4];

	FMT("%5d %10.5d %10.5d") % cnt++   % y  % "\" \"";
	for (int i=0; i<2; ++i) FMT("%10.5d") %x[i];
	cout << endl;
	return y;
}


int	main(void)  {

	/* Starting point */
	double xa[2]= {5,7};
	gsl_vector *x = gsl_vector_alloc(2);
	gsl_vector_set(x, 0, 5.0);
	gsl_vector_set(x, 1, 7.0);

	/* Set initial step sizes to 1 */
	double ssa[2] ={1,1};
	gsl_vector *ss = gsl_vector_alloc(2);
	gsl_vector_set_all(ss, 1.0);

	cout << 
		"# :gnuplot:  set font \"arial,6\"; set view 0,90,1.7;  set dgrid3d;  set key off;  set contour surface;  set cntrparam levels 20;  set isosample 20;"
		"p0=1; p1=2; p2=10; p3=20; p4=30;"
		"splot [-3:10] [-3:10]"
			"p2*(x - p0)*(x-p0) + p3*(y-p1)*(y-p1) + p4,"
			"\"pipe\" using 4:5:2:1 with labels;\n";


	FMinimizer fm(2, f, xa, par, ssa, false);	
	//FMinimizer fm(2, my_f, x, par, ss, false);	
	fm.find_min(1e-2, 100);

	if (fm.found)  {
		FMT("Result: Fmin=%10.5f   Xmin: ") % fm.fmin ;    for  ( int i=0;   i < int(x->size);   ++i )   FMT("%10.5d") % fm.xmin[i];  cout << endl;
	} else {
		cout << "Result: minimum not found\n";
	}

	gsl_vector_free(x);
	gsl_vector_free(ss);

	return 0;
}

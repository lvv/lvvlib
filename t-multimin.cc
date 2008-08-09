#include  "multimin.h"
using namespace lvv;

// set contour; set isosamples 30; splot [] [-3:10] (1/(0.5+((x/2)**2-y)**2))/(0.5+(x/10)**2+(y/20)**2)
double curved_trench(const gsl_vector * v, void *params) {
	/* Paraboloid centered on (p[0],p[1]), with  scale factors (p[2],p[3]) and minimum p[4] */
	double  x, y;
	double *p = (double *) params;

	x = gsl_vector_get(v, 0);
	y = gsl_vector_get(v, 1);

	return p[2] * (x - p[0]) * (x - p[0]) + p[3] * (y - p[1]) * (y - p[1]) + p[4];
}


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

	double x0[2]    = {5,7}; 	
	double step0[2] = {1,1};
	int    N        = sizeof(x0)/sizeof(x0[0]);

	cout << 
		"# :gnuplot:  set font \"arial,6\"; set view 0,90,1.7;  set dgrid3d;  set key off;  set contour surface;  set cntrparam levels 20;  set isosample 20;"
		"p0=1; p1=2; p2=10; p3=20; p4=30;"
		"splot [-3:10] [-3:10]"
			"p2*(x - p0)*(x-p0) + p3*(y-p1)*(y-p1) + p4,"
			"\"pipe\" using 4:5:2:1 with labels;\n";


	f_minimizer 	fm(N, f, x0, step0);	
	fm.find_min(1e-2, 100);

	if (fm.found)  {
		FMT("Result: Fmin=%10.5f   Xmin: ") % fm.fmin ;    for  ( int i=0;   i < N;   ++i )   FMT("%10.5d") % fm.xmin[i];  cout << endl;
	} else {
		cout << "Result: minimum not found\n";
	}

	return 0;
}

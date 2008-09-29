#include  "multimin.h"
using namespace lvv;


double f(const gsl_vector * gv, void *dummy) {
	//#define  GP_F "p0=1; p1=2; p2=10; p3=20; p4=30;" "splot [-3:10] [-3:10]" "p2*(x - p0)*(x-p0) + p3*(y-p1)*(y-p1) + p4,"
	/* Paraboloid centered on (p[0],p[1]), with  scale factors (p[2],p[3]) and minimum p[4] */
	double  p[5] = { 1.0, 2.0, 10.0, 20.0, 30.0 };
	double const *x   = gsl_vector_const_ptr(gv, 0);
	double        y   = p[2] *(x[0] - p[0]) *(x[0] - p[0]) + p[3] *(x[1] - p[1]) *(x[1] - p[1]) + p[4];
								int static    cnt = 0;
								FMT("%5d %10.5d %10.5d") % cnt++   % y  % "\" \"";
								for (int i=0; i<2; ++i) FMT(" %12.5d") %x[i];
								cout << endl;
	return y;
}

double curved_trench(const gsl_vector * gv, void *var) {
	//#define  GP_F "splot [-1:8] [-3:8] (1/(0.5+((x/2)**2-y)**2))/(0.5+(x/10)**2+(y/20)**2),"
	#define  GP_F "splot [-2:1.5][-0.5:2] log(100 * (y - x*x)**2 + (1 - x)**2),  "
	//#define  GP_F "unset view; splot [-1:8] [-3:8] "
	const double  *X = gsl_vector_const_ptr(gv,0);
	//double 	y=(1/(0.5+pow2(pow2(x[0]/2)-x[1])))/(0.5+pow2(x[0]/10)+pow2(x[1]/20));  // my curved trench
        double y = 100 * powi(X[1] - X[0] * X[0], 2) + powi(1 - X[0], 2); // this is rosenbrock func
								int static    cnt = 0;
								FMT("%7d %24.20g  %30t") % ++cnt  % y  ;
								for (int i=0; i<2; ++i) FMT("%24.20g") %X[i];
								cout << endl;
	//return  -y;
	return  y;
}

double f3d(const gsl_vector * gv, void *var) {
	//#define  GP_F "splot [-1:8] [-3:8] (1/(0.5+((x/2)**2-y)**2))/(0.5+(x/10)**2+(y/20)**2),"
	//#define  GP_F "unset view; splot [-1:8] [-3:8] "
	const double  *x = gsl_vector_const_ptr(gv,0);
	double 	y=
			(1/(0.5+pow2(pow2(x[0]/2)-x[1]))) 
			/  (0.5  +  pow2 (x[0]/10)  +  pow2(x[1]/20)  +  pow2(x[2])  );
								int static    cnt = 0;
								FMT("%7d %24.20g %10.5g") % cnt++   % y  % "\" \"";
								for (int i=0; i<3; ++i) FMT("%24.20g") %x[i];
								cout << endl;
	return  -y;
}


int	main(void)  {

	// f3d
	//double	x0[]    = {4.444, 6.6666, 10}; 
	//double	step0[] = {0.5,   0.5,  1}; 
	double	x0[]    = {-1.2, 1}; 
	double	step0[] = {0.001,  0.001}; 

	double	*x      = x0; 
	int	N       = sizeof(x0)/sizeof(x0[0]); 

	cout << 
		"# :gnuplot: set view 0,0,1.7;   set font \"arial,6\"; set dgrid3d;  set key off;  set contour surface;  set cntrparam levels 20;  set isosample 40;"
		GP_F "\"pipe\" using 3:4:2:1 with labels; \n";

	f_minimizer 	fm(N, curved_trench, x, step0, NULL);	
	//f_minimizer 	fm(N, f3d, x, step0, NULL, true);	
	fm.find_min(1e-10, 300);

	if (fm.found)  {
		FMT("Result: Fmin=%10.5f   Xmin: ") % fm.fmin ;    for  ( int i=0;   i < N;   ++i )   FMT("%12.5g") % fm.xmin[i];  cout << endl;
		FMT("Result: Fmin=%10.5f   x0:   ") % fm.fmin ;    for  ( int i=0;   i < N;   ++i )   FMT("%12.5g") % x[i];  cout << endl;
	} else {
		cout << "Result: minimum not found\n";
	}

	return 0;
}

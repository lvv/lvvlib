
#include <cmath>
using namespace std;

#include <lvv/lvv.h>
#include <lvv/math.h>
using lvv::powi;



int iter_cnt;

#include <lvv/hook-jeevs-min.h>

double f1(const array<double,2,1> & X) { 		//  Rosenbroke function
	iter_cnt++;
	double y = 100 * powi(X[2] - X[1] * X[1], 2) + powi(1 - X[1], 2);
								int static    cnt = 0;
								FMT("%7d %24.20g  %30t") % ++cnt  % y  ;
								for (int i=X.ibegin(); i<X.iend(); ++i) FMT("%24.20g") %X[i];
								cout << endl;
	return y;
}


void test1() {
	typedef array<double,2,1> vector_t;
	vector_t  b0 = {{-1.2, 1}};		// startin point
	vector_t  b;				// result
	vector_t  bm = {{ 1.0, 1.0}};		// Exact min location
	vector_t  h0 = {{10., 10.}};		// Initial step
	b =  b0;
	iter_cnt = 0;
	class hook_jeevs_min<vector_t> minimizer;

	cout << "# :gnuplot: set view 0,0,1.7;   set font \"arial,6\"; set dgrid3d;  set key off;  set contour surface;  set cntrparam levels 20;  set isosample 40;splot [-2:1.5][-0.5:2] log(100 * (y - x*x)**2 + (1 - x)**2),  \"pipe\" using 3:4:2:1 with labels;\n" ;

	cout << "\n\tRosenbroke function:  f = 100*(x2-x1^2)^2 + (1-x1)^2\n" 
		"\nInitial guess          b0" <<	b0;
	cout << "\nFunction value at it  f0 = " << 	f1(b0) << 
		"\nInitial steps          h0" <<	h0 << 
		"\nMinimum f value found f  = " << minimizer.min(b, h0, f1) << "     at  b" << b << 
		"\nExact min location    bm" << bm;
	cout << "\nNo. of iterations     ni = " << iter_cnt << endl;

}

/*
double f2(array<double,2,1>& X) { //	Bocks function
	iter_cnt++;
	return powi(exp(-1. / 10) - exp(-X[1] / 10) + exp(-10. / 10) - exp(-X[2] / 10), 2);
}

void test2() {
	const int n = 2;
	VEC  b0 = {{0, 0}};		// startin point
	VEC  b;				// result
	VEC  bm = {{ 10.0, 1.0}};	// Exact min location
	VEC  h0 = {{10., 10.}};		// Initial step

	b =  b0;
	iter_cnt = 0;
	class hook_jeevs_min<array<double,2,1>> minimizer;
	cout << "\n\n\tRosenbroke function\n"
		"\n\n\tf = 100*(x2-x1^2)^2 + (1-x1)^2\n\n"
		"\nInitial guess         b0 = " <<	b0
		"\nFunction value at it  f0 = " << 	f1(b0) << 
		"\nInitial steps         h0 = " <<	h0 << endl << 
		"\nMinimum f value found f  = " << minimizer.min(b, h0, f2) << 
		"\n                  at  b  = " << b << 
		"\nExact min location    bm = " << bm << 
		"\nNo. of iterations     ni = " << iter_cnt << endl;

}



double f3(array<double,4,1>& X) { //	Mile & Cuntrell function
	iter_cnt++; return powi(exp(X[1]) - X[2], 4) + 100 * powi(X[2] - X[3], 6) + powi(atan(X[3] - X[4]), 4) + powi(X[1], 8);
}
*/

/*
void test3() {
	const int n = 4;
	VECTOR  b0 = V_build(1, n, 1., 2., 2., 2., "END");				
	VECTOR  b = V_new(1, n);						
	VECTOR  bm = V_build(1, n, 0., 1., 1., 1., "END");		
	VECTOR  h0 = V_build(1, n, 10., 10., 10., 10., "END");	
	...
}*/



double f4(array<double,4,1>& X) { //  Powell function
	iter_cnt++; return powi(X[1] + 10 * X[2], 2) + 5 * powi(X[3] - X[4], 2) + powi(X[2] - 2 * X[3], 4) + 10 * powi(X[1] - X[4], 4);
}

/*
void test4() {
	const int n = 4;
	VECTOR  b0 = V_build(1, n, 3., -1., 0., 1., "END");			
	VECTOR  b = V_new(1, n);					
	VECTOR  bm = V_build(1, n, 0., 0., 0., 0., "END");	
	VECTOR  h0 = V_build(1, n, 10., 10., 10., 10., "END");
	..
}*/


int main() {
	printf("\n\n\n\tVerify HJMIN program to minimize a function value\n");
	test1();
	//test2();
	//test3();
	//test4();
}

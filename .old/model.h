
    #ifndef LVVMODEL_H
    #define LVVMODEL_H

    #include <iostream>
    #include <iomanip>
    using std::fixed;
    using std::showpos;

    #include <string>
    #include <gsl/gsl_multifit.h>
    #include <gsl/gsl_poly.h>
    #include "lvv.h"
    #include "math.h"
    using lvv::powi;


    namespace lvv {

    int  const  poly_order = 4;

//	template<int M>
class   Model   {     public: ///////////////////////////////////////////////////////////// Model Data - μ² polinom fitting


Model () : n(0), m(0), x(NULL), y(NULL), X(NULL),  cov(NULL),  c(NULL)              {}

Model (double _x[], double _y[], int _n, int _m=-1) : n(_n), m(_m), x(_x), y(_y)    { ////////////////////////////////   CTOR

        // N - data points [0..N) ( 5 for NF )
 	// M - number of model parameters [0..M)
 	// if polynomial used in model:
 	//      M-1 -  poly order  C[0]..C[m-1]

	assert(_n >= 3 && "not implemented");    
	if (_m == -1) {      //  then need autodetect
	    if      (n < 6 ) m = n-2;
	    else if (n < 10) m = n-3;
	    else if (n < 20) m = n-4;
	} 

	assert(n >= m);  

	X   = gsl_matrix_alloc (n, m) ;		assert(X);
	c   = gsl_vector_alloc (m   ) ;		assert(c);
	cov = gsl_matrix_alloc (m, m) ;		assert(cov);
	
	xv = gsl_vector_view_array (_x, n); 
	yv = gsl_vector_view_array (_y, n); 

	/////    INIT - PREP MATRIX for POLIFIT
	for (i = 0; i<n; i++)    for (int p=0; p<m; ++p)     gsl_matrix_set (X, i, p, powi(_x[i], p));

	/////    FIT
	gsl_multifit_linear_workspace *work = gsl_multifit_linear_alloc (n, m); 
	//  gsl_multifit_linear     (X, y,                         c, cov, &chisq, work); // int gsl_multifit_linear     (const gsl_matrix *X, const gsl_vector *y,                           gsl_vector *c, gsl_matrix *cov, double *chisq, gsl_multifit_linear_workspace *ws)
	    gsl_multifit_linear_svd (X, &yv.vector, svd_tol, &rank, c, cov, &chisq, work); // int gsl_multifit_linear_svd (const gsl_matrix *X, const gsl_vector *y, double tol, size t* rank, gsl_vector *c, gsl_matrix *cov, double *chisq, gsl_multifit_linear_workspace *ws)
	gsl_multifit_linear_free (work);
 };

~Model() { ////////////////////////////////////////////////////////////////// DTOR
	if(cov)    gsl_matrix_free (cov);
	if(c  )    gsl_vector_free (c);
	if(X  )    gsl_matrix_free (X);
 };


double  estimate (const double x)   const {
	double y_est = gsl_vector_get(c,0) ; 
	double pow_x = 1.0                 ; // x[0,0]^0

	for (int p=1;  p<m;  ++p) {
	    pow_x *= x;
	    y_est += gsl_vector_get(c,p)*pow_x;
	}

	return y_est;
 };

double  inverse_estimate (const double yy)    const {

	double xx = -1.0;

	double *C=c->data;

	if        (m>2) {

		double c0_save = C[0];
		C[0] =  c0_save-yy;

		struct { double real; double imag; } z[poly_order-1];

		int order = poly_order;	
		//if ( abs(C[poly_order-1]) < 0.000001 )	// reduce polinomial order of last elem == 0  
		if ( C[poly_order-1] == 0 )	// reduce polinomial order of last elem == 0  
			order = poly_order-1;
		    			assert (C[poly_order-1] != 0);	// hope we don't need to do it twice

		//  solve
		gsl_poly_complex_workspace * w = gsl_poly_complex_workspace_alloc (order);
		gsl_poly_complex_solve (gsl_vector_ptr(c,0), order, w, (double *)z);
		gsl_poly_complex_workspace_free (w);

		//  select real root from list of complex roots
		double oorr_distance         = numeric_limits<double>::max(); // out_of_range root distance to normal interval
		bool   got_root              = false;
		bool   got_out_of_range_root = false;
		double out_of_range_root     = -100;
		double real_root             = -100000;

		//double x_step                = x[1]-x[0];                    // with step p-rmse go from 0.9904215  to 0.9907456 
		double x_lower_bound         = x[0]    /* -x_step/2.0 */ ;
		double x_upper_bound         = x[n-1]  /* +x_step/2.0 */ ;

		for  (int i = 0;  i < order-1;  i++)    {				// for all roots
												//cerr << " \t("<<i<<") "<<  z[2*i] << "+i" << z[2*i+1];
			if  (abs(z[i].imag)  >  0.00000001)  continue;  

			if   ( x_lower_bound <=  z[i].real   &&  z[i].real <=  x_upper_bound)   {  // in x valid range
				real_root = z[i].real;
				got_root  = true;
															//cerr << " rr=" << real_root;
				break;	// found it
			}

			double below_lower_distance =  x_lower_bound - z[i].real;
			if  (  below_lower_distance > 0 )  {
				if  (( got_out_of_range_root  &&  below_lower_distance < oorr_distance )  ||  ! got_out_of_range_root)  {
					oorr_distance         =   below_lower_distance; 	// new shortest oorr distance
					got_out_of_range_root = true;
					out_of_range_root     = x_lower_bound;
													//cerr  << " oor=" << out_of_range_root ;
					continue;
				}
			}

			double above_upper_distance =  z[i].real - x_upper_bound ;
			if   ( above_upper_distance > 0 )  {
				if (( got_out_of_range_root  && above_upper_distance  < oorr_distance )  ||  ! got_out_of_range_root)  {  
					oorr_distance         = above_upper_distance;
					got_out_of_range_root = true;
					out_of_range_root     = x_upper_bound;
													//cerr  << " oor=" << out_of_range_root ;
					continue;
				}
			}

		};
			

	    if	     (got_root)				xx = real_root;
	    else  if (got_out_of_range_root)		xx = out_of_range_root;
	    else					{ xx=3.66; cerr << "#model::inverse_estimate(): root not found\n";  ; }
														//cerr << "  ROOT=" << xx << endl;

	    gsl_vector_set(c, 0, c0_save);

	    /*
	    double c0 =  gsl_vector_get(c,0);
	    double c1 =  gsl_vector_get(c,1);
	    double c2 =  gsl_vector_get(c,2);
	    double c3 =  gsl_vector_get(c,3);
	    if ( 0 > (27*pow2(c3)*pow2(yy)+(-54*c0*pow2(c3)+18*c1*c2*c3-4*pow3(c2))*yy+27*pow2(c0)*pow2(c3)+(4*pow3(c1)-18*c0*c1*c2)*c3+4*c0*pow3(c2)-pow2(c1)*pow2(c2)))  {
		cout << "inverse_estimate-4-1: cannot solve: c0-2" <<  c0 << " " << c1 << " " <<  c2 << " " << c3 << " y: " << yy << endl;
		return 3.6;
	    }
	    if ( 0 > 27*pow2(c3)*pow2(yy)+(-54*c0*pow2(c3)+18*c1*c2*c3-4*pow3(c2))*yy+27*pow2(c0)*pow2(c3)+(4*pow3(c1)-18*c0*c1*c2)*c3+4*c0*pow3(c2)-pow2(c1)*pow2(c2))  {
		cout << "inverse_estimate-4-2: cannot solve: c0-2" <<  c0 << " " << c1 << " " <<  c2 << " " << c3 << " y: " << yy << endl;
		return 3.6;
	    }
	    xx = cbrt((sqrt(27*pow2(c3)*pow2(yy)+(-54*c0*pow2(c3)+18*c1*c2*c3-4*pow3(c2))*yy+27*pow2(c0)*pow2(c3)+(4*pow3(c1)-18*c0*c1*c2)*c3+4*c0*pow3(c2)-pow2(c1)*pow2(c2))/(6*sqrt(3)*pow2(c3))-(-27*pow2(c3)*yy+27*c0*pow2(c3)-9*c1*c2*c3+2*pow3(c2))/(54*pow3(c3))))-cbrt((3*c1*c3-pow2(c2))/(9*pow2(c3)*(sqrt(27*pow2(c3)*pow2(yy)+(-54*c0*pow2(c3)+18*c1*c2*c3-4*pow3(c2))*yy+27*pow2(c0)*pow2(c3)+(4*pow3(c1)-18*c0*c1*c2)*c3+4*c0*pow3(c2)-pow2(c1)*pow2(c2))/(6*sqrt(3)*pow2(c3))-(-27*pow2(c3)*yy+27*c0*pow2(c3)-9*c1*c2*c3+2*pow3(c2))/(54*pow3(c3)))))-c2/(3*c3);

	} else if (m==3){
	    double c0 =  gsl_vector_get(c,0);
	    double c1 =  gsl_vector_get(c,1);
	    double c2 =  gsl_vector_get(c,2);

	    if(4*c2*yy-4*c0*c2+pow2(c1) < 0) {
		cout << "inverse_estimate-3: cannot solve: c0-2" <<  c0 << " " << c1 << " " <<  c2 << " y: " << yy << endl;
		return 3.6;
	    }

	    xx = (sqrt(4*c2*yy-4*c0*c2+pow2(c1))-c1)/(2*c2);
	    //xx = -(sqrt(4*c2*yy-4*c0*c2+pow2(c1))+c1)/(2*c2);
	   
	   */ 
	} else if (m==2){
	    double c0 =  gsl_vector_get(c,0);
	    double c1 =  gsl_vector_get(c,1);
	    xx = (yy-c0)/c1;
	} else {
	    assert(false);
	}

	return xx;
 };


void	print (string title="")  const {
	cout << "# :gnuplot: set key bottom; set ytics 0,0.5; set yrange [-0.1:1.1]; set xrange [0:6]; set grid; set pointsize 1.5;"
		<< (title.length()>0  ?  "set title \" " +  title + "\";"  :  "") << 
	    
		    "plot "
			" \"pipe\" using 1:3 title \"model\" with lines 5, "
			" \"pipe\" using 4:2 title \"inv x(y)\" with point 4,"
			" \"pipe\" using 1:2 title \"data\" with points 11 "
		";\n";

	format		table(" % 9f    %20t % 9f   %40t % 9f   %60t % 9f\n");
	string		_("\" \"");
							cout << table	% "# X" % "  Y"		% "Y-mod"     	% "X-mod-inv" ;

	for (int i=0;  i<n; ++i                )	cout << table	% x[i] 	% y[i] 		% _    		% _ ;
	for (double xx=0.0;  xx<=6.0; xx+=1./3.)	cout << table	% xx   	% _		% estimate(xx)	% _  ;
	for (double yy=0.0;  yy<=1.0; yy+=0.05 )	cout << table	% _ 	% yy   		% _    		% inverse_estimate(yy) ;
 };
	

private: // member vars
        int                  n         , m;
        const static double  svd_tol = 0.000001;
        size_t               rank;
        int                  i;
        double               xi        , yi, ei, chisq;
        gsl_vector_view      xv        , yv;
        double    	   * x;
        double             * y;
        gsl_matrix          *X         , *cov;
     
    public:
        gsl_vector          *c;
 };

    }      // namespace lvv
    #endif // LVVMODEL_H

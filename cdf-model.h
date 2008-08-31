
    #ifndef LVVMODEL_H
    #define LVVMODEL_H

    #include <iostream>
    #include <iomanip>
    using std::fixed;
    using std::showpos;

    #include <string>
    #include <lvv/lvv.h>
    #include <lvv/math.h>
    using lvv::powi;

    #include  "multimin.h"                                                                                                                                      
    using lvv::f_minimizer;



    namespace lvv {

    //int  const  poly_order = 4;

double  cdf_model_eval (int M, const double x, double *C)   {
	double poly = C[0] ; 
        double pow_x = 1.0                 ; // x[0,0]^0
 
        for (int i=1;  i<M;  ++i) {
            pow_x  *=  x;
            poly   +=  C[i]*pow_x;
        }
 
	double  y_est = erf(poly)/2.0 + 0.5;
	return  y_est;
 };

double sse(const gsl_vector *gv_param, void *var)  {        //####################################################################   Optimizee              
	double		*C	=   const_cast<double*>(gsl_vector_const_ptr(gv_param,0));
        double		*X	=  (double *) (((void **) var) [0]);
        double		*Y	=  (double *) (((void **) var) [1]);
        int   		N	= *(int *)    (((void **) var) [2]);

	double 		sum 	= 0.0;
	for (int i=0; i < N; i++) {
		sum +=  pow2<double> ( Y[i] - cdf_model_eval(N, X[i], C) );
							//FMT("\t X[i]=%f \t Y[i]=%f \t cdf_model_eval()=%f\n")  %X[i]  %Y[i]  %cdf_model_eval(N, X[i], C);
	}

							int static    cnt = 0;
							FMT("sse: call=%d  sse=%d \t C[]: ") % cnt++  %sum << *(array<double,4>*)C << endl;
                                			//copy(X, X+N, ostream_iterator<double>(cout, "  "));
	return  sum;
 }
 
	template<int M>
class   Model   {     public: ///////////////////////////////////////////////////////////// Model Data - μ² polinom fitting

Model () : n(0), X(NULL), Y(NULL)    {}

Model (double X[], double Y[], int n ) : n(n), X(X), Y(Y)    { ////////////////////////////////   CTOR

	// N - data points [0..N) ( 5 for NF )
	// M - number of model parameters [0..M)
	// if polynomial used in model:
	// 	M-1 -  poly order  C[0]..C[m-1]

	//assert(n >= 3 && "not implemented");    
	assert	(n >= M);  

	array<double, M> C0     = {{ -1.73996, 0.349906, -0.0125859, 0.00720428 }}; 
	array<double, M> C_step = {{ 0.5     , 0.2     , 0.1       , 0.05       }}; 
	C = C0;
 
	// fit model paramS
	void *var[] = {X, Y, &n};
        f_minimizer     fm(M, sse, (double *)&C, (double *) &C_step, var);       
        fm.find_min(1e-3, 200);
				if (!fm.found)  cerr << "# error model::fitting: minimum not found\n";
	C = *(array<double,M>*)fm.xmin;
				//cout << "xmin: " << *(array<double,M>*) fm.xmin << endl;
				//cout << "C:    " <<  C       << endl;
 };

~Model() { ////////////////////////////////////////////////////////////////// DTOR
 };


double  estimate (const double x)   const {
	double poly = C[0] ; 
        double pow_x = 1.0                 ; // x[0,0]^0
 
        for (int i=1;  i<M;  ++i) {
            pow_x  *=  x;
            poly   +=  C[i]*pow_x;
        }
 
	double  y_est = erf(poly)/2.0 + 0.5;
	return  y_est;
 };

double  inverse_estimate (const double cdf)    const {

	double       r_low     = -20+1;
	double       r_high    =  20+5;
	int    const max_cnt   = 200;
	double const precision = 0.0001;

	for (int cnt=0; cnt < max_cnt; cnt++) {
		double r_middle = (r_high + r_low)/2;
		double cdf_middle = estimate(r_middle);

		if (cdf_middle > cdf)	r_high = r_middle;
		else			r_low  = r_middle;

												//PR4(cdf, cdf_middle, r_low, r_high) 
		if ( (r_high-r_low) < precision ) 
			break;
	}
	return (r_high+r_low)/2.;
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

	for (int i=0;  i<n; ++i              	)	cout << table	% X[i] 	% Y[i] 		% _    		% _ ;
	for (double x=0.0;  x<=6.0; x+=1./3.	)	cout << table	% x   	% _		% estimate(x)	% _  ;
	for (double y=0.0;  y<=1.0; y+=0.05	)	cout << table	% _ 	% y   		% _    		% inverse_estimate(y) ;
 };
	

private: // member vars
        const int		n;
        int			i;
        double			*X;
        double			*Y;
        array<double,M> 	C;
        array<double,M> 	C_step;
    public:
 };

    }      // namespace lvv
    #endif // LVVMODEL_H


    #ifndef LVVMODEL_H
    #define LVVMODEL_H

    #include <iostream>
    #include <iomanip>
    using std::fixed;
    using std::showpos;

    #include <string>
    #include <gsl/gsl_multifit.h>
    #include <gsl/gsl_poly.h>
    #include "lvvlib.h"
    #include "lvvmath.h"

    #define poly_order 4

    namespace lvv {

    ////////////////////////////////////////////////////////////////////////////////// Model Data - μ² polinom fitting

class   Model   {                                 // gsl multifit wrapper

    public:
        Model (double _x[], double _y[], int _n, int _m=-1) : n(_n), m(_m), x(_x), y(_y)    { ////////////////////////////////   CTOR

                // N, M 
                assert(_n >= 3);     //  n==1 and n==2  - not implemented
                if (_m == -1) {      //  then need autodetect
                    if      (n < 6 ) m = n-2;
                    else if (n < 10) m = n-3;
                    else if (n < 20) m = n-4;
                } 

                assert(n >= m);  

                X   = gsl_matrix_alloc (n, m) ;
                c   = gsl_vector_alloc (m   ) ;
                cov = gsl_matrix_alloc (m, m) ;
                
                xv = gsl_vector_view_array (_x, n); 
                yv = gsl_vector_view_array (_y, n); 

                /////    INIT - PREP MATRIX for POLIFIT
                for (i = 0; i<n; i++)    for (int p=0; p<m; ++p)     gsl_matrix_set (X, i, p, lvv::powi(_x[i], p));

                /////    FIT
                gsl_multifit_linear_workspace *work = gsl_multifit_linear_alloc (n, m); 
                //  gsl_multifit_linear     (X, y,                         c, cov, &chisq, work); // int gsl_multifit_linear     (const gsl_matrix *X, const gsl_vector *y,                           gsl_vector *c, gsl_matrix *cov, double *chisq, gsl_multifit_linear_workspace *ws)
                    gsl_multifit_linear_svd (X, &yv.vector, svd_tol, &rank, c, cov, &chisq, work); // int gsl_multifit_linear_svd (const gsl_matrix *X, const gsl_vector *y, double tol, size t* rank, gsl_vector *c, gsl_matrix *cov, double *chisq, gsl_multifit_linear_workspace *ws)
                gsl_multifit_linear_free (work);
        };

        ~Model() { ////////////////////////////////////////////////////////////////// DTOR
                gsl_matrix_free (X);
                gsl_vector_free (c);
                gsl_matrix_free (cov);
        };

    public:

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
                //PR2(yy,xx);

                if        (m>2) {

                    double c0_save = gsl_vector_get(c,0);
                    gsl_vector_set(c, 0, c0_save-yy);

                    double z[(poly_order-1)*2];

                    //  solve
                    gsl_poly_complex_workspace * w = gsl_poly_complex_workspace_alloc (poly_order);                                                                                                            
                    gsl_poly_complex_solve (gsl_vector_ptr(c,0), poly_order, w, z);                                                                                                                   
                    gsl_poly_complex_workspace_free (w);                                                                                                                   

                    //  select root
                    bool got_root=false;
                    double real_root=3.6;
                                                                                                                //cerr << "Y=" << yy ;  
                    for (int i = 0; i < poly_order-1; i++)   {
                         cerr << " \t("<<i<<") "<<  z[2*i] << "+i" << z[2*i+1];            
                        if (lvv::abs(z[2*i+1]) <  0.00000001) {              //*imag part  2GEN
                            if ( x[0]-2 <  z[2*i]  &&  z[2*i] <  x[n-1]+2) {
                                real_root = z[2*i];
                                                                                                                //cerr << " \tr=" << real_root ;
                                got_root = true;
                            }
                        }
                    };
                    cerr << endl;

                    if (!got_root) {
                        cerr << "root not found\n";   
                        print();
                    } 

                    gsl_vector_set(c, 0, c0_save);

                    xx = real_root;

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


        void print (string title="")  const {
                cout << "# :gnuplot: set key bottom; set ytics 0,0.5; set yrange [-0.1:1.1]; set xrange [0:6]; set grid; "
                        << (title.length()>0  ?  "set title \" " +  title + "\";"  :  "") << 
                    
                            "plot "
                                " \"pipe\" using 1:3 title \"model\" with lines 5, "
                                " \"pipe\" using 4:2 title \"inv x(y)\" with point 4,"
                                " \"pipe\" using 1:2 title \"data\" with points 11 "
                        ";\n"
                    <<                                       "#  X              Y            "      "  Y-mod         X-mod-inv\n" << fixed << showpos ;
                for (int i=0;  i<n; ++i)                 cout << x[i]        << "\t" << y[i]                                                << endl;
                for (double xx=0.0;  xx<=6.0; xx+=1./3.) cout << xx          << "\t" << "\" \"\t\t" << estimate(xx)                         << endl;
                for (double yy=0.0;  yy<=1.0; yy+=0.05)  cout << "\" \"\t\t" << yy   << "\t"        << "\" \"\t\t"  << inverse_estimate(yy) << endl;
        };

        gsl_vector          *c;

    private:
        int                  n         , m;
        const static double  svd_tol = 0.000001;
        size_t               rank;
        int                  i;
        double               xi        , yi, ei, chisq;
        gsl_matrix          *X         , *cov;
        gsl_vector_view      xv        , yv;
        double     * x;
        double     * y;
 };

    }      // namespace lvv
    #endif // LVVMODEL_H

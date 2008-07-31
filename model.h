
    #ifndef LVVMODEL_H
    #define LVVMODEL_H

    #include "lvvmath.h"
    #include <gsl/gsl_multifit.h>

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

        double estimate(const double x) const {
                double y_est = gsl_vector_get(c,0) ; 
                double pow_x = 1.0                 ; // x[0,0]^0

                for (int p=1;  p<m;  ++p) {
                    pow_x *= x;
                    y_est += gsl_vector_get(c,p)*pow_x;
                }

                return y_est;
        };

        double inverse_estimate(const double yy) const {

                double xx;
                //PR2(yy,xx);

                if        (m==4) {
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
                   
                } else if (m==2){
                    double c0 =  gsl_vector_get(c,0);
                    double c1 =  gsl_vector_get(c,1);
                    xx = (yy-c0)/c1;
                } else {
                    assert(false);
                }

                return xx;
        };


        void print() {
                #define C(i) (gsl_vector_get(c,(i)))
                #define COV(i,j) (gsl_matrix_get(cov,(i),(j)))

                // printing for gnu plot
                double xx;
                double x_delta = (x[n-1] - x[0])/(n-1);

                cout  << "# Xᵢ 	"   <<  "  Yᵢ"  <<  "	Y est "  <<  endl;
                #define PRINT_DATA_LINE    cout << xx << " 	"  << " \" \" "  << " 	" <<  estimate(xx) << endl;
                xx = x[0] - x_delta  ;    PRINT_DATA_LINE
                xx = x[0] - x_delta/2;    PRINT_DATA_LINE

                float  sum_data_model_delta = 0;
                for (int i=0;  i<n;  ++i)  {
                    xx     = x[i]             ; cout << xx << " 	"  << y[i]  << " 	" <<  estimate(xx) << endl;
                    sum_data_model_delta += lvv::abs(y[i]) - estimate(xx);
                    xx     = x[i] + x_delta/2 ; PRINT_DATA_LINE
                }
                xx = x[n-1] + x_delta  ;    PRINT_DATA_LINE

                cout  << "#  N=" << n <<  "  M=" <<  m << "  rank=" <<  rank  <<  "   χ²/n="   << chisq/n 
                        << "   μ|data-model|=" << sum_data_model_delta/n ;
                cout  << "   C[p]={"; for (int p=0;  p<m;  ++p) cout << gsl_vector_get(c,p) << ", "; cout << "}\n";

        };

    private:
        int                  n         , m;
        const static double  svd_tol = 0.000001;
        size_t               rank;
        int                  i;
        double               xi        , yi, ei, chisq;
        gsl_matrix          *X         , *cov;
        gsl_vector          *c;
        gsl_vector_view      xv        , yv;
        double              *x         , *y;
 };

    }      // namespace lvv
    #endif // LVVMODEL_H

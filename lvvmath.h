
    #ifndef LVVMATH_H
    #define LVVMATH_H

    // TODO:  2 check boost: typedef typename tools::promote_args<T>::type result_type;
    #include <blitz/promote-old.h>

    #include <fenv.h>
    #include <csignal>
    #include <csetjmp>
    #include <limits>

    //#include <sys/resource.h>
    #include <cassert>
    #include <cstring>

    #include <string>
    #include <iostream>
    #include <iomanip>
    using std::string;

    using std::cout;
    using std::cerr;
    using std::flush;
    using std::endl;
    using std::setw;
    using std::boolalpha;
    using std::ostream;
    using std::setprecision;

    using std::numeric_limits;

    #include <boost/type_traits.hpp>
    using boost::true_type;
    using boost::false_type;
    using boost::is_integral;

    namespace lvv {

///////////////////////////////////////////////////////////////////////////////////////////////  SUPERIOR TYPE type_trait
    // this is promote_trait class to provide summator type
    //    typename Type<T>::SuperiorType       sum;
    // if T if float then sum will be double
    // if T if   int then sum will be long
    template <typename Default> struct   Type                   { typedef long            SuperiorType; };
    template <>                 struct   Type<  signed char>    { typedef   signed long   SuperiorType; };
    template <>                 struct   Type<unsigned char>    { typedef unsigned long   SuperiorType; };
    template <>                 struct   Type<unsigned short>   { typedef unsigned long   SuperiorType; };
    template <>                 struct   Type<unsigned int>     { typedef unsigned long   SuperiorType; };
    template <>                 struct   Type<unsigned long>    { typedef unsigned long   SuperiorType; };
    template <>                 struct   Type<float>            { typedef double          SuperiorType; };
    template <>                 struct   Type<double>           { typedef double          SuperiorType; };

////////////////////////////////////////////////////////////////////////////////////////  Average

            template<typename T>
class Average {  public:
        Average(string _lable=0):  count(0), sum(0),  lable(_lable)  {};
        double    average()  const    { /* div by 0 posible */  return double(sum)/count; }
        void      sample(T x)         { sum += x;  ++count; }

        template <typename U> friend ostream& operator<< (ostream& os, Average<U>  s);
    private:
        long        count;
        typename Type<T>::SuperiorType       sum;
        string      lable;
 };

                    template <typename T> ostream&
 operator<<  (ostream& os, Average<T> s)  {
        if     ( !s.lable.empty() ) 
           os  <<  s.lable << " avg: ";

       if (s.count > 0 ) 
           cout << s.average(); 
       else
           cout << "n/a" ;
       return os;
 };

    ////////////////////////////////////////////////////////////////////////////////////////////////////  POWI()
                double  inline  static
powi  (double x, int n)  {  // simplified http://dslinux.gits.kiev.ua/trunk/lib/libm/powi.c.  TODO: add asserts 
    double y;
    if( n & 1 )
        y = x;
    else
        y = 1.0;

    double w = x;
    n >>= 1;
    while( n ) {
        w = w * w; 

        if( n & 1 )
            y *= w;

        n >>= 1;
    }
    return y;
 }

template<typename T>  T static inline pow2(T x)  { return x*x; };
template<typename T>  T static inline pow3(T x)  { return x*x*x; };
template<typename T>  T static inline pow4(T x)  { return x*x*x*x; };
template<typename T>  T static inline pow5(T x)  { return x*x*x*x*x; };

    ////////////////////////////////////////////////////////////////////////////////////////////////////  ABS()
template<typename T>  T static inline abs(T x){ return x > 0 ? x  : -x; };


 /////////////////////////////////////////////////////////////////////////////////////////////////////  EQ (int/FP)
    typedef  unsigned long long int                     ulp_t;

    ///type_trait overloded 
    template<typename T1, typename T2, typename T>   bool static inline   eq_impl (T1 n1, T2 n2, true_type  integral_flag, ulp_t ulps, T characteristic_value) {  // integral
            return (T)n1==(T)n2;
     };  

    template<typename T1, typename T2, typename T>   bool static inline   eq_impl (T1 n1, T2 n2, false_type integral_flag, ulp_t ulps, T characteristic_value) {  // floating point
            // algorithm taken from: http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
            if (n1==n2)   return true;
            T diff      = n1-n2 > 0 ? n1-n2 : n2-n1;   // |n1-n2|
            if  ( characteristic_value == 0 ) 
                  characteristic_value   =  (lvv::abs(n1)+  lvv::abs(n2)) / 2.0;   // (|n1| + |n2|) /2
            T max_error = std::numeric_limits<T>::epsilon() * ulps;
                                                                                                        //PR(diff/divider); PR(max_error);
            return diff/characteristic_value < max_error;
     }

                                template<typename T1, typename T2> static inline   bool
eq (T1 n1,T2 n2, ulp_t ulps=100, typename promote_trait<T1,T2>::T_promote characteristic_value=0)  {
        typedef  typename promote_trait<T1,T2>::T_promote  T;
        typename is_integral<T>::type  integral_flag;
        return eq_impl<T1,T2,T>(n1, n2, integral_flag, ulps, characteristic_value);
 }


 //////////////////////////////////////////////////////////////////////////////////////  SIMON_MEAN
                    double static inline  
group_mean(
    double group_weight,    // Simon's K;   default ==25.  How much more we prefer group to individual mean (bigger --> prefer group)
    double group_mean,      // global mean
    double sum,             // individual measurements sum
    double count            // individual measurements count 
 ) { 
    // So intead of : mean = sum(ratings)/count(ratings)
    // He uses: bettermean = [K*global_mean + sum(ratings)] / [K+count(ratings)] and he uses K=25
                                                                            assert (group_weight > 0);
        return ( group_weight*group_mean + sum )  /  ( group_weight + count );
 } 


                    double static inline  
group_value(
    double group_weight,    // Simon's K;   default ==25.  How much more we prefer group to individual mean (bigger --> prefer group)
    double group_value,     // global value
    double value,           // individual measurements value
    double count            // individual measurements count 
 ) { 
    // So intead of : mean = sum(ratings)/count(ratings)
    // He uses: bettermean = [K*global_mean + sum(ratings)] / [K+count(ratings)] and he uses K=25
                                                                            assert (group_weight > 0);
        return ( group_weight * group_value + value * count )  /  ( group_weight + count );
 } 

    //////////////////////////////////////////////////////////////////////////////////////  FP Exceptions

    // from http://publib.boulder.ibm.com/infocenter/systems/index.jsp?topic=/com.ibm.aix.basetechref/doc/basetrf1/nextafterf.htm
    // An application wishing to check for error situations should set the errno
    // global variable to zero and call feclearexcept(FE_ALL_EXCEPT) before calling
    // these subroutines. Upon return, if errno is nonzero or
    // fetestexcept(FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW) is
    // nonzero, an error has occurred.
            //
            // rounding 
            //  FE_TONEAREST = 0,
            //  FE_DOWNWARD = 0x400,
            //  FE_UPWARD = 0x800,
            //  FE_TOWARDZERO = 0xc00
            //  int   fegetround(void)
            //  void  fesetround(int)

    jmp_buf             setjmp_environment;

void fpe_signal_handler(int signum, siginfo_t *info, void *context) {

    cerr << "FP error: "; 
    switch (info->si_code) {                                            // FIXME there might be several exception at the same time
        case FPE_INTDIV:   cerr << "Integer divide by zero "           ; break ; 
        case FPE_INTOVF:   cerr << "Integer overflow "                 ; break ; 
        case FPE_FLTDIV:   cerr << "Floating point divide by zero "    ; break ; 
        case FPE_FLTOVF:   cerr << "Floating point overflow "          ; break ; 
        case FPE_FLTUND:   cerr << "Floating point underflow "         ; break ; 
        case FPE_FLTRES:   cerr << "Floating point inexact result "    ; break ; 
        case FPE_FLTINV:   cerr << "Floating point invalid operation " ; break ; 
        case FPE_FLTSUB:   cerr << "Subscript out of range "           ; break ; 
        default:           cerr << "unknown. si_code: " << info->si_code ; 
    }
    cerr << endl;
    longjmp(setjmp_environment, 1);
 }

void setup_fpe() {
    feenableexcept(FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW); // do not enable all
    struct sigaction fpe_sigaction;
    memset(&fpe_sigaction, 0, sizeof(fpe_sigaction));
    fpe_sigaction.sa_sigaction = &fpe_signal_handler;
    fpe_sigaction.sa_flags = SA_RESETHAND | SA_SIGINFO;
    sigaction(SIGFPE, &fpe_sigaction, 0);

    if (setjmp(setjmp_environment)) 
        exit(111); // after exception control comes here
 }


    ////////////////////////////////////////////////////////////////////////////////// Model Data - μ² polinom fitting

                                #include <gsl/gsl_multifit.h>
                                template<typename C = const double[] >
class   Model   {                                 // gsl multifit wrapper

    public:
        Model (C _x, C _y, int _n, int _m=-1) : n(_n), m(_m)   { ////////////////////////////////   CTOR

                // N, M 
                assert(_n >= 3);     //  n==1 and n==2  - not implemented
                if (_m == -1) {      //  then need autodetect
                    if      (n < 6 ) m = n-2;
                    else if (n < 10) m = n-3;
                    else if (n < 20) m = n-4;
                } 

                assert(n >= m);  

                X   = gsl_matrix_alloc (n, m) ;
                x   = gsl_vector_alloc (n   ) ;
                y   = gsl_vector_alloc (n   ) ;
                c   = gsl_vector_alloc (m   ) ;
                cov = gsl_matrix_alloc (m, m) ;
                
                /////    INPUT
                for (i = 0; i < n; i++) {
                    gsl_vector_set (x, i, _x[i]);
                    gsl_vector_set (y, i, _y[i]);
                }

                /////    INIT - PREP MATRIX for POLIFIT
                for (i = 0; i<n; i++)    for (int p=0; p<m; ++p)     gsl_matrix_set (X, i, p, lvv::powi(_x[i], p));

                /////    FIT
                gsl_multifit_linear_workspace *work = gsl_multifit_linear_alloc (n, m); 
                //  gsl_multifit_linear     (X, y,                 c, cov, &chisq, work); // int gsl_multifit_linear     (const gsl_matrix *X, const gsl_vector *y,                           gsl_vector *c, gsl_matrix *cov, double *chisq, gsl_multifit_linear_workspace *ws)
                    gsl_multifit_linear_svd (X, y, svd_tol, &rank, c, cov, &chisq, work); // int gsl_multifit_linear_svd (const gsl_matrix *X, const gsl_vector *y, double tol, size t* rank, gsl_vector *c, gsl_matrix *cov, double *chisq, gsl_multifit_linear_workspace *ws)
                gsl_multifit_linear_free (work);
        };

        ~Model() { ////////////////////////////////////////////////////////////////// DTOR
                gsl_matrix_free (X);
                gsl_vector_free (x);
                gsl_vector_free (y);
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

            void print() {
                    #define C(i) (gsl_vector_get(c,(i)))
                    #define COV(i,j) (gsl_matrix_get(cov,(i),(j)))

                    // printing for gnu plot
                    double xx;
                    double x_delta = (gsl_vector_get(x,n-1) - gsl_vector_get(x,0))/(n-1);

                    cout  << "# Xᵢ 	"   <<  "  Yᵢ"  <<  "	Y est "  <<  endl;
                    #define PRINT_DATA_LINE    cout << xx << " 	"  << " \" \" "  << " 	" <<  estimate(xx) << endl;
                    xx = gsl_vector_get(x,0) - x_delta  ;    PRINT_DATA_LINE
                    xx = gsl_vector_get(x,0) - x_delta/2;    PRINT_DATA_LINE

                    float  sum_data_model_delta = 0;
                    for (int i=0;  i<n;  ++i)  {
                        xx     = gsl_vector_get(x,i)             ; cout << xx << " 	"  << gsl_vector_get(y,i)  << " 	" <<  estimate(xx) << endl;
                        sum_data_model_delta += lvv::abs(gsl_vector_get(y,i) - estimate(xx));
                        xx     = gsl_vector_get(x,i) + x_delta/2 ; PRINT_DATA_LINE
                    }
                    xx = gsl_vector_get(x,n-1) + x_delta  ;    PRINT_DATA_LINE

                    cout  << "#  N=" << n <<  "  M=" <<  m << "  rank=" <<  rank  <<  "   χ²/n="   << chisq/n 
                            << "   μ|data-model|=" << sum_data_model_delta/n ;
                    cout  << "   C[p]={"; for (int p=0;  p<m;  ++p) cout << gsl_vector_get(c,p) << ", "; cout << "}\n";

            };

        private:
            int                 n, m;
            const static double  svd_tol = 0.000001;
            size_t               rank;
            int                  i;
            double               xi, yi, ei, chisq;
            gsl_matrix          *X, *cov;
            gsl_vector          *x, *y, *c;
 };
    ////////////////////////////////////////////////////////////////////////////////// END
    }
    #endif // LVVMATH_H
    

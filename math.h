	
	#ifndef LVVMATH_H
	#define LVVMATH_H
	
	// TODO:  2 check boost: typedef typename tools::promote_args<T>::type result_type;
	#include <blitz/promote-old.h>
	
	#include <fenv.h>
	#include <csignal>
	#include <csetjmp>
	#include <limits>
		using std::numeric_limits;
	
	//#include <sys/resource.h>
	#include <cassert>
	#include <cstring>
	
	#include <string>
		using std::string;
	#include <iostream>
	#include <iomanip>
		using std::cout;
		using std::cerr;
		using std::flush;
		using std::endl;
		using std::setw;
		using std::boolalpha;
		using std::ostream;
		using std::setprecision;
		

	#include <gsl/gsl_vector.h>

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

    // TODO:  now depricated, use http://www.boost.org/doc/libs/1_36_0/libs/math/doc/sf_and_dist/html/math_toolkit/special/powers/ct_pow.html
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
 };

	template<typename T>  T static inline pow2(T x)  { return x*x; };
	template<typename T>  T static inline pow3(T x)  { return x*x*x; };
	template<typename T>  T static inline pow4(T x)  { return x*x*x*x; };
	template<typename T>  T static inline pow5(T x)  { return x*x*x*x*x; };

  ////////////////////////////////////////////////////////////////////////////////////////////////////  GSL
 
  // double[]  to  gsl_vector  wrapper
  struct mk_gsl_vector: public gsl_vector {
  	 mk_gsl_vector(double *a, int n) {
	 	size = n;
		stride = 1;
		data = a;
		block = NULL;
		owner = 0;
	 };
  };
 
    ////////////////////////////////////////////////////////////////////////////////////////////////////  ABS()
template<typename T>  T static inline abs(T x){ return x > 0 ? x  : -x; };
 //template<typename T>  T static inline max(T x, T y){ return x > y ? x  : y; };
 //template<typename T>  T static inline mix(T x, T y){ return x < y ? x  : y; };


 /////////////////////////////////////////////////////////////////////////////////////////////////////  EQ (int/FP)
    typedef  unsigned long long int                     ulp_t;

    ///type_trait overloded 
    template<typename T1, typename T2, typename T>   bool static inline   eq_impl (T1 n1, T2 n2, boost::true_type  integral_flag, ulp_t ulps, T characteristic_value) {  // integral
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
    double sample_value,
    double samples,
    double gloable_value,
    double eq_N	// K
 ) { 
    // So intead of : mean = sum(ratings)/count(ratings)
    // He uses: bettermean = [K*global_mean + sum(ratings)] / [K+count(ratings)] and he uses K=25
    //  http://en.wikipedia.org/wiki/Bayesian_average
                                                                            //assert (group_weight > 0);
        return (eq_N*gloable_value + sample_value*samples  )  /  ( eq_N + samples );
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
    //feenableexcept(FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW); // do not enable all
    feenableexcept(FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW ); // do not enable all
    struct sigaction fpe_sigaction;
    memset(&fpe_sigaction, 0, sizeof(fpe_sigaction));
    fpe_sigaction.sa_sigaction = &fpe_signal_handler;
    fpe_sigaction.sa_flags = SA_RESETHAND | SA_SIGINFO;
    sigaction(SIGFPE, &fpe_sigaction, 0);

    if (setjmp(setjmp_environment)) 
        exit(111); // after exception control comes here
 }

		template<typename ARRAY_t>
double		polynomial_eval	(const double x, ARRAY_t C)	{
 
	double poly = *C.begin() ; 
	double pow_x = 1.0; // x[0,0]^0
	for ( int i=C.ibegin()+1;   i < C.iend();   ++i )   {
	    pow_x  *=  x;
	    poly   +=  C[i]*pow_x;
	}

	return poly;
 };

// x  = a + b*x + c*x^2
// dx = 0 + b   + 2c*x
		template<typename ARRAY_t>
double		polynomial_derivative_eval	(const double x, ARRAY_t C)	{
 
	double	sum = *(C.begin()+1) ;  // 1st nonomial == 0, this is second
	double	pow_x = 1.0; // x[0,0]^0
	for ( int i = C.ibegin()+2;   i < C.iend();   ++i )   {
	    pow_x  *=  x;
	    sum    += i*C[i]*pow_x;
	}

	return sum;
 };

    ////////////////////////////////////////////////////////////////////////////////// END
    }
    #endif // LVVMATH_H
    

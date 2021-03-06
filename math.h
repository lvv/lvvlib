// math.h
// Part of lvvlib - https://github.com/lvv/lvvlib
// Copyright (c) 2000-2013
// Leonid Volnitsky (Leonid@Volnitsky.com)
	
	#ifndef LVV_MATH_H
	#define LVV_MATH_H
	
	
	#include <fenv.h>
	#include <csignal>
	#include <csetjmp>
	#include <limits>
		using std::numeric_limits;

	#include <tr1/type_traits>
	
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
		

	#include <lvv/meta.h>

	namespace lvv {

////////////////////////////////////////////////////////////////////////////////////////  Average

		    template<typename T>
	class Average {  public:
		Average(string _lable=0):  count(0), sum(0),  lable(_lable)  {};
		double    average()  const    { /* div by 0 posible */  return double(sum)/count; }
		void      sample(T x)         { sum += x;  ++count; }

		template <typename U> friend ostream& operator<< (ostream& os, Average<U>  s);
	    private:
		long        count;
		//typename Type<T>::SuperiorType       sum;
		//typename  std::tr1::promote<T>::type         sum;
		//__gnu_cxx::__promote<T>::__type         sum;
		typename LVV_PROMOTE1(T)         sum;
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
	// Depricated, use any of:
	// 	__gnu_cxx::power
	// 	http://www.sgi.com/tech/stl/power.html
	// 	http://www.boost.org/doc/libs/1_36_0/libs/math/doc/sf_and_dist/html/math_toolkit/special/powers/ct_pow.html
	//  glibc pow vs std::pow   - https://twiki.cern.ch/twiki/bin/view/Atlas/CalculatingIntegerPowers
	// TODO:  type specialization
	// TODO:  add asserts 
	// TODO:  fast pow with lookup table: http://www.hxa7241.org/articles/content/fast-pow-adjustable_hxa7241_2007.html
			template<typename T> inline  static
T  powi (T x, int n)  {  // simplified http://dslinux.gits.kiev.ua/trunk/lib/libm/powi.c
	T y;
	if ( n & 1 )	y = x;
	else		y = 1.0;
	
	T w = x;
	n >>= 1;
	while( n ) {
	    w = w * w; 
	
	    if  ( n & 1 )	y *= w;
	    n >>= 1;
	}
	return y;
 };


	template<typename T>  T static inline pow2(T x)  { return x*x; };
	template<typename T>  T static inline pow3(T x)  { return x*x*x; };
	template<typename T>  T static inline pow4(T x)  { return (x*x)*(x*x); };
	template<typename T>  T static inline pow5(T x)  { return (x*x)*(x*x)*x; };

	 
    ////////////////////////////////////////////////////////////////////////////////////////////////////  ABS()
    // TODO add specialisation for FP
    // 
    // We can take the absolute value by setting the sign bit to zero:
    //       float f;
    //       *(int*)&f &= 0x7FFFFFFF; // set sign bit to zero
   
	template<typename T>  T static inline abs(T x){ return x > 0 ? x  : -x; };
	template<typename T>  T static inline max(T x, T y){
		return x > y ? x  : y;
	};
	template<typename T>  T static inline min(T x, T y){
		return x < y ? x  : y;
	};
	/*
	#ifdef x__SSE__                                                                                                                    
		// fit to range
	        asm(    
	                " maxss %[Z_front], %[z];"
	                " minss %[Z_back],  %[z];"
	                        :[z]    "=&x"(z)
	                        :"0"(z), [Z_front]      "m"(rZ.front()),        [Z_back]        "m"(rZ.back())   
	        );
	*/



 /////////////////////////////////////////////////////////////////////////////////////////////////////  EQ (int/FP)
    typedef  unsigned long long int                     ulp_t;

    ///type_trait overloded 
    template<typename T1, typename T2, typename T>   bool static inline   eq_impl (T1 n1, T2 n2, std::tr1::true_type  integral_flag, ulp_t ulps, T characteristic_value) {  // integral
            return (T)n1==(T)n2;
     };  

    template<typename T1, typename T2, typename T>   bool static inline   eq_impl (T1 n1, T2 n2, std::tr1::false_type integral_flag, ulp_t ulps, T characteristic_value) {  // floating point
            // algorithm taken from: http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
            if (n1==n2)   return true;
            T abs_diff      = n1-n2 > 0 ? n1-n2 : n2-n1;   // |n1-n2|
            if  ( characteristic_value == 0 ) 
                  characteristic_value   =  (lvv::abs(n1)+  lvv::abs(n2)) * 0.5;   // (|n1| + |n2|) /2
            T max_error = std::numeric_limits<T>::epsilon() * ulps * characteristic_value ;
                                                                                                        //PR(diff/divider); PR(max_error);
            return abs_diff < max_error;
     }


                                template<typename T1, typename T2> static inline
bool		eq		(T1 n1,T2 n2, ulp_t ulps=100, typename LVV_PROMOTE2(T1,T2) characteristic_value=0)  {
        typedef typename LVV_PROMOTE2(T1,T2)  T;
        typename std::tr1::is_integral<T>::type  integral_flag;
        return eq_impl<T1,T2,T>(n1, n2, integral_flag, ulps, characteristic_value);
 }


 //////////////////////////////////////////////////////////////////////////////////////  SIMON_MEAN
					    static inline  
double		group_mean		(
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

void		fpe_signal_handler		(int signum, siginfo_t *info, void *context) {

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

void		setup_fpe			() {
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
double		polynomial_eval			(const double x, ARRAY_t C)	{
 
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

//		template<typename T>
//int		ilog2	(T n)	{
//	int ilog = 0; 
//	if (!n)  return 0;
////	while (n >>= 1)  { ilog++; }
//	return ilog;
//}


    ////////////////////////////////////////////////////////////////////////////////// END
    }
    #endif // LVV_MATH_H
    

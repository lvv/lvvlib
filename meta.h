
	// template metaprogramming and conveniance macros
	
	#ifndef LVV_META_H
	#define LVV_META_H

	
	// TODO:  2 check boost: typedef typename tools::promote_args<T>::type result_type;
	// local copy of blitz promote-old.h 
	#include <lvv/blitz-promote-old.h>
	
	#include <boost/type_traits/integral_constant.hpp>
		using boost::true_type;
		using boost::false_type;
	#include <boost/type_traits/is_integral.hpp>
		//#include <boost/type_traits.hpp>
		using boost::is_integral;
	
        #ifdef __GNUC__
                #define PURE         __attribute__((const))                                                                                                    
        #else
                #define PURE
        #endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////

	#include  <boost/type_traits/promote.hpp>

	namespace lvv {

///////////////////////////////////////////////////////////////////////////////////////////////  SUPERIOR TYPE type_trait
	/*  DEPRICATED, use boost::promote
	// this is promote_trait class to provide summator type
	// use:
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
	*/

//////////////////////////////////////////////////////////////////////////////////////////////  META  IF

	// also in /usr/include/boost/detail/select_type.hpp
	template <bool CONDITION, class THEN, class ELSE>	struct IF { typedef THEN type; };

	template  <class THEN, class ELSE>			struct IF<false, THEN, ELSE> 	{ typedef ELSE type; };

				// USE like this:
				//	if sizeof(int) < sizeof(long) then use long else use int
				//	IF< sizeof(int)<sizeof(long), long, int>::type  i;


/////////////////////////////////////////////////////////////////////////////////////////////  TODO IS_POW_OF_TWO
// (x&(x-1)) == 0 
/////////////////////////////////////////////////////////////////////////////////////////////  IPOW
	template<unsigned X, unsigned  P>	struct  ipow		{  enum { value =  ipow<X, P % 2>::value  *  ipow<X*X, P / 2>::value }; };
	template<unsigned X>			struct  ipow<X, 0>	{  enum { value =  1 };  };
	template<unsigned X>			struct  ipow<X, 1>	{  enum { value =  X };  };


/////////////////////////////////////////////////////////////////////////////////////////////  ILOG2
	template<unsigned N>	struct  ilog2		{  static_assert(N%2==0, "ilot2:  N must be even number"); enum { value =  1 + ilog2<N/2>::value}; };
	template<>		struct  ilog2<1>	{  enum { value =  0 }; };
	template<>		struct  ilog2<2>	{  enum { value =  1 }; };

/////////////////////////////////////////////////////////////////////////////////////////////  BINARY

	// useage:   const uint32_t bin_val2=binary<101010>::value;
	template <uint32_t N>	struct binary	 { static uint32_t const	value	= binary<N/10>::value <<1 | N%10; };
	template <> 		struct binary<0> { static uint32_t const	value	= 0; };

/////////////////////////////////////////////////////////////////////////////////////////////  RATIO
			template<long N, long D=1, typename FP=long double>
	struct ratio {
		//template<typename T>  T value() { return T(N)/D;};
		enum { numerator = N,  denominator = D };
		FP	const static 	value = FP(N)/D;
	};

/////////////////////////////////////////////////////////////////////////////////////////////  INT_
	template<long N> struct int_ { enum { value = N }; };

		}
		#endif // LVV_META_H
 

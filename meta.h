
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


//////////////////////////////////////////////////////////////////////////////////////////////  IEEE FLOATING POINT
template<typename T>	struct 	fp_metrics;
template<>		struct 	fp_metrics<float>	{ enum { mantissa_size=23, exponent_size=8 }; };
//////////////////////////////////////////////////////////////////////////////////////////////  META  IF

	// also in /usr/include/boost/detail/select_type.hpp
	template <bool CONDITION, class THEN, class ELSE>	struct IF { typedef THEN type; };

	template  <class THEN, class ELSE>			struct IF<false, THEN, ELSE> 	{ typedef ELSE type; };

				// USE like this:
				//	if sizeof(int) < sizeof(long) then use long else use int
				//	IF< sizeof(int)<sizeof(long), long, int>::type  i;



		}
		#endif // LVV_META_H
 


	// template metaprogramming and conveniance macros
	
	#ifndef LVVLIB_META_H
	#define LVVLIB_META_H

	
	// TODO:  2 check boost: typedef typename tools::promote_args<T>::type result_type;
	// local copy of blitz promote-old.h 
	#include <lvv/blitz-promote-old.h>
	
	#include <boost/type_traits.hpp>
	using boost::true_type;
	using boost::false_type;
	using boost::is_integral;
	
        #ifdef __GNUC__
                #define PURE         __attribute__((const))                                                                                                    
        #else
                #define PURE
        #endif

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


//////////////////////////////////////////////////////////////////////////////////////////////  META  IF

	template <bool condition, class Then, class Else>
	struct IF { typedef Then RET; };

	template  <class Then, class Else>
	struct IF<false, Then, Else> 	{ typedef Else RET; };

	// USE like this:
	// if sizeof(int) < sizeof(long) then use long else use int
	// IF< sizeof(int)<sizeof(long), long, int>::RET  i;



    }
    #endif // LVVMATH_H
    

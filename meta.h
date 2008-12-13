
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

	#include <boost/static_assert.hpp>
//		#define  static_assert	BOOST_STATIC_ASSERT
//////////////////////////////////////////////////////////////////////////////////////////////  STATIC ASSERT

/*
	#ifdef __GNUC__
		#define STATIC_ASSERT_HELPER(expr, msg) ( !!sizeof (struct { unsigned int STATIC_ASSERTION__##msg: (expr) ? 1 : -1; } ))
		#define STATIC_ASSERT(expr, msg)  extern int (*assert_function__(void)) [STATIC_ASSERT_HELPER(expr, msg)]
	#else
		#define STATIC_ASSERT(expr, msg)   \
		extern char STATIC_ASSERTION__##msg[1]; \
		extern char STATIC_ASSERTION__##msg[(expr)?1:2]
	#endif 
*/
/*
	#define STATIC_ASSERT(expr, msg)               \
	{                                              \
	    char STATIC_ASSERTION__##msg[(expr)?1:-1]; \
	    (void)STATIC_ASSERTION__##msg[0];          \
	}

*/
/*
#define STATIC_ASSERT(x, error) \
do { \
    const static char error[(x)?1:-1];\
} while(0)
*/

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



		}
		#endif // LVV_META_H
 

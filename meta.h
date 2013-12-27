// meta.h - template metaprogramming and convenience macros (obsolete)
// Part of lvvlib - https://github.com/lvv/lvvlib
// Copyright (c) 2000-2013
// Leonid Volnitsky (Leonid@Volnitsky.com)

					
					#ifndef LVV_META_H
					#define LVV_META_H

					#ifdef __GXX_EXPERIMENTAL_CXX0X__
	#include	<type_traits>
					#endif
	#include	<stdint.h>
	

	//#include	<cassert>
	//#include	<boost/type_traits/integral_constant.hpp>
	#define		LVV_TRUE_TYPE		std::tr1::true_type
	#define		LVV_FALSE_TYPE		std::tr1::false_type
				// what is std::__false_type ?

	#include	<iostream>
			// for type_descriptor

					#ifdef OLD_PRE_TR1_FIX
						#include	<boost/type_traits.hpp>    
						#define		LVV_PROMOTE1(T)		boost::promote<T>::type
						#define		LVV_IS_INTEGRAL(T)	boost::is_integral<T>::value

						#include	<boost/numeric/ublas/traits.hpp>
						#define		LVV_PROMOTE2(T1,T2)	boost::numeric::ublas::promote_traits<T1,T2>::promote_type
					#endif
//------------------------------------------------------------------------------------------	SELECT BOOST OR TR1
	#include	<boost/numeric/ublas/traits.hpp>
	#define		LVV_PROMOTE2(T1,T2)	boost::numeric::ublas::promote_traits<T1,T2>::promote_type

	#include	<boost/type_traits/promote.hpp>    
	#define		LVV_PROMOTE1(T)		boost::promote<T>::type
	#define		LVV_IS_INTEGRAL(T)	std::tr1::is_integral<T>::value

	/* for promotion:
		for single arg only:
			#include  <boost/type_traits/promote.hpp>    
			boost::promote 

		for 2 args
			#include  <boost/boost/numeric/ublas/traits.hpp>
			boost::numeric:ublas

		old blitz promte:
			//#include <lvv/blitz-promote-old.h>
	
		gcc builtin doesn't works with T from template?
			__gnu_cxx::__promote_2<T1,T2>

		my own, depricated:

			DEPRICATED
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


        #ifdef __GNUC__
                #define PURE         __attribute__((const))                                                                                                    
        #else
                #define PURE
        #endif

						namespace lvv {

////////////////////////////////////////////////////////////////////////////////////////////  TRAIT

	typedef	 int64_t	int_longest_t;
	typedef	 uint64_t	uint_longest_t;
	typedef	 long double	float_longest_t;


//------------------------------------------------------------------------------------------	TODO:  FLOAT DEMOTION
// see after #else at /usr/include/boost-1_37/boost/type_traits/floating_point_promotion.hpp

//------------------------------------------------------------------------------------------	TYPE_DESCRIPTOR
 // by Ariel Badichi, Irfan Zaidi and Leonid Volnitsky
 //  usage:   cout << type_descriptor<const float>;

 template<typename T> struct type_descriptor;

 template<typename T> struct type_descriptor<T *>                {std::ostream & print(std::ostream & out) const{return out << type_descriptor<T>() << " *";            }};
 template<typename T> struct type_descriptor<T &>                {std::ostream & print(std::ostream & out) const{return out << type_descriptor<T>() << " &";            }};
 template<typename T, std::size_t N> struct type_descriptor<T[N]>{std::ostream & print(std::ostream & out) const{return out << type_descriptor<T>() << " [" << N << "]";}};
 template<typename T> struct type_descriptor<const T>            {std::ostream & print(std::ostream & out) const{return out << type_descriptor<T>() << " const";        }};
 template<typename T> struct type_descriptor<volatile T>         {std::ostream & print(std::ostream & out) const{return out << type_descriptor<T>() << " volatile";     }};
 template<typename T> struct type_descriptor<const volatile T>   {std::ostream & print(std::ostream& out) const  {out << "const volatile " << type_descriptor<T>(); return out; } };
 template<typename T> struct type_descriptor<T* const>           {std::ostream & print(std::ostream& out) const  {out << type_descriptor<T>() << "* const"; return out; } };


 template<> struct type_descriptor<char>       {std::ostream & print(std::ostream & out) const{return out << "char";         }}; // without this compile error
 template<> struct type_descriptor<int8_t>     {std::ostream & print(std::ostream & out) const{return out << "int8_t";     }};
 template<> struct type_descriptor<uint8_t>    {std::ostream & print(std::ostream & out) const{return out << "uint8_t";    }};
 template<> struct type_descriptor<int16_t>    {std::ostream & print(std::ostream & out) const{return out << "int16_t";    }};
 template<> struct type_descriptor<uint16_t>   {std::ostream & print(std::ostream & out) const{return out << "uint16_t";   }};
 template<> struct type_descriptor<int32_t>    {std::ostream & print(std::ostream & out) const{return out << "int32_t";    }};
 template<> struct type_descriptor<uint32_t>   {std::ostream & print(std::ostream & out) const{return out << "uint32_t";   }};
 template<> struct type_descriptor<int64_t>    {std::ostream & print(std::ostream & out) const{return out << "int64_t";    }};
 template<> struct type_descriptor<uint64_t>   {std::ostream & print(std::ostream & out) const{return out << "uint64_t";   }};
 template<> struct type_descriptor<float>      {std::ostream & print(std::ostream & out) const{return out << "float";      }};
 template<> struct type_descriptor<double>     {std::ostream & print(std::ostream & out) const{return out << "double";     }};
 template<> struct type_descriptor<long double>{std::ostream & print(std::ostream & out) const{return out << "long double";}};

 template<typename T> std::ostream & operator<< (std::ostream & out, const type_descriptor<T> & desc) { return desc.print(out); }


////////////////////////////////////////////////////////////////////////////////////////////  CONTROL STRUCTURE

//------------------------------------------------------------------------------------------	META  IF

	// also in /usr/include/boost/detail/select_type.hpp
	template <bool CONDITION, class THEN, class ELSE>	struct IF { typedef THEN type; };

	template  <class THEN, class ELSE>			struct IF<false, THEN, ELSE> 	{ typedef ELSE type; };

				// USE like this:
				//	if sizeof(int) < sizeof(long) then use long else use int
				//	IF< sizeof(int)<sizeof(long), long, int>::type  i;



////////////////////////////////////////////////////////////////////////////////////////////  META   MATH


//------------------------------------------------------------------------------------------ 	RATIO
			template<long N, long D=1>
	struct ratio_ {
		long const static  numerator = N;
		long const static  denominator = D;
		long const static  value = N/D;
		typedef 	ratio_<N,D>	type;
		template<typename TO> TO static convert() {return TO(N)/D; }
	};

	template<long N> struct int_ : ratio_<N,1> { long const static value=N; };

//------------------------------------------------------------------------------------------	PLUS, MINUS
			template<typename A, typename B>
	struct plus  { typedef 	ratio_<A::numerator*B::denominator  + B::numerator*A::denominator, A::denominator * B::denominator>	type; };

			template<typename A, typename B>
	struct minus { typedef 	ratio_<A::numerator*B::denominator  - B::numerator*A::denominator, A::denominator * B::denominator>	type; };

	

//------------------------------------------------------------------------------------------	TODO IS_POW_OF_TWO

/*
	template<int x, unsigned y>	struct ipower		{ enum { value = x * ipower<x, y-1>::value }; };
	template<int x>			struct ipower<x, 0>	{ enum { value = 1 }; };
	template<unsigned y>		struct ipower<0, y>	{ enum { value = 0 }; };
	template<>			struct ipower<0, 0>	{};
*/

//------------------------------------------------------------------------------------------	IPOW
       template<unsigned X, unsigned  P>       struct  ipow            {  enum { value =  ipow<X, P % 2>::value  *  ipow<X*X, P / 2>::value }; };
       template<unsigned X>                    struct  ipow<X, 0>      {  enum { value =  1 };  };
       template<unsigned X>                    struct  ipow<X, 1>      {  enum { value =  X };  };

 
       //template<float X, unsigned  P>       struct  fpow            {  float const static value =  fpow<X, P % 2>::value  *  fpow<X*X, P / 2>::value }; };
       //template<float X>                    struct  fpow<X, 0>      {  float const static value =  1;  };
       //template<float X>                    struct  fpow<X, 1>      {  float const static value =  X;  };

//------------------------------------------------------------------------------------------	ILOG2
	template<unsigned N>	struct  ilog2		{  
					#ifdef __GXX_EXPERIMENTAL_CXX0X__
					static_assert(N%2==0, "ilot2:  N must be even number");  
					#endif
		enum { value =  1 + ilog2<N/2>::value};
	};

	template<>		struct  ilog2<1>	{  enum { value =  0 }; };
	template<>		struct  ilog2<2>	{  enum { value =  1 }; };

//------------------------------------------------------------------------------------------	BINARY

	// useage:   const uint32_t mask=binary<101010>::value;
	template <uint32_t N>	struct binary	 { static uint32_t const	value	= binary<N/10>::value <<1 | N%10; };
	template <> 		struct binary<0> { static uint32_t const	value	= 0; };

	// useage: cout << to_binary(0x1f);
		template <typename T> inline	
	const char* to_binary(T n) {
		static char	s[500];
		int 		ni;
		size_t 		si;
		for (ni=8*sizeof(T)-1, si=0;   ni>=0;   ni--, si++)  {
			int bit = ((n >> ni) & 1);
			if (bit)	s[si] = '1';
			else    	s[si] = '0';
			if (ni%4==0 && si)  {
				if (ni%8==0 && si)   {  s[++si]=' ';   s[++si]=' '; }
				else			s[++si]=',';
			}
		}
		s[si] = '\0';
		return s;
	    };
	
	// hex
	//
	//for (int i=2*sizeof(int) - 1; i>=0; i--) {
	//	cout << "0123456789ABCDEF"[((n >> i*4) & 0xF)];
	//}
		



//------------------------------------------------------------------------------------------    TODO FIXED NUMBERS
//  TR http://msdn.microsoft.com/en-us/library/ms972705.aspx
//------------------------------------------------------------------------------------------    TODO UNION_CAST
/*
    template<typename From, typename To>
    union Union_Cast {
        From m_from;
        To m_to;
        Union_Cast (const From& from_) : m_from (from_) {}
    };


    float f = Union_Cast<int, float> (my_int).m_to;

	and you can even add some static assert to verify that sizeof(From) == sizeof (To) if you want.
	-------------------
	template<typename From, typename To>
	union union_cast {
	    From from;
	    To   to;

	    union_cast(From from)
		:from(from) { }

	    To getTo() const { return to; }
	};

*/

// TO test http://cocoawithlove.com/2008/04/using-pointers-to-recast-in-c-is-bad.html)
/* #define UNION_CAST(x, destType) \
 	(((union {__typeof__(x) a; destType b;})x).b)
*/

							}
							#endif // LVV_META_H
 

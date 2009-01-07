
	// template metaprogramming and conveniance macros
	
	#ifndef LVV_META_H
	#define LVV_META_H

	
	// TODO:  2 check boost: typedef typename tools::promote_args<T>::type result_type;
	// local copy of blitz promote-old.h 
	//#include <lvv/blitz-promote-old.h>
	
	#include <boost/type_traits/integral_constant.hpp>
		using boost::true_type;
		using boost::false_type;
	#include <boost/type_traits/is_integral.hpp>
		//#include <boost/type_traits.hpp>
		using boost::is_integral;
	#include <iostream>
	
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

/////////////////////////////////////////////////////////////////////////////////////////////  TYPE_DESCRIPTOR
	 // by Ariel Badichi, Irfan Zaidi and Leonid Volnitsky
	// #include <cstddef>

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

/////////////////////////////////////////////////////////////////////////////////////////////  
		}
		#endif // LVV_META_H
 

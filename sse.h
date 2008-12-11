
				#ifndef LVV_SSE_H
				#define LVV_SSE_H
				

#include <lvv/meta.h>

#ifdef __SSE__
	#include <emmintrin.h>
	//#include <immintrin.h>		// immitrin doesn't need ifdef wrapper, but it is only in gcc44
#endif

#include <boost/detail/select_type.hpp>
	using boost::detail::if_true;

				namespace lvv {
/*
// indicator what technoloty is available
struct plain	{};	// no OpenMP, no SSE
struct sse  	{};	// SSE, no OpenMP
struct openmp   {};	// OpenMP + SSE

template<typename T, int N>	struct	select_method			{typedef	plain		type;}; // default method
template<int N>			struct	select_method<float,N>		{typedef	typename IF< (N>127), sse, plain>::type 	type;};

			template<typename T, int N>
struct select_alignment {
	typedef T	elem_t[N]; 
	typedef T	elem_align_t[N] __attribute__((aligned(16))); 

	#ifdef __SSE__
		typedef		typename if_true<(N>127)>::template then<elem_align_t, elem_t>::type		type;
	#else
		typedef		elem_t										type;				
	#endif
};
*/

	
	#define mk_m128(x) *(__m128*)&(x)
	//namespace array {
	template<typename T, int N, int B> class array;
	//template<typename T, int N, int B> const lvv::array<T,N,B>& mk_array(const __m128 m128) { return reinterpret_cast<lvv::array<T,N,B> > (m128); } // is there an overhead?
	template<typename T, int N, int B> const array<T,N,B>& mk_array(const __m128& m128) { return *(array<T,N,B>*)&(m128); } // is there an overhead?
	//}
	//array<float,4,0>& mk_array(const __m128& m128) { return *(array<float,4,0>*)&(m128); } // is there an overhead?

				} // namespace lvv
				#endif // LVV_SSE_H

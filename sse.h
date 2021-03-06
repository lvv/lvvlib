
				#ifndef LVV_SSE_H
				#define LVV_SSE_H
				

#include <lvv/meta.h>

//#include <immintrin.h>		// we can just include  immitrin instead of all these test, but it is only in gcc44
#ifdef __MMX__
	#include <mmintrin.h>
#endif

#ifdef __SSE__
	#include <xmmintrin.h>
#endif

#ifdef __SSE2__
	#include <emmintrin.h>
#endif

#ifdef __SSE3__
	#include <pmmintrin.h>                                                                                                                                      
#endif

#ifdef __SSSE3__
	#include <tmmintrin.h>
#endif

#include <boost/detail/select_type.hpp>
	using boost::detail::if_true;

				namespace lvv {

	

				#ifdef __SSE__
	#define mk_m128(x) *(__m128*)&(x)
	#define mk_m128i(x) *(__m128i*)&(x)
	template<typename T, int N, int B> class array;
	//template<typename T, int N, int B>	array<T,N,B>&	mk_array(const __m128&  V) { return *(array<T,N,B>*)&(V); } // is there an overhead?
	//template<typename T, int N, int B>	const array<T,N,B>&	mk_array(const __m128&  V) { return *(array<T,N,B>*)&(V); } // is there an overhead?


		template<typename T, int N, int B>
		union sse_vector{
			__m128i  m128i;
			array<T,N,B> arr; 
		};

	//template<typename T, int N, int B>	const array<T,N,B>&	mk_array(const __m128i& V) {

	//	template<typename T, int N, int B>
	//const array<T,N,B>&	mk_array(const __m128i& V) {
	//	sse_vector<T,N,B>   SV;
	//	SV.m128i = V;
	//	return  SV.arr;
	//}
	//			#endif // __SSE__
		template<typename T, int N, int B>
	const array<T,N,B>&	mk_array(const __m128i& V) {
		sse_vector<T,N,B>   SV;
		SV.m128i = V;
		return  SV.arr;
	}
				#endif // __SSE__


	// indicator what technology is available
	struct plain	{};	// no OpenMP, no SSE
	struct ooo	{};	// Out of Order Optimization
	struct nofpu	{};	// FPU is not used  (bit twiddle)

	struct mmx  	{};
	struct sse  	{};	// SSE, no OpenMP
	struct sse2  	{};
	struct sse3  	{};
	struct ssse3  	{};

	struct openmp   {};	// OpenMP + SSE
	const unsigned	sse_threshould = 128;

				} // namespace lvv
				#endif // LVV_SSE_H

#ifndef LVV_ARRAY
#define LVV_ARRAY


		#include	<lvv/lvv.h>
		#include	<lvv/math.h>
		#include	<cassert>

		#include	<iostream>
				using std::ostream;
				using std::istream;
				using std::cout;
				using std::endl;

		#include	<iterator>
				using std::ostream_iterator;

		#include	<numeric>
				using std::accumulate;
		#include	<algorithm>
				//using std::max;

		#include <iterator>
		#include <algorithm>
		using std::size_t;

		#include	<cmath> 
				using std::sqrt;
			
		#include 	<lvv/sse.h>

		namespace lvv {

	template<typename T, int N>	struct	select_method			{typedef	plain		type;}; // default method

	#if	defined(__MMX__)  &&  defined(__i386__)
	template<int N>			struct	select_method<int16_t,N>	{typedef	typename IF< (N>127), mmx, plain>::type 	type;};
	#endif

	#ifdef __SSE__
	template<int N>			struct	select_method<float,N>		{typedef	typename IF< (N>127), sse,  plain>::type 	type;};
	#endif

	#ifdef __SSE2__
	template<int N>			struct	select_method<int16_t,N>	{typedef	typename IF< (N>127), sse2, plain>::type 	type;};
	#endif

				template<typename TT, int NN>
	struct select_alignment {
		typedef TT	elem_t[NN]; 
		typedef TT	elem_align_t[NN] __attribute__((aligned(16))); 

		#ifdef __SSE__
			typedef		typename if_true<(NN>127)>::template then<elem_align_t, elem_t>::type		type;
		#else
			typedef		elem_t										type;				
		#endif
	};

		//namespace array {

////////////////////////////////////////////////////////////////////////////////////////////////////   ARRAY CLASS
			template < class T, int N, int B=0>
struct array {


	typename select_alignment<T,N>::type 	elems;

	enum { sz = N, ibg=B, ien=B+N };  // gcc: "a function call cannot appear in a constant-expression" in something like x<V::size()>

      public:
	// type definitions
	typedef T		value_type;
	typedef T *		iterator;
	typedef const T *	const_iterator;
	typedef T &		reference;
	typedef const T &	const_reference;

	typedef int		size_type;
	typedef int		index_type;

	// CTOR 
	
	// n/a (impossible with having aggregate constructor)

	// index
	index_type				ibegin()	const		{ return B; }
	index_type				iend()		const		{ return B + N; }

	// iterator 
	iterator				begin()				{ return elems; }
	iterator				end()				{ return elems + N; }
        const_iterator				begin()		const		{ return elems; }
        const_iterator				end() 		const		{ return elems+N; }

	// reverse iterator
	typedef std::reverse_iterator<iterator>		reverse_iterator;
        typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;

	reverse_iterator			rbegin()			{ return reverse_iterator(end()); }
	reverse_iterator			rend()				{ return reverse_iterator(begin()); }
        const_reverse_iterator			rbegin()	const		{ return const_reverse_iterator(end()); }
        const_reverse_iterator			rend()		const		{ return const_reverse_iterator(begin()); }

	// operator[]
	reference				operator[](int i) throw(char *)	{
		#if  	defined (DOCHECK)   ||   (!defined (NDEBUG)  &&  !defined (NOCHECK))
			if (i < ibegin()  ||  iend() <= i) {
				cerr << "lvv::array::operator[] error: index=" << i <<  " is out of range [" << ibegin() << ".." << iend() << ")  at " << __FILE__ << ":" << __LINE__<< endl ;    
				assert(false);
			}
		#endif 
		return elems[i-B];
	}

	const_reference				operator[](int i) const	 throw(char *) {
		#if  	defined (DOCHECK)   ||   (!defined (NDEBUG)  &&  !defined (NOCHECK))
			if (i < ibegin()  ||  iend() <= i) {
				cerr << "lvv::array::operator[] error: index=" << i <<  " is out of range [" << ibegin() << ".." << iend() <<")  at " << __FILE__ << ":" << __LINE__<< endl;    
				assert(false);
			}
		#endif 
		return elems[i-B];
	}

	reference				at(size_type i)			{ assert(i<N+B && i>=B && "out of range"); return elems[i-B]; }
	const_reference				at(size_type i)	const		{ assert(i<N+B && i>=B && "out of range"); return elems[i-B]; }
	reference				front()				{ return elems[0]; }
	reference				back()				{ return elems[N-1]; }
	const_reference				front()		const		{ return elems[0]; }
	const_reference				back()		const		{ return elems[N-1]; }

	static size_type const			size()				{ return N; }
	static bool				empty()				{ return false; }
	static size_type			max_size()			{ return N; }

	enum { static_size = N };

	void					swap(array<T, N> &y)		{ std::swap_ranges(begin(), end(), y.begin()); }

	const T *				data()	const			{ return elems; }	// tr1 calls this data()
	T *					data()				{ return elems; }

	// assignment with type conversion
	//template <typename T2>	array <T, N, B>	&operator=(const array < T2, N, B > &rhs) { std::copy(rhs.begin(), rhs.end(), begin()); return *this; };
	template <typename T2, int N2, int B2>	array <T, N, B>	&operator=(const array<T2,N2,B2>  &rhs) { std::copy(rhs.begin(), rhs.end(), begin()); return *this; };
	
	//TODO memcpy assignment (without type conversion)

	// assign one value to all elements
	template<typename T2> 	array<T,N,B>&  operator= ( const  T2 value) {  std::fill_n(begin(), size(), value);  return *this; }
	void					assign(const T & value)		{ std::fill_n(begin(), size(), value); }
	//TODO memset scalar assignment

	template <typename TT, int NN,  int BB> friend   ostream& operator<< (ostream& os, const array<TT,NN,BB> a);
	template <typename TT, int NN,  int BB> friend   istream& operator>> (istream& is,       array<TT,NN,BB>&  a);


//// ================================================================================================================ SUM

	template<typename method_type>	T	sum()	const	{ return sum_impl(method_type(), T()); } 			// explicit
					T	sum()	const	{ return sum_impl(typename select_method<T,N>::type(), T()); }	// auto-selection

	T	sum_impl (plain, T) 		const	{ return std::accumulate(begin(), end(), T()); };			// default impt

	#ifdef __SSE__
	float	sum_impl (sse, float)		const	{ DBG cerr << " max<sse,float> " << N << "(" << N-N%8 <<")"; 
		float  __attribute__((aligned(16))) sum4[4] = {};
		double sum = 0;
		__m128 _0, _1, _2, _3;

		for (int i=0; i<N-32; i+=32) {
			  _0 = mk_m128(elems[i+0]) ;	_0 = _mm_add_ps(_0, mk_m128(elems[i+4 ])); 
			  _1 = mk_m128(elems[i+8]) ;	_1 = _mm_add_ps(_1, mk_m128(elems[i+12])); 
			  _2 = mk_m128(elems[i+16]);	_2 = _mm_add_ps(_2, mk_m128(elems[i+20])); 
			  _3 = mk_m128(elems[i+24]);	_3 = _mm_add_ps(_3, mk_m128(elems[i+28])); 

			  _0 = _mm_add_ps(_0, _1);
			  _2 = _mm_add_ps(_2, _3);
			  _0 = _mm_add_ps(_0, _2);

			_mm_store_ps(sum4,_0);
			sum +=  (sum4[0]+sum4[1]) + (sum4[2]+sum4[3]);		// TODO: inline assambly; mm_dp_ps (SSE41)
		}
		return (float) sum;
	}
	#endif 
//// ================================================================================================================ MIN
T					min() 		const	{ return *std::min_element(begin(), end()); };

//// ================================================================================================================ MAX
template<typename method_type>	T	max()	const	{ return max_impl(method_type(), T()); } 			// explicit
T					max()	const	{ return max_impl(typename select_method<T,N>::type(), T()); }	// auto-selection
		// default template parameter:  Due to an unfortunate oversight, the standard simply bans
		// default arguments for template parameters for a function template. Voted to be corrected in the next standard


T	max_impl (plain, T) 		const { T max=elems[0]; for(size_t i=1; i<N; i++) max = ((max>elems[i]) ? max : elems[i]); return max; }

	
// ----------------------------------------------------------------------------------------------------------------- MAX FLOAT-32  NO-FPU
			//  TO BENCHMARK, TO FIX STILE: no-fpu max:  http://bits.stephan-brumme.com/minmax.html
			int select(int x, int y, int ifXisSmaller, int ifYisSmaller) {
				int diff  = x - y;
				// sets bit31 to 0xFFFFFFFF if x<y, else 0x00000000
				int bit31 = diff >> 31;

				// return ifXisSmaller if x is smaller than y, else y
				return (bit31 & (ifXisSmaller ^ ifYisSmaller)) ^ ifYisSmaller;
			  }

			int minimum(int x, int y)  {
				// if x<y then return x, else y
				return select(x,y,x,y);
			  }

			int maximum(int x, int y) {
				// if x<y then return y, else x
				return select(x,y,y,x);
			  }

T	max_impl (nofpu, float) 		const {
	T max=elems[0];
	for(size_t i=1; i<N; i++) max = ((max>elems[i]) ? max : elems[i]);  // TO REWRITE WITH above select
	return max;
 }


// ----------------------------------------------------------------------------------------------------------------- MAX FLOAT-32

	#ifdef __SSE__
float	max_impl (sse, float) 			const	{ // DBG cerr <<" max<sse,float> " << N << "(" << N-N%8 <<")"; 
	const unsigned	sse_size	= 4;
	const unsigned	unroll		= 2;
	const unsigned	prefetch	= 512;
	const unsigned	cycle_step	= unroll * sse_size;
	const size_t	sse_cycles	= N - N % cycle_step;
									static_assert (N>=sse_size*unroll, "{{{ SSE can be used only for N>=8 }}}");

	__m128 m1 = mk_m128(elems[0]);
	__m128 m2 = mk_m128(elems[sse_size]);

	for (size_t i= cycle_step;  i < sse_cycles; i+=cycle_step) { 			// SSE
		  m1 = _mm_max_ps(m1, mk_m128(elems[i]) );
		  m2 = _mm_max_ps(m2, mk_m128(elems[i+sse_size]) );
		 __builtin_prefetch((void*)&elems[i+prefetch],0,0);      
	}

	m1 = _mm_max_ps(m1, m2);

	T reg_save[sse_size]  __attribute__((aligned(16)));
	_mm_store_ps (reg_save, m1);
	T reg_max   = reinterpret_cast<const array<T,sse_size>* >     (reg_save)            -> max<plain>();    // vector register max
	T tail_max  = reinterpret_cast<const array<T,N-sse_cycles>* > (&elems[sse_cycles])  -> max<plain>();    // tail max
	return  std::max(reg_max, tail_max);
 }
 	#endif

	
// ----------------------------------------------------------------------------------------------------------------- MAX  INT-16
	#ifdef __SSE__
int16_t	max_impl (sse2, int16_t)		const { // DBG cerr << " max<sse2,int16> " << N << "(" << N-N%8 << ")"; 
	const unsigned	sse_size	= 8;
	const unsigned	unroll		= 2;
	const unsigned	prefetch	= 1024;
	const unsigned	cycle_step	= unroll * sse_size;
	const size_t	sse_cycles	= N - N % cycle_step;
									static_assert (N>=sse_size*unroll, "{{{ SSE can be used only for N>=8 }}}");

	__m128i m1 = mk_m128i(elems[0]);
	__m128i m2 = mk_m128i(elems[sse_size]);

	for (size_t i= cycle_step;  i < sse_cycles; i+=cycle_step) {
		  m1 = _mm_max_epi16(m1, mk_m128i(elems[i]) );
		  m2 = _mm_max_epi16(m2, mk_m128i(elems[i+sse_size]) );
		 __builtin_prefetch((void*)&elems[i+prefetch],0,0);      
	}

	m1 = _mm_max_epi16(m1, m2);

	T reg_save[sse_size]  __attribute__((aligned(16)));
	_mm_store_si128 ((__m128i *)reg_save, m1);
	T reg_max   = reinterpret_cast<const array<T,sse_size>* >     (reg_save)           -> max<plain>();    // vector register max
	T tail_max  = reinterpret_cast<const array<T,N-sse_cycles>* > (&elems[sse_cycles]) -> max<plain>();    // tail max
	return  std::max(reg_max, tail_max);
 }
 	#endif

 };
////////////////////////////////////////////////////////////////////////////////////////////////////   END ARRAY


// comparisons
 template<class T, int N, int B> bool operator==(const array<T, N, B> &x, const array<T, N, B> &y) { return std::equal(x.begin(), x.end(), y.begin()); }
 template<class T, int N, int B> bool operator< (const array<T, N, B> &x, const array<T, N, B> &y) { return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }
 template<class T, int N, int B> bool operator!=(const array<T, N, B> &x, const array<T, N, B> &y) { return !(x == y); }
 template<class T, int N, int B> bool operator> (const array<T, N, B> &x, const array<T, N, B> &y) { return   y < x; }
 template<class T, int N, int B> bool operator<=(const array<T, N, B> &x, const array<T, N, B> &y) { return !(y < x); }
 template<class T, int N, int B> bool operator>=(const array<T, N, B> &x, const array<T, N, B> &y) { return !(x < y); }

// global swap()
 template < class T, size_t N, int B > inline void swap(array < T, N, B > &x, array < T, N, B > &y) { x.swap(y); }

// array op= scalar  ( conflict with google sparsehash if we not spell out type)
 template<typename T,int N, int B, typename D>  array<T,N,B>&  operator+=(array<T,N,B>& A, const D d) { for(typename array<T,N,B>::iterator it =  A.begin(); it != A.end(); it++)  *it += d; return A; }
 template<typename T,int N, int B, typename D>  array<T,N,B>&  operator-=(array<T,N,B>& A, const D d) { for(typename array<T,N,B>::iterator it =  A.begin(); it != A.end(); it++)  *it -= d; return A; }
 template<typename T,int N, int B, typename D>  array<T,N,B>&  operator*=(array<T,N,B>& A, const D d) { for(typename array<T,N,B>::iterator it =  A.begin(); it != A.end(); it++)  *it *= d; return A; }
 template<typename T,int N, int B, typename D>  array<T,N,B>&  operator/=(array<T,N,B>& A, const D d) { for(typename array<T,N,B>::iterator it =  A.begin(); it != A.end(); it++)  *it /= d; return A; }
 //template<typename T,int N, int B, typename D>  array<T,N,B>&  operator= (array<T,N,B>& A, const D d) { for(typename array<T,N,B>::iterator it =  A.begin(); it != A.end(); it++)  *it  = d; return A; }

// array op= array  
 template<typename T,int N, int B> array<T,N,B>& operator+=(array<T,N,B>& LA, const array<T,N,B>& RA) { typename array<T,N,B>::iterator lit =  LA.begin(); typename array<T,N,B>::const_iterator rit =  RA.begin(); for(; lit != LA.end();)  *lit++  +=  *rit++; return LA; }
 template<typename T,int N, int B> array<T,N,B>& operator-=(array<T,N,B>& LA, const array<T,N,B>& RA) { typename array<T,N,B>::iterator lit =  LA.begin(); typename array<T,N,B>::const_iterator rit =  RA.begin(); for(; lit != LA.end();)  *lit++  -=  *rit++; return LA; }
 template<typename T,int N, int B> array<T,N,B>& operator*=(array<T,N,B>& LA, const array<T,N,B>& RA) { typename array<T,N,B>::iterator lit =  LA.begin(); typename array<T,N,B>::const_iterator rit =  RA.begin(); for(; lit != LA.end();)  *lit++  *=  *rit++; return LA; }
 template<typename T,int N, int B> array<T,N,B>& operator/=(array<T,N,B>& LA, const array<T,N,B>& RA) { typename array<T,N,B>::iterator lit =  LA.begin(); typename array<T,N,B>::const_iterator rit =  RA.begin(); for(; lit != LA.end();)  *lit++  /=  *rit++; return LA; }

// array op array  
 template<typename T,int N, int B>
array<T,N,B>&&  operator+(const array<T,N,B>& LA, const array<T,N,B>& RA) {

 	array<T,N,B> RES;
	for(int i=B;  i<N+B;  i++) {
		RES[i] = LA[i] + RA[i];
		PR4(i,LA[i], RA[i],RES[i]);
	}
	return std::move(RES);
 }


			template<typename T,int N, int B>  T
dot_prod 		(const array<T,N,B>& LA, const array<T,N,B>& RA) {
	typename array<T,N,B>::const_iterator lit =  LA.begin();
	typename array<T,N,B>::const_iterator rit =  RA.begin();
	T sum = 0;
	while(lit != LA.end())  sum += (*lit++  *  *rit++);
	return  sum;
 }

			template<typename T,int N, int B>   array<T,N,B>
operator-		(array<T,N,B> A) { // A passed by value
	typename array<T,N,B>::iterator  it =  A.begin();
	for(;it != A.end(); it++)     *it = -*it;
	return  A;
 }
			template<typename T,int N, int B>  T
norm2 		(const array<T,N,B>& A) {
	typename array<T,N,B>::const_iterator  it =  A.begin();
	T sum = 0;
	for(;it != A.end(); it++)    sum  +=  *it * *it;
	return  sqrt(sum);
 }

			template<typename T,int N, int B>  T
distance_norm2 		(const array<T,N,B>& LA, const array<T,N,B>& RA) {
	typename array<T,N,B>::const_iterator lit =  LA.begin();
	typename array<T,N,B>::const_iterator rit =  RA.begin();
	T sum = 0;
	while(lit != LA.end())  sum  +=  pow2(*lit++  -  *rit++) ;
	return  sqrt(sum);
 }

		template <typename T, int N, int B>
		std::ostream&
operator<<  (ostream& os, const array<T,N,B> A)  {		// WHY: if we change A to const-ref or rval-ref it will pring garbage? 
	//os << format("[%d..%d]=") %A.ibegin() %(A.iend()-1);
	
	//if (N > 10)  std::cout << endl;
	//std::cout << "[" << A.ibegin() << ".." << A.iend() << "] ";
	//if (N > 10)  std::cout << endl;

	copy (A.begin(),  A.end(),  ostream_iterator<T>(os, " "));
	//for (long i=A.ibegin();  i< A.iend();  i++)
	return os;
 };


		template <typename T, int N, int B>
		std::istream&
operator>>  (istream& is, array<T,N,B>& A)  {
 	for (size_t i=B;  i<B+N;  i++)	 is >> A[i];
	return is;
 };


template <typename T, int N> 		class vector: public array<T,N,1> {}; // index start from 1

template <typename T, int N1, int N2, int B1=1, int B2=1>	struct  matrix: public array<array<T,N1,B1>,N2,B2> {
	enum { sz1 = N1, sz2=N2, sz0=N1*N2 };
	const T *				data()	const			{ return this->front().data(); }	// tr1 calls this data()
	T *					data()				{ return this->front().data(); }
 };
			};	// namespace lvv
			#endif	// LVV_ARRAY

		// TODO 
		//	try to inherit from tr1:array - 	/usr/local/include/c++/4.4.0/tr1_impl/array
		//	
		//	tensor: http://www.sitmo.com/doc/A_Simple_and_Extremely_Fast_CPP_Template_for_Matrices_and_Tensors
		//
		//	memcpy specialization: file:///tr/boost-trunk.svn/libs/type_traits/doc/html/boost_typetraits/examples/copy.html
		//
		//	A+A (expresions templates:
		// 		http://aszt.inf.elte.hu/~gsd/visit/eindhoven/material/ch01s06.html
		// 		Portable Expression Template Engine	http://acts.nersc.gov/pete/
		// 		Tiny Vector Matrix library - http://tvmet.sourceforge.net/

						// According to the language definition, aggregate initialization only works
						// for aggregate types. An array or class type is not an aggregate if it has
						// any user-declared constructors, any private or protected nonstatic data
						// members, any base classes, or any virtual functions.
					
		// overlaying arrays with 'placement new':
		//
		//	typedef array <int,4> A;
		//	int init[] = {1, 2, 3, 4};
		//	A& a = *new (init) A;
		//	
		//	Of course, this is equivalent to
		//	
		//	array<int,4> a = {1, 2, 3, 4};



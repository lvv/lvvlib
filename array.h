#ifndef LVV_ARRAY
#define LVV_ARRAY

		// TODO 
		// tensor: http://www.sitmo.com/doc/A_Simple_and_Extremely_Fast_CPP_Template_for_Matrices_and_Tensors
		// memcpy specialization: file:///tr/boost-trunk.svn/libs/type_traits/doc/html/boost_typetraits/examples/copy.html

						// According to the language definition, aggregate initialization only works
						// for aggregate types. An array or class type is not an aggregate if it has
						// any user-declared constructors, any private or protected nonstatic data
						// members, any base classes, or any virtual functions.
		#include	<lvv/lvv.h>
		#include	<lvv/math.h>
		#include	<cassert>

		#include	<iostream>
				using std::ostream;
				using std::cout;
				using std::endl;

		#include	<iterator>
				using std::ostream_iterator;

		#include	<numeric>
				using std::accumulate;

		//#include	<boost/format.hpp>
				//using boost::format;

		#include <iterator>
		#include <algorithm>
		using std::size_t;

		#include	<cmath> 
				using std::sqrt;
			
		#include 	<lvv/sse.h>

		namespace lvv {


template < class T, int N, int BEGIN=0> class array {

      public:

	/*
	typedef T	elem_t[N]; 
	typedef T	elem_align_t[N] __attribute__((aligned(16))); 
	*/

	/*
	#ifdef __SSE__
		typename if_true<(N>127)>::template then<elem_align_t, elem_t>::type  elems;
	#else
		elem_t	elems;				
	#endif
	*/
	typename select_alignment<T,N>::type	elems;

	enum { sz = N, ibg=BEGIN, ien=BEGIN+N };  // gcc: "a function call cannot appear in a constant-expression" in something like x<V::size()>

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
	
	// n/a (imposible with having aggrigate constructor)


	// index
	index_type				ibegin()	const		{ return BEGIN; }
	index_type				iend()		const		{ return BEGIN + N; }

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
				//format msg("lvv::array::operator[] error: index=%d out of range [%d..%d)  at " __FILE__ ":%d" );    
				cerr << "lvv::array::operator[] error: index=" << i <<  "out of range [" << ibegin() << ".." << iend()
					<< ")  at " << __FILE__ << ":" << __LINE__ ;    
				//msg %i %ibegin() %iend() %__LINE__;
				//throw  msg.str().c_str();
				assert(false);
			}
		#endif 
		return elems[i-BEGIN];
		// TODO __OPTIMIZE__ - is defined in all optimizing compilations,
	}

	const_reference				operator[](int i) const	 throw(char *) {
		#if  	defined (DOCHECK)   ||   (!defined (NDEBUG)  &&  !defined (NOCHECK))
			if (i < ibegin()  ||  iend() <= i) {
				//format msg("lvv::array::operator[] error: index=%d out of range [%d..%d)  at " __FILE__ ":%d" );    
				cerr << "lvv::array::operator[] error: index=" << i <<  "out of range [" << ibegin() << ".." << iend() <<")  at " << __FILE__ << ":" << __LINE__;    
				//msg %i %ibegin() %iend() %__LINE__;
				//cerr << msg << endl;
				//throw  msg.str().c_str();
				assert(false);
			}
		#endif 
		return elems[i-BEGIN];
	}

	reference				at(size_type i)			{ assert(i<N+BEGIN && i>=BEGIN && "out of range"); return elems[i-BEGIN]; }
	const_reference				at(size_type i)	const		{ assert(i<N+BEGIN && i>=BEGIN && "out of range"); return elems[i-BEGIN]; }
	reference				front()				{ return elems[0]; }
	reference				back()				{ return elems[N-1]; }
	const_reference				front()		const		{ return elems[0]; }
	const_reference				back()		const		{ return elems[N-1]; }

	static size_type const			size()				{ return N; }
	static bool				empty()				{ return false; }
	static size_type			max_size()			{ return N; }

	enum { static_size = N };

	void					swap(array<T, N> &y)		{ std::swap_ranges(begin(), end(), y.begin()); }
	const T *				c_array()	const		{ return elems; }
	T *					c_array()			{ return elems; }

        const T*				data()		const		{ return elems; }
        T*					data()				{ return elems; }

	// assignment with type conversion
	template <typename T2>	array <T, N, BEGIN>	&operator=(const array < T2, N, BEGIN > &rhs) { std::copy(rhs.begin(), rhs.end(), begin()); return *this; };
	
	//TODO memcpy assignment (without type conversion)

	// assign one value to all elements
	template<typename T2> 	array<T,N,BEGIN>&  operator= ( const  T2 value) {  std::fill_n(begin(), size(), value);  return *this; }
	void					assign(const T & value)		{ std::fill_n(begin(), size(), value); }
	//TODO memset scalar assignment

	template <typename TT, int NN,  int BB> friend   ostream& operator<< (ostream& os, array<TT,NN,BB>  a);

	T					sum() 		const	{ return std::accumulate(begin(), end(), 0); };
	//T					max() 		const	{ return *std::max_element(begin(), end()); };
	template<typename method_type>	T	max()		const	{ return max_impl(method_type()); } 			// explicit template selecton	
					T	max()		const	{ return max_impl(typename select_method<T,N>::type()); }	// auto-selection (no template)
						// default template paramter:  Due to an unfortunate oversight, the standard simply bans
						// default arguments for template parameters for a function template. Voted
						// to be corrected in the next standard

	T max_impl (plain)  const { cerr <<" max<plain>" << N; return *std::max_element(begin(), end()); }
	T max_impl (sse)    const { cerr <<" max<sse>" << N << "(" << N-N%8 <<")"; 
		const unsigned	sse_size	= 4;
		const unsigned	unroll		= 2;
										// commented out: boost-1.37/SVN  error
										//BOOST_STATIC_ASSERT((N>=sse_size*unroll));  
										//STATIC_ASSERT(N>=sse_size*unroll,"sse can be used for N>=8");
		const unsigned	prefetch	= 512;
		const unsigned	cycle_step	= unroll * sse_size;
		const size_t	sse_cycle	= N - N % cycle_step;

		__m128 m1 = mk_m128(elems[0]);
		__m128 m2 = mk_m128(elems[sse_size]);

		for (int i= cycle_step;  i < sse_cycle; i+=cycle_step) { 			// SSE
			PR1(i);
			  m1 = _mm_max_ps(m1, mk_m128(elems[i]) );
			  m2 = _mm_max_ps(m2, mk_m128(elems[i+sse_size]) );
			 __builtin_prefetch((void*)&elems[i+prefetch],0,0);      
		}

		m1 = _mm_max_ps(m1, m2);
		return  std::max(mk_array<float,4,0>(m1).max<plain>()   ,    (*(array<float,N-sse_cycle,0> *) (&elems[sse_cycle])).max<plain>() );
	}
	
};
//////////////////////////////////////////////////////////////////////////////////////////////   END ARRAY



// comparisons
template<class T, int N, int B> bool operator==(const array<T, N, B> &x, const array<T, N, B> &y) { return std::equal(x.begin(), x.end(), y.begin()); }
template<class T, int N, int B> bool operator< (const array<T, N, B> &x, const array<T, N, B> &y) { return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }
template<class T, int N, int B> bool operator!=(const array<T, N, B> &x, const array<T, N, B> &y) { return !(x == y); }
template<class T, int N, int B> bool operator> (const array<T, N, B> &x, const array<T, N, B> &y) { return   y < x; }
template<class T, int N, int B> bool operator<=(const array<T, N, B> &x, const array<T, N, B> &y) { return !(y < x); }
template<class T, int N, int B> bool operator>=(const array<T, N, B> &x, const array<T, N, B> &y) { return !(x < y); }

// global swap()
template < class T, size_t N, int B > inline void swap(array < T, N, B > &x, array < T, N, B > &y) { x.swap(y); }


// array op= scallar  ( conflict with google sparsehash if we not spell out type)
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
 operator<<  (ostream& os, array<T,N,B> A)  {
	//os << format("[%d..%d]=") %A.ibegin() %(A.iend()-1);
	copy (A.begin(),  A.end(),  ostream_iterator<T>(os, " "));
	return os;
 };


template <typename T, int N> 		class vector: public lvv::array<T,N,1> {}; // index start from 1
template <typename T, int N1, int N2, int B1=1, int B2=1>	class matrix: public array<array<T,N1,B1>,N2,B2> {
	enum { sz1 = N1, sz2=N2, sz0=N1*N2 };
	// operator()(int i, int j) { return elems[i][j]; }
};

			};	// namespace lvv
			#endif	// LVV_ARRAY

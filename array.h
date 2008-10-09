#ifndef LVV_ARRAY
#define LVV_ARRAY

// TODO  tensor: http://www.sitmo.com/doc/A_Simple_and_Extremely_Fast_CPP_Template_for_Matrices_and_Tensors

#include <cassert>
#include <iostream>
using std::ostream;
using std::cout;
using std::endl;
#include <iterator>
using std::ostream_iterator;
#include <numeric>
using std::accumulate;

#include <boost/format.hpp>
using boost::format;

#include <iterator>
#include <algorithm>
using std::size_t;

namespace lvv {

template < class T, int N, int BEGIN=0> class array {
      public:
	T elems[N];				
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
	//array<T,N,BEGIN>(T init_value) { for (size_type i=0;  i<N;  i++)  elems[i]=init_value; } // TODO specialization for memset-to-0 
	//init(T init_value) { for (size_type i=0;  i<N;  i++)  elems[i]=init_value; } // TODO specialization for memset-to-0 
	//array<T,N,BEGIN>() {}

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
				format msg("lvv::array::operator[] error: index=%d out of range [%d..%d)  at " __FILE__ ":%d" );    
				msg %i %ibegin() %iend() %__LINE__;
				throw  msg.str().c_str();
			}
		#endif 
		return elems[i-BEGIN];
		// TODO __OPTIMIZE__ - is defined in all optimizing compilations,
	}

	const_reference				operator[](int i) const	 throw(char *) {
		#if  	defined (DOCHECK)   ||   (!defined (NDEBUG)  &&  !defined (NOCHECK))
			if (i < ibegin()  ||  iend() <= i) {
				format msg("lvv::array::operator[] error: index=%d out of range [%d..%d)  at " __FILE__ ":%d" );    
				msg %i %ibegin() %iend() %__LINE__;
				cerr << msg << endl;
				throw  msg.str().c_str();
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
	template <typename T2>	array <T, N>	&operator=(const array < T2, N > &rhs) { std::copy(rhs.begin(), rhs.end(), begin()); return *this; };

	// assign one value to all elements
	void					assign(const T & value)		{ std::fill_n(begin(), size(), value); }
	template <typename TT, int NN,  int BB> friend   ostream& operator<< (ostream& os, array<TT,NN,BB>  a);
	//template <typename TT, int NN, int BB> 	friend   gsl_vector* operator<<  (gsl_vector* gV, array<TT,NN,BB> A);

	// kitchen sink
	T					sum() 		const		{ return accumulate(begin(), end(), 0); };
	
};

/*
// comparisons  (TODO, add BEGIN)
template<class T, int N> bool operator==(const array<T, N> &x, const array<T, N> &y) { return std::equal(x.begin(), x.end(), y.begin()); }
template<class T, int N> bool operator< (const array<T, N> &x, const array<T, N> &y) { return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }
template<class T, int N> bool operator!=(const array<T, N> &x, const array<T, N> &y) { return !(x == y); }
template<class T, int N> bool operator> (const array<T, N> &x, const array<T, N> &y) { return   y < x; }
template<class T, int N> bool operator<=(const array<T, N> &x, const array<T, N> &y) { return !(y < x); }
template<class T, int N> bool operator>=(const array<T, N> &x, const array<T, N> &y) { return !(x < y); }
*/
// global swap()
template < class T, size_t N > inline void swap(array < T, N > &x, array < T, N > &y) { x.swap(y); }



// array op= scallar  ( conflict with google sparsehash if we not spell out type)
template<typename T,int N, int B, typename D>  array<T,N,B>&  operator+=(array<T,N,B> &A, D d) { for(typename array<T,N,B>::iterator it =  A.begin(); it != A.end(); it++)  *it += d; return A; }
template<typename T,int N, int B, typename D>  array<T,N,B>&  operator-=(array<T,N,B> &A, D d) { for(typename array<T,N,B>::iterator it =  A.begin(); it != A.end(); it++)  *it -= d; return A; }
template<typename T,int N, int B, typename D>  array<T,N,B>&  operator*=(array<T,N,B> &A, D d) { for(typename array<T,N,B>::iterator it =  A.begin(); it != A.end(); it++)  *it *= d; return A; }
template<typename T,int N, int B, typename D>  array<T,N,B>&  operator/=(array<T,N,B> &A, D d) { for(typename array<T,N,B>::iterator it =  A.begin(); it != A.end(); it++)  *it /= d; return A; }


// array op= array  
template<typename T,int N, int B> array<T,N,B>& operator+=(array<T,N,B>& LA, const array<T,N,B>& RA) { typename array<T,N,B>::iterator lit =  LA.begin(); typename array<T,N,B>::const_iterator rit =  RA.begin(); for(; lit != LA.end();)  *lit++  +=  *rit++; return LA; }
template<typename T,int N, int B> array<T,N,B>& operator-=(array<T,N,B>& LA, const array<T,N,B>& RA) { typename array<T,N,B>::iterator lit =  LA.begin(); typename array<T,N,B>::const_iterator rit =  RA.begin(); for(; lit != LA.end();)  *lit++  -=  *rit++; return LA; }
template<typename T,int N, int B> array<T,N,B>& operator*=(array<T,N,B>& LA, const array<T,N,B>& RA) { typename array<T,N,B>::iterator lit =  LA.begin(); typename array<T,N,B>::const_iterator rit =  RA.begin(); for(; lit != LA.end();)  *lit++  *=  *rit++; return LA; }
template<typename T,int N, int B> array<T,N,B>& operator/=(array<T,N,B>& LA, const array<T,N,B>& RA) { typename array<T,N,B>::iterator lit =  LA.begin(); typename array<T,N,B>::const_iterator rit =  RA.begin(); for(; lit != LA.end();)  *lit++  /=  *rit++; return LA; }
/*
		template<typename LT,typename RT,int N, int B> 
		typename lvv::array<LT,N,B>& 
operator+=(lvv::array<LT,N,B>& LA, lvv::array<RT,N,B>& RA) {
	typename lvv::array<LT,N,B>::iterator lit =  LA.begin();
	typename lvv::array<RT,N,B>::iterator rit =  RA.begin();
	for(; lit != LA.end();)  *lit++  +=  *rit++;
	return LA;
}*/
//template<typename LT,int N, int B, typename T2>  array<T,N,B>&  operator-=(array<T,N,B> &A, D d) { for(typename array<T,N,B>::iterator it =  A.begin(); it != A.end(); it++)  *it -= d; return A; }
//template<typename LT,int N, int B, typename T2>  array<T,N,B>&  operator*=(array<T,N,B> &A, D d) { for(typename array<T,N,B>::iterator it =  A.begin(); it != A.end(); it++)  *it *= d; return A; }
//template<typename LT,int N, int B, typename T2>  array<T,N,B>&  operator/=(array<T,N,B> &A, D d) { for(typename array<T,N,B>::iterator it =  A.begin(); it != A.end(); it++)  *it /= d; return A; }



// CONDOR
#ifdef  _INCLUDE_VECTOR_H
	
			template <typename T, int N>
			array<T,N>&
	operator<<  (array<T,N>& A, CONDOR::Vector& cV)  {        // operator= should be member, so we are using operator<<
								assert(A.size()==cV.sz());  assert(A.ibegin()==0);  
		for (int i=A.ibegin(); i<A.iend(); i++)    A[i] = cV[i];
		return A;
	 };

			template <typename T, int N>
			CONDOR::Vector&
	 operator<<  (CONDOR::Vector& cV, const array<T,N>& A)  {
		cV.setSize(A.size());				assert(A.size()==cV.sz());  assert(A.ibegin()==0);  
		for (int i=A.ibegin(); i<A.iend(); i++)    cV[i] = A[i];
		return cV;
	 };
#endif

#ifdef __GSL_VECTOR_H__
	// this comment was inside class
	//array <T, N>	&operator=(const gsl_vector*  rhs)       { assert(N==rhs->size);   for (int i=ibegin(); i<iend(); i++)  elems[i-BEGIN] = gsl_vector_get(rhs, i); return *this; };

	/*  if(?) we will have constructor we can not use {{}} initilizer;
	array<T,N,BEGIN>(const gsl_vector*  rhs)   {
						assert(N==rhs->size);   
						assert(ibegin()==gsl_vector_min_index(rhs));   
						assert(iend()-1==gsl_vector_max_index(rhs));   
		for (int i=ibegin(); i<iend(); i++)  elems[i-BEGIN] = gsl_vector_get(rhs, i);
	}*/

	
			template <typename T, int N>
			array<T,N>&
	 operator<<  (array<T,N>& A, const gsl_vector* gV)  {	// operator= should be member, so we are using operator<<
								assert(A.size()==gV->size);  assert(A.ibegin()==0);  
		for (int i=A.ibegin(); i<A.iend(); i++)  A[i] = gsl_vector_get(gV, i);
		return A;
	 };

			template <typename T, int N, int B>
			gsl_vector*
	 operator<<  (gsl_vector* gV, array<T,N,B>& A)  {
								assert(A.size()==gV->size);  assert(A.ibegin()==0);  
		for (int i=A.ibegin(); i<A.iend(); i++)  gsl_vector_set(gV, i, A[i]);
		return gV;
	 };
#endif
		template <typename T, int N, int B>
		ostream&
 operator<<  (ostream& os, array<T,N,B> A)  {
	os << format("[%d..%d]=") %A.ibegin() %(A.iend()-1);
	copy (A.begin(),  A.end(),  ostream_iterator<T>(os, " "));
	return os;
 };


template <typename T, int N1, int N2> class matrix: public array<array<T,N1,1>,N2,1> { enum { sz1 = N1, sz2=N2, sz0=N1*N2 }; };


};	// namespace lvv
#endif	// LVV_ARRAY

#ifndef BOOST_ARRAY_HPP
#define BOOST_ARRAY_HPP

#include <cstddef>
#include <stdexcept>
#include <cassert>

#include <iterator>

#include <boost/throw_exception.hpp>
#include <algorithm>
using std::size_t;

template < class T, size_t N, int BEGIN=0> class array {
      public:
	T elems[N];				

      public:
	// type definitions
	typedef T		value_type;
	typedef T *		iterator;
	typedef const T *	const_iterator;
	typedef T &		reference;
	typedef const T &	const_reference;
	typedef size_t		size_type;

	// iterator support
	iterator				begin()				{ return elems; }
	iterator				end()				{ return elems + N; }

	// reverse iterator support typedef
	typedef std::reverse_iterator<iterator>		reverse_iterator;

	std::reverse_iterator<iterator>		rbegin()			{ return reverse_iterator(end()); }
	reverse_iterator			rend()				{ return reverse_iterator(begin()); }

	reference				operator[](size_type i)		{ assert(i < N+BEGIN && "out of range"); return elems[i-BEGIN]; }
	// at() with range check reference
	reference				at(size_type i)			{ rangecheck(i); return elems[i+BEGIN]; }
	reference				front()				{ return elems[0]; }
	reference				back()				{ return elems[N-1]; }
	static size_type			size()				{ return N; }
	static bool				empty()				{ return false; }
	static size_type			max_size()			{ return N; }

	enum { static_size = N };

	void					swap(array<T, N> &y)		{ std::swap_ranges(begin(), end(), y.begin()); }
	T *					c_array()			{ return elems; }

	// assignment with type conversion
	template <typename T2>	array <T, N>	&operator=(const array < T2, N > &rhs) { std::copy(rhs.begin(), rhs.end(), begin()); return *this; }
	// assign one value to all elements
	void					assign(const T & value)		{ std::fill_n(begin(), size(), value); }
	// check range (may be private because it is static)
	static void				rangecheck(size_type i)		{ if (i >= size()+BEGIN) { throw std::out_of_range("array<>: index out of range"); } }

};


// comparisons
template<class T, size_t N> bool operator==(const array<T, N> &x, const array<T, N> &y) { return std::equal(x.begin(), x.end(), y.begin()); }
template<class T, size_t N> bool operator< (const array<T, N> &x, const array<T, N> &y) { return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }
template<class T, size_t N> bool operator!=(const array<T, N> &x, const array<T, N> &y) { return !(x == y); }
template<class T, size_t N> bool operator> (const array<T, N> &x, const array<T, N> &y) { return   y < x; }
template<class T, size_t N> bool operator<=(const array<T, N> &x, const array<T, N> &y) { return !(y < x); }
template<class T, size_t N> bool operator>=(const array<T, N> &x, const array<T, N> &y) { return !(x < y); }

// global swap()
template < class T, size_t N > inline void swap(array < T, N > &x, array < T, N > &y) { x.swap(y); }

#endif				// BOOST_ARRAY_HPP ///////////////////////////////////////////////////////////////////////////////////////


#include <iostream>
using namespace std;
#include <lvv.h>

int
main()
{
	array < int, 5 > a;
	array <int, 5, 1> aa;
	ostream_iterator < int >
	os(cout, " ");

	unsigned i;
	for (i = 0; i < a.size(); ++i)		a[i] = i;

	for (i = 1; i < aa.size()+1; ++i)		aa[i] = i;
	for (i = 1; i < aa.size()+1; ++i)		{PR1(aa[i])};

	copy(a.begin(), a.end(), os);  	cout << endl;
	copy(aa.begin(), aa.end(), os);	cout << endl;
}

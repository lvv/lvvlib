#ifndef BOOST_ARRAY_HPP
#define BOOST_ARRAY_HPP

#include <cstddef>
#include <stdexcept>
//#include <boost/assert.hpp>
#include <cassert>

#include <iterator>

#include <boost/throw_exception.hpp>
#include <algorithm>
using std::size_t;

template < class T, size_t N > class array {
      public:
	T elems[N];										   // fixed-size array of elements of type T

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
	const_iterator				begin()			const	{ return elems; }
	iterator				end()				{ return elems + N; }
	const_iterator				end()			const	{ return elems + N; }

	// reverse iterator support typedef
	typedef std::reverse_iterator<iterator>		reverse_iterator;
	typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;

	std::reverse_iterator<iterator>		rbegin()		{ return reverse_iterator(end()); }
	const_reverse_iterator			rbegin()	const	{ return const_reverse_iterator(end()); }
	reverse_iterator			rend()			{ return reverse_iterator(begin()); }
	const_reverse_iterator			rend() const { return const_reverse_iterator(begin()); }

	reference				operator[](size_type i)		{ assert(i < N && "out of range"); return elems[i]; }
	const_reference				operator[](size_type i) const	{ assert(i < N && "out of range"); return elems[i]; }
	// at() with range check reference
	reference				at(size_type i)			{ rangecheck(i); return elems[i]; }
	const_reference				at(size_type i)		const	{ rangecheck(i); return elems[i]; }
	reference				front()				{ return elems[0]; }
	const_reference				front()			const	{ return elems[0]; }
	reference				back()				{ return elems[N - 1]; }
	const_reference				back()			const	{ return elems[N - 1]; }
	static size_type			size()				{ return N; }
	static bool				empty()				{ return false; }
	static size_type			max_size()			{ return N; }

	enum { static_size = N };

	// swap (note: linear complexity)
	void swap(array < T, N > &y) { std::swap_ranges(begin(), end(), y.begin()); }

	// direct access to data (read-only)
	const T *				data()			const	{ return elems; }
	T    *					data()				{ return elems; }

	// use array as C array (direct read/write access to data)
	T      *				c_array()			{ return elems; }

	// assignment with type conversion
	template <typename T2>	array <T, N>	&operator=(const array < T2, N > &rhs) { std::copy(rhs.begin(), rhs.end(), begin()); return *this; }

	// assign one value to all elements
	void					assign(const T & value)		{ std::fill_n(begin(), size(), value); }

	// check range (may be private because it is static)
	static void				rangecheck(size_type i)		{ if (i >= size()) { throw std::out_of_range("array<>: index out of range"); } }

};


// comparisons
template<class T, size_t N> bool operator==(const array<T, N> &x, const array<T, N> &y) { return std::equal(x.begin(), x.end(), y.begin()); }
template<class T, size_t N> bool operator <(const array<T, N> &x, const array<T, N> &y) { return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }
template<class T, size_t N> bool operator!=(const array<T, N> &x, const array<T, N> &y) { return !(x == y); }
template<class T, size_t N> bool operator> (const array<T, N> &x, const array<T, N> &y) { return y < x; }
template<class T, size_t N> bool operator<=(const array<T, N> &x, const array<T, N> &y) { return !(y < x); }
template<class T, size_t N> bool operator>=(const array<T, N> &x, const array<T, N> &y) { return !(x < y); }

// global swap()
template < class T, size_t N > inline void swap(array < T, N > &x, array < T, N > &y) { x.swap(y); }

#endif				// BOOST_ARRAY_HPP ///////////////////////////////////////////////////////////////////////////////////////


	#include <iostream>
using namespace
    std;

int
main()
{
	array < int,
	    5 >
	    a;
	ostream_iterator < int >
	os(cout, " ");

	for (unsigned i = 0; i < a.size(); ++i)
		a[i] = i;
	copy(a.begin(), a.end(), os);
}

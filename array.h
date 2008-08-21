
#ifndef LVV_ARRAY
#define LVV_ARRAY

#include <cassert>
#include <iterator>
#include <algorithm>
using std::size_t;

namespace lvv {

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

	reference				operator[](size_type i)		{ assert(i<N+BEGIN && i>=BEGIN && "out of range"); return elems[i-BEGIN]; }
	reference				at(size_type i)			{ assert(i<N+BEGIN && i>=BEGIN && "out of range"); return elems[i+BEGIN]; }
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

};


// comparisons  (TODO, add BEGIN)
template<class T, size_t N> bool operator==(const array<T, N> &x, const array<T, N> &y) { return std::equal(x.begin(), x.end(), y.begin()); }
template<class T, size_t N> bool operator< (const array<T, N> &x, const array<T, N> &y) { return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }
template<class T, size_t N> bool operator!=(const array<T, N> &x, const array<T, N> &y) { return !(x == y); }
template<class T, size_t N> bool operator> (const array<T, N> &x, const array<T, N> &y) { return   y < x; }
template<class T, size_t N> bool operator<=(const array<T, N> &x, const array<T, N> &y) { return !(y < x); }
template<class T, size_t N> bool operator>=(const array<T, N> &x, const array<T, N> &y) { return !(x < y); }

// global swap()
template < class T, size_t N > inline void swap(array < T, N > &x, array < T, N > &y) { x.swap(y); }


};	// namespace lvv
#endif	// LVV_ARRAY

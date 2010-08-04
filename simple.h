#ifndef  LVV_SIMPLE_H
#define  LVV_SIMPLE_H

// C
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>

// C++
#include <algorithm>
#include <deque>
#include <iomanip>
#include <iomanip>
#include <iostream>
#include <iostream> 
#include <iterator>
#include <list>
#include <map>
#include <set>
#include <sstream> 
#include <string>
#include <tuple>
#include <utility>
#include <vector>

// local
#include <lvv/lvv.h>
#include <lvv/meta.h>
#include <lvv/array.h>
	using lvv::array;
//	using std::to_binary;

using namespace std;

// FOREACH
//#include <boost/foreach.hpp>
//#define         foreach         BOOST_FOREACH  
//#define reverse_foreach		BOOST_REVERSE_FOREACH



	//////// LINE INPUT
	static std::istringstream		lin_sstream;
	static char __attribute__((unused))	lin_line[1000];	

	
	#define		nlin   		( \
						cin.getline(lin_line,sizeof(lin_line)-1),  \
						lin_sstream.clear(),  \
						lin_sstream.str(lin_line),  \
						lin_sstream \
	)

	#define		lin  lin_sstream

	#define		NL      		cin.ignore(1000,'\n');
	#define		nl      		cin.ignore(1000,'\n');


	#define		IS_SPACE                (cin.peek()==' '  || cin.peek()=='\t')
	#define		IS_EOL                  (cin.peek()=='\n' || cin.peek()=='\r')
	#define		IS_COMMA                (cin.peek()==',')
	#define		SKIP_SPACE              while ( IS_SPACE             )    cin.ignore(1);
	#define		SKIP_SPACE_N_COMMA      while ( IS_SPACE || IS_COMMA )    cin.ignore(1);

	//////// integral to binary string 

			template<typename T> inline
	const string binstr (T v) {
		string binstr(sizeof(T)*8,'#') ;
		for (int i=0; i<sizeof(T)*8; i++) {
			binstr[sizeof(T)*8-1-i] = (v>>i) & 1 ? '1' : '0' ;
			//v = v / 2 ;
		}
		//return std::move(binstr) ;
		return binstr ;
	}

	template<typename T> struct list_t;
	

// print any std::sequance-containter<printable>
template<typename E, template<typename E, typename L> class L > inline std::ostream&                                              
operator<<      (ostream& os, const L<E, std::allocator<E> >& LL) {              

        if (LL.empty()) return os;

        //for (size_t i=0; i<LL.size()-1; i++)
        //        os<<LL[i]<<", ";
	auto it=LL.begin();
	os  <<  *it++;
        for (; it !=LL.end();   it++)
                os <<  ", " << *it;
        os << "   size:" << LL.size() <<"  ";
        return os;
};

// SET -- print any std::set<printable>  with std comparator and allocator
template<typename K> inline std::ostream&                                              
operator<<      (ostream& os, const set<K, std::less<K>, std::allocator<K> >& C) {              

        if (C.empty()) return os;

	auto it=C.begin();
	os  <<  *it++;
        for (; it !=C.end();   it++)
                os <<  ", " << *it;
        os << "   size:" << C.size() << "  ";
        return os;
};


// PAIR -- print any std::pair<printable1, printable2>
template<typename T, typename U> inline std::ostream&  
operator<<      (ostream& os, const typename std::pair<T,U>& p) {               
	os << "<" << p.first << "," << p.second <<">";
	return os;
};



// MAP -- print any std::map<printable, printable>  with std comparator and allocator
template<typename K, typename V> inline std::ostream&                                              
operator<<      (ostream& os, const map<K, V, std::less<K>, std::allocator<std::pair<const K,V> > > & C) {              

        if (C.empty()) return os;

	auto it = C.begin();
	os  <<  *it++;
        for (; it !=C.end();   it++)
                os <<  ", " << *it;

        os << "   size:" << C.size() <<"  ";
        return os;
};
	

// OSI -- used as:    copy(V.begin(), V.end(), osi<int>());
template<typename T=int>
struct	osi : ostream_iterator<T> {
	osi(): ostream_iterator<T>(cout, " ") { self_addr = (void*) this; }; 
	void* self_addr;	// to check if we are iriginal instance of osi
	~osi() { if (self_addr == (void*) this)   cout << endl; };	
};


/*
// TUPLE -- print any std::tuple<printable ...>
template<typename T0, typename... REST> inline std::ostream&  
operator<<      (ostream& os, const std::tuple<T0, REST...>& tup) {               
	os <<  get<0>(tup) << " ";
	tuple<REST...> sub_tup;
	tie(ignore, sub_tup) = tup;
	os << sub_tup; 
	return os;
};*/


#endif

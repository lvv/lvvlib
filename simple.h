#ifndef  LVV_SIMPLE_H
#define  LVV_SIMPLE_H

#include <lvv/lvv.h>

#include <sstream> 
#include <iostream> 
#include <iomanip>
	using std::flush;
	using std::string;
	using std::cout;
	using std::cerr;
	using std::endl;
	using std::setw;
	using std::ostream;
	using std::setprecision;

#include <iterator>
#include <algorithm>
	using std::find;
	using std::swap;
	using std::max;
	using std::min;

#include <cctype>
	using std::islower;

#include <cstring>
	using std::strchr;
	using std::strcspn;
	using std::memset;
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <tr1/tuple>
	using std::tr1::tuple;
	using std::tr1::make_tuple;

#include <vector>
	using std::vector;
#include <deque>
	using std::deque;
#include <set>
	using std::deque;

	using namespace std;

	//////// LINE INPUT
	static std::istringstream	lin_sstream;
	static char			lin_line[1000];	

	
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



#endif

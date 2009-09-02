	//#include <lvv/lvv.h>

	#include "s_pool.h"

	#include <fstream>
	#include <iostream>
	#include <deque>

	using namespace std;

int main() {

			typedef 	lvv::spool_t <20,50>	SPOOL_t;
			typedef 	SPOOL_t::ref_t		REF_t;
		SPOOL_t		spool;
		deque<REF_t>	s_list;
		REF_t		ref;

	while (cin.getline (spool.get_new(ref), 1000))  {
		cout << "in: " << spool.get(ref) << "   \t ref: " << int(ref.buf) << " / " << ref.offset << endl;	
		s_list.push_back(ref);
	}

	for (auto it = s_list.rbegin();   it != s_list.rend();  it++) 
		cout << "out:  " << spool.get(*it) << endl;
	exit(0);
}

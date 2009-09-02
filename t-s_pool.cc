	//#include <lvv/lvv.h>

	#include "s_pool.h"

	#include <fstream>
	#include <iostream>
	#include <deque>


	using namespace std;


int main() {

	/////////////////////////////////////////////////

	spool_t<20,50>		spool;
	deque<spool_ref_t>	s_list;
	spool_ref_t		ref;

	while (cin.getline (spool.get_new(ref), 1000))  {
		cout << "in: " << spool.get(ref) << "   \t ref: " << int(ref.buf) << " / " << ref.offset << endl;	
		s_list.push_back(ref);
	}

	for (auto it = s_list.rbegin();   it != s_list.rend();  it++) 
		cout << "out:  " << spool.get(*it) << endl;
	exit(0);
}

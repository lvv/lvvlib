
#include "memoize.h"

#include <iostream>
using namespace std;

int f  (int i) 		{ cout << "f(" << i << ")\n";  return i+1; };
int ff (int i, int j)	{ cout << "f(" << i << ", " << j << ")\n";  return i+j; };


int main()  {
	auto  f_cached  =  lvv::memoize ( std::function <int(int)> (f) );
	f_cached(1);
	f_cached(2);
	f_cached(1);
	f_cached(2);
	f_cached(3);

	// output:
	//   	f(1)
	// 	f(2)
	// 	f(3)
	

	auto ff_cached  =  lvv::memoize ( std::function <int(int, int)> (ff) );
	ff_cached(1,1);
	ff_cached(2,2);
	ff_cached(1,1);
	ff_cached(0,0);
	ff_cached(1,1);

	// output
	// f(1, 1)
	// f(2, 2)
	// f(0, 0)
}

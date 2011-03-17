
#include "memoize.h"

#include <iostream>
using namespace std;

int f(int i) { cout << "f(" << i << ")\n";  return i+1; };


int main()  {
	auto fo  =  lvv::memoize ( std::function <int(int)> (f) );
	fo(1);
	fo(2);
	fo(1);

	// output:
	//   	f(1)
	// 	f(2)
}

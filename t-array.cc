

#include <iostream>
using namespace std;
#include <lvv/lvv.h>
#include <lvv/array.h>
using lvv::array;
#include <boost/foreach.hpp>

typedef array<int,5> a5_t;


int main() {

	array <int, 5   > a0 = {{0,1,2,3,4}}; 				// index starts from 0 
	array <int, 5, 1> a1 = {{1,2,3,4,5}}; 				// index starts from 1
	array <int, 5, -2> an = *new array <int, 5, -2>;		// test new


	for (int i = 1; i < int(a1.size())+1; ++i)		{          PR2(i,   a1 [i])};
	for (int i = -2; i < int(an.size())-2; ++i)		{an[i]=i;  PR2(i, an[i])};

	cout << "a0: "       << a0;
	BOOST_FOREACH(int &elem, a0)  { elem+=10; };
	cout << "a0 += 10: " << a0;

	cout << "a1: " << a1;
	cout << "an: " << an;
}



#include <iostream>
using namespace std;
#include <lvv.h>
#include <array.h>
using lvv::array;

int main() {
	array <int, 5   > a0 = {{0,1,2,3,4}}; // index starts from 0 
	array <int, 5, 1> a1 = {{1,2,3,4,5}}; // index starts from 1

	for (unsigned i = 1; i < a1.size()+1; ++i)		{PR1(a1[i])};

	ostream_iterator<int>	os(cout, " ");
	copy(a0.begin(), a0.end(), os);  	cout << endl;
	copy(a1.begin(), a1.end(), os);		cout << endl;
}


#include <iostream>
using namespace std;

#include <boost/foreach.hpp>

#include <lvv/array.h>
#include <lvv/lvv.h>
using lvv::array;


int main() { 

	typedef array<int,5> a5_t;

	array <int, 5   >        a0 = {{0,1,2,3,4}}; 			// index starts from 0 
	array <int, 5, 1> const  a1 = {{1,2,3,4,5}}; 			// index starts from 1
	array <int, 5, -2>       an = *new array <int, 5, -2>;		// test new

	for (int i = a1.ibegin(); i < a1.iend(); ++i)	{           cout << format("i=%d   a1[i]=%d") %i  % (a1[i]) << endl; };
	for (int i = an.ibegin(); i < an.iend(); ++i)	{ an[i]=i;  cout << format("i=%d   an[i]=%d") %i  % (an[i]) << endl; };

	cout << "a0: "       << a0;
	BOOST_FOREACH(int &elem, a0)  { elem+=10; };
	cout << "a0 += 10: " << a0;

	cout << "a1: " << a1;
	cout << "an: " << an;

	cout << "an+10  " << (an += 10);
	cout << "an-1   " << (an -= 1);
	cout << "an*2   " << (an *= 2);
	cout << "an/4   " << (an /= 4.0);

	
	cout << "FOR_ARRAY "; 
	//FOR_ARRAY(a,an) cout << *a ;
	typedef typeof(an) T;
	for(
		//array<int,5,-2>::iterator a=an.begin();
		T::iterator a=an.begin();
		a != an.end(); 
		a++
	)
		cout << *a << " ";



	cout << endl;
}

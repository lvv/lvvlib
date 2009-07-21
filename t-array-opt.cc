
#include <iostream>
	using namespace std;

#include <lvv/array.h>
#include <lvv/lvv.h>
	using lvv::array;


int main() { 

	typedef array<int,5> a5_t;

	array <int, 5   >       a0 = {{0,1,2,3,4}}; 			// index starts from 0 
	array <int, 5, 1>	a1 = {{1,2,3,4,5}}; 			// index starts from 1
	array <int, 5, 1> const b1 = {{10,20,30,40,50}}; 			// index starts from 1
	array <int, 5, -2>      an = *new array <int, 5, -2>;		// test new

	for (int i = a1.ibegin(); i < a1.iend(); ++i)	{           cout << format("i=%d   a1[i]=%d") %i  % (a1[i]) << endl; };


	cout << "\n array op= array \n";
	cout << "a1+=b1  " << (a1 += b1)<< endl;

	cout << "-a1  " << -a1 << endl;
	

	// vector ops
	array<float,2> c1={{1,2}};
	array<float,2> c2={{2,2}};
	cout << "dot prod:  {1,2} x {2,2} = " << dot_prod(c1,c2) << endl;
	cout << "norm2: : |{2,2}| = " << norm2(c2) << endl;
	cout << "distance_norm2: : |{1,2}-{2,2}| = " << distance_norm2(c1,c2) << endl;

	cout << endl;
}

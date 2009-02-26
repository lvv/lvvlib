
#include <iostream>
	using namespace std;

//#include <boost/foreach.hpp>

#include <boost/format.hpp>
	using boost::format;

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
	for (int i = an.ibegin(); i < an.iend(); ++i)	{ an[i]=i;  cout << format("i=%d   an[i]=%d") %i  % (an[i]) << endl; };

	cout << "a0: "       << a0 << endl;
	cout << "a0 += 10: " << a0 << endl;

	cout << "a1: " << a1 << endl;
	cout << "an: " << an << endl;

	
	cout << "\n array op= scalar : an+10  " << (an += 10) << endl;

	cout << "\n array op= array \n";
	cout << "a1+=b1  " << (a1 += b1)<< endl;

	cout << "-a1  " << -a1 << endl;
	

	// vector ops
	array<float,2> c1={{1,2}};
	array<float,2> c2={{2,2}};
	cout << "dot prod:  {1,2} x {2,2} = " << dot_prod(c1,c2) << endl;
	cout << "norm2: : |{2,2}| = " << norm2(c2) << endl;
	cout << "distance_norm2: : |{1,2}-{2,2}| = " << distance_norm2(c1,c2) << endl;


	//#define FOR_EACH(x,A)  for(A::value_type& it=*A.begin();  ....
	//FOR_EACH(a,A) cout << a << endl;



	/*
	cout << "FOR_ARRAY "; 
	typedef typeof(an) T;
	for(
		//array<int,5,-2>::iterator a=an.begin();
		T::iterator a=an.begin();
		a != an.end(); 
		a++
	)
		cout << *a << " ";

	cout << endl;
	*/

	{
		cout << "\narray input test, type three whole number\n";
		array<int, 3> A;
		cin >> A;
		cout << "got from  input: " << A << endl;
	}
}

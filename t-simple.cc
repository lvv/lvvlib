
	#include "simple.h"
	//#include <boost/type_traits.hpp>
	//	using boost::is_base_of;

int main() {
	pair<int,double> p = make_pair(1,2.0);
	cout << p << endl;

	vector<int> v(2,0); 
	cout << v << endl;

	vector<pair<int,double> > vv(2,p); 
	cout << vv << endl;


	deque<pair<int,string> > vps = {{1, "aaa"}, {2,"bbb"}};
	cout << vps << endl;


	array<int,5> A = {1, 2, 3, 4, 5};
	cout << A << endl;
}

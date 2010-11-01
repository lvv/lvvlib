
	#include "simple.h"
	#include <boost/type_traits.hpp>
		using boost::is_base_of;

int main() {
	pair<int,double> p = make_pair(1,2.0);
	cout << p << endl;

	vector<int> v(2,0); 
	cout << v << endl;

	vector<pair<int,double> > vv(2,p); 
	cout << vv << endl;


	const pair<int,string> ps = make_pair(1,string("aaa"));
	deque<pair<int,string> > vps;
	vps.push_back(ps);
	PR1(vps)


	// cout << p == p;

	//cout << sv << endl;
}

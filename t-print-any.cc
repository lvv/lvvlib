#include<lvv/simple.h>

using namespace std;

int main()  {

	//  VECTOR
	vector<int>	V = {0, 1, 2, 3, 4, 5, 6};
	cout << "vector: \t" << V << endl;

	// TUPLE  (0x built-in, not yet implemented)
	//cout << "tuple-2: \t" << make_tuple(1,2) << endl; 

	//  LIST
	list<int>	L = {0, 1, 2, 3, 4, 5, 6};
	cout << "list: \t" << L << endl;

	//  SET
	set<int>	S = {6,3,4,1,2,0,5};
	cout << "set: \t" << S << endl;

	//  MAP
	map<string,int>	M = { {"A",1}, {"B",2}, {"C",3} };
	M.erase("B");
	//for_each (M.begin(), M.end(), [](const pair<string,int>& m){ cout << m.first << "\t"  << m.second << endl; } );	cout << endl;
	cout << "map: \t" << M;
	

	return 0;
}

#include<lvv/simple.h>

int main()  {

	vector<int>	V = {0, 1, 2, 3, 4, 5, 6};
	cout << V << endl;

	list<int>	L = {0, 1, 2, 3, 4, 5, 6};
	cout << L << endl;

	set<int>	S = {6,3,4,1,2,0,5};
	cout << S << endl;

	map<string,int>	M = { {"A",1}, {"B",2}, {"C",3} };
	cout <<  M << endl;
}

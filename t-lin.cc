#include <simple.h>
#include <lvv/lvv.h>
#include <lvv/array.h>
	using lvv::array;


int main() {
	int i,j,k;
	int n=0;
	char s[1000];
	char c;
	cerr << "enter lines: " << endl;
	//nlin >> s; 		PR1(s);
	cin >> c; 		PR1(c);  PR1(cin.rdbuf()->tellg())
	                    	PR1(cin.tellg())
	cin >> c; 		PR1(c);  PR1(cin.rdbuf()->in_avail());
	cin >> c; 		PR1(c);  PR1(cin.rdbuf()->in_avail());
	nl;				 PR1(cin.rdbuf()->in_avail());

	nlin >> i;     		PR1(i);
	lin  >> j;  		PR1(j);
	
	nlin  >> s; 		PR1(s);
		while  ( lin >> s ) cerr << "("<<n++<<")\t" << s << endl;
	
	//cin >> i;  cin.ignore(1000, '\n');
	////cin >> j;  NL
					PR3(i,j,k);
	return 0;
}

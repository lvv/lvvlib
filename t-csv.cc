#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <lvv/csv.h>
using namespace lvv;
using namespace std;


int main() {

	string csv =
	    "a\"\"b\"\"c\n"
	    "a\"\"\"b\"\"\"c\n"
	    "\"a\"\"b\"\"c\"\n"
	    ",\n"
	    "a\n"
	    ",a\n"
	    "a,\n"
	    "a,\" a\"a,b\"b \"\n"
	    "aa,b\"b,c\"c,   d   ,,ee,ff,  g\"g,h\"h  \n" "aa,  bb,cc  ,\"  dd\",\"ee  \",\"f,  g\n" ",  h\",\"i,\"\"j,k\"\",l\"\n";

	istringstream is(csv);

	while (true) {
		typedef vector <string> rec_t;

		rec_t rec = csv_get_line(is);

		if (rec.size() == 0)    break;

		for (rec_t::iterator x = rec.begin(); x != rec.end(); ++x) {
			cout << '>' << *x << "<\n";
		}

		cout << string(20, '*') << '\n';
	}
}

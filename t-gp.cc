
#include <iostream>
using namespace std;

#include <boost/foreach.hpp>

#include <lvv/lvv.h>
#include <lvv/math.h>

namespace gp {

   
	format          table(" % 9g    %20t % 9g   %40t % 9g   %60t % 9g %80t % 9g\n");
	string          _("\" \"");
	#define GNUPLOT_CONFIG_STRING   "set key bottom; set ytics 0,0.5;  set ytics 0,0.5; set yrange [-0.1:1.1]; set xrange [-1:7]; set grid; set pointsize 1.5;" \
	                                "plot " \
	                                        " \"pipe\" using 1:3 title \"model\"            with lines   5,"\
	                                        " \"pipe\" using 4:2 title \"inv x(y)\"         with point   4,"\
	                                        " \"pipe\" using 1:2 title \"cdf\"              with points 11,"\
	                                        " \"pipe\" using 1:5 title \"PDF[=bin/n]\"      with points  7 "\
	                                ";"

int main() { 

	
			typename<int N_col>
	class multiplot { public:


			array<string,N_col>	legend;
			deque<array<float,N_col>, 20>	T;
			string title;
			string	plot;

			multiplot(string title) : this->title(title),  {}
	void 		newline() { T.pushback();}
	void 		addplot(int xi, int yi, string legend, string config)   {
		this->legend[...] = legend;
		......
	}






	void 				plot(string x_name, string y_name) : this->x_name(xname),  this->y_name(y_name) {}
		add(double x,  double y)
		deque <float, 20>		xT;
		deque <float, 20>		yT;

		string x_name; 
		string y_name; 
	}
}

} // gp 

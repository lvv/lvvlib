
#include <iostream>
using namespace std;

#include <boost/foreach.hpp>

#include <lvv/lvv.h>
#include <lvv/math.h>
using lvv::group_mean;


int main() { 

	double sample_value = 1.;
	double samples= 20 ;
	double global_value = 10.;
	double K = 5.;

for (int i=1; i < 20; i++)
	FMT("sv=%f	sN=%f		gv=%f	K=%f	===  GM=%f\n") %sample_value %i  %global_value %K %group_mean(sample_value, i, global_value, K);
}

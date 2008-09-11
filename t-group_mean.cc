
#include <iostream>
using namespace std;

#include <boost/foreach.hpp>

#include <lvv/lvv.h>
#include <lvv/math.h>
using lvv::group_mean;


int main() { 

	double sample_value = 1.;
	double samples;
	double global_value = 10.;
	double K = 5.;

FMT("sv=%f	sN=%f		gv=%f	K=%f	===  GM=%f\n") %sample_value %samples  %global_value %1%group_mean(sample_value, 1, global_value, K);
FMT("sv=%f	sN=%f		gv=%f	K=%f	===  GM=%f\n") %sample_value %samples  %global_value %2%group_mean(sample_value, 2, global_value, K);
FMT("sv=%f	sN=%f		gv=%f	K=%f	===  GM=%f\n") %sample_value %samples  %global_value %4%group_mean(sample_value, 4, global_value, K);
FMT("sv=%f	sN=%f		gv=%f	K=%f	===  GM=%f\n") %sample_value %samples  %global_value %6%group_mean(sample_value, 6, global_value, K);
FMT("sv=%f	sN=%f		gv=%f	K=%f	===  GM=%f\n") %sample_value %samples  %global_value %8%group_mean(sample_value, 8, global_value, K);
FMT("sv=%f	sN=%f		gv=%f	K=%f	===  GM=%f\n") %sample_value %samples  %global_value %10%group_mean(sample_value, 10, global_value, K);
FMT("sv=%f	sN=%f		gv=%f	K=%f	===  GM=%f\n") %sample_value %samples  %global_value %12%group_mean(sample_value, 12, global_value, K);
FMT("sv=%f	sN=%f		gv=%f	K=%f	===  GM=%f\n") %sample_value %samples  %global_value %15%group_mean(sample_value, 15, global_value, K);
FMT("sv=%f	sN=%f		gv=%f	K=%f	===  GM=%f\n") %sample_value %samples  %global_value %20%group_mean(sample_value, 20, global_value, K);
FMT("sv=%f	sN=%f		gv=%f	K=%f	===  GM=%f\n") %sample_value %samples  %global_value %30%group_mean(sample_value, 30, global_value, K);
FMT("sv=%f	sN=%f		gv=%f	K=%f	===  GM=%f\n") %sample_value %samples  %global_value %40%group_mean(sample_value, 40, global_value, K);
FMT("sv=%f	sN=%f		gv=%f	K=%f	===  GM=%f\n") %sample_value %samples  %global_value %50%group_mean(sample_value, 50, global_value, K);
FMT("sv=%f	sN=%f		gv=%f	K=%f	===  GM=%f\n") %sample_value %samples  %global_value %80%group_mean(sample_value, 80, global_value, K);
}

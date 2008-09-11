
#include <stats/stats.h>
#include <lvv/lvv.h>
using namespace std;
using namespace lvv;

#include <boost/math/distributions/beta.hpp>
using boost::math::beta_distribution;
using boost::math::quantile;


int main() { 

	beta_distribution<> bt(7,14);

	MSG("%f  %.40g\n") %0.01  %(cdf(bt, 0.1));
	MSG("%f  %.40g\n") %0.1  %(cdf(bt, 0.1));
	MSG("%f  %.40g\n") %0.2  %(cdf(bt, 0.2));
	MSG("%f  %.40g\n") %0.3  %(cdf(bt, 0.3));
	MSG("%f  %.40g\n") %0.4  %(cdf(bt, 0.4));
	MSG("%f  %.40g\n") %0.5  %(cdf(bt, 0.5));
	MSG("%f  %.40g\n") %0.7  %(cdf(bt, 0.7));
	MSG("%f  %.40g\n") %0.8  %(cdf(bt, 0.8));
	MSG("%f  %.40g\n") %0.9  %(cdf(bt, 0.9));
	MSG("%f  %.40g\n") %0.99  %(cdf(bt, 0.9));

	exit(0);
}

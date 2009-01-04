

#include <lvv/check.h>
#include <lvv/meta.h>
	using namespace std;
	using namespace lvv;
                int
main() {
	CHECKeq(fp_metrics<float>::mantissa_size,23);
	CHECKeq(fp_metrics<float>::exponent_size,8);
	CHECK_EXIT;
}

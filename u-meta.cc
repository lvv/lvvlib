
#include <lvv/check.h>
#include <lvv/meta.h>
#include <lvv/float.h>

	using namespace std;
	using namespace lvv;

                int
main() {

	cout << "*********  INT_<>  **********\n";
	CHECK_ARE_EQUAL		((int_<3>::value), 			3);
	CHECK_ARE_EQUAL		((int_<-3>::value), 			-3);

	cout << "*********  IPOW<>  **********\n";
	CHECK_ARE_EQUAL		((ipow<3,2>::value), 			9);
	CHECK_ARE_EQUAL		((ipow<10,3>::value),			1000);
	CHECK_ARE_EQUAL		((ipow<10,0>::value), 			1);

	cout << "*********  FP<>  **********\n";
	CHECK_ARE_EQUAL		((fp<float,2,-1>::value),		float(0.2));
	CHECK_ARE_EQUAL		((fp<float,2,0>::value),		2);
	CHECK_ARE_EQUAL		((fp<float,2,1>::value),		20);

	cout << "*********  RATIO<>  **********\n";
	CHECK_ARE_EQUAL		((ratio<2>::denominator),		1);
	CHECK_ARE_EQUAL		((ratio<2,3>::denominator),		3);
	CHECK_ARE_EQUAL		((ratio<2,3>::numerator),		2);
	CHECK_ARE_FP_EQUAL	((ratio<2,3,float>::value),		float(2./3.));
	CHECK_ARE_FP_EQUAL	((ratio<1,2>::value),			1./2.);
	CHECK_ARE_FP_EQUAL	((ratio<0,3,float>::value),		float(0.));
	CHECK_ARE_FP_EQUAL	((ratio<-2,3,float>::value),		float(2./-3.));
	CHECK_ARE_FP_EQUAL	((ratio<1,1000,float>::value),		float(0.001));

	CHECK_EXIT;

}

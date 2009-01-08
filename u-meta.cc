
#include <lvv/check.h>
//#include <lvv/meta.h>
#include <lvv/float.h>
#include <lvv/lvv.h>
#include <typeinfo>
	// for typeid

	using namespace std;
	using namespace lvv;

                int
main() {

	cout << "*********  PROMOTE<>  **********\n";

	PR1((type_descriptor<LVV_PROMOTE1(int                   ) >() ) ) ;
	PR1((type_descriptor<LVV_PROMOTE1(float                 ) >() ) ) ;

	PR1	((type_descriptor<LVV_PROMOTE2(float       , double  ) >() ) ) ;
	PR1	((type_descriptor<LVV_PROMOTE2(int         , int     ) >() ) ) ;
	PR1	((type_descriptor<LVV_PROMOTE2(int         , float   ) >() ) ) ;
	PR1	((type_descriptor<LVV_PROMOTE2(int         , float   ) >() ) ) ;
	PR1	((type_descriptor<LVV_PROMOTE2(float       , float   ) >() ) ) ;
	PR1	((type_descriptor<LVV_PROMOTE2(int         , int     ) >() ) ) ;
	PR1	((type_descriptor<LVV_PROMOTE2(char        , unsigned) >() ) ) ;
	PR1	((type_descriptor<LVV_PROMOTE2(long double , char    ) >() ) ) ;

	{ cout << "\n\n *** Test is_integral ***\n";
	PR1	(LVV_IS_INTEGRAL(int));
	PR1	(LVV_IS_INTEGRAL(float));
	PR1	(LVV_IS_INTEGRAL(double));
	}

	cout << "*********  RATIO<>  **********\n";
	CHECK_ARE_EQUAL		((ratio_<2>::denominator),		1);
	CHECK_ARE_EQUAL		((ratio_<2,3>::denominator),		3);
	CHECK_ARE_EQUAL		((ratio_<2,3>::numerator),		2);
	CHECK_ARE_FP_EQUAL	((ratio_<2,3>::convert<float>()),	float(2./3.));
	CHECK_ARE_FP_EQUAL	((ratio_<2,3>::convert<int>()),		0);
	CHECK_ARE_FP_EQUAL	((ratio_<1,2>::convert<float>()),	1./2.);
	CHECK_ARE_FP_EQUAL	((ratio_<0,3>::convert<float>()),	float(0.));
	CHECK_ARE_FP_EQUAL	((ratio_<-2,3>::convert<float>()),float(2./-3.));
	CHECK_ARE_FP_EQUAL	((ratio_<1,1000>::convert<float>()),	float(0.001));

	cout << "*********  FP<>  **********\n";
	CHECK_ARE_EQUAL		((fp<float,2,-1>::value),		float(0.2));
	CHECK_ARE_EQUAL		((fp<float,2,0>::value),		2);
	CHECK_ARE_EQUAL		((fp<float,2,1>::value),		20);


	cout << "*********  INT_<>  **********\n";
	CHECK_ARE_EQUAL		((int_<3>::value), 			3);
	CHECK_ARE_EQUAL		((int_<-3>::value), 			-3);

	cout << " ***** IPOW  *******\n"; ///////////////////////////////////////////////
	CHECKeq((lvv::ipow<3,0>::value), 1);
	CHECKeq((lvv::ipow<3,1>::value), 3);
	CHECKeq((lvv::ipow<3,2>::value), 9);

	cout << " ***** ILOG2  *******\n"; ///////////////////////////////////////////////
	CHECKeq((lvv::ilog2<1>::value), 0);
	CHECKeq((lvv::ilog2<2>::value), 1);
	CHECKeq((lvv::ilog2<4>::value), 2);
	CHECKeq((lvv::ilog2<256>::value), 8);

	CHECK_EXIT;
	#ifndef ONE
	#endif // ONE

}

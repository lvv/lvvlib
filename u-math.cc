

#include <lvv/check.h>
#include <lvv/math.h>
	//using namespace std;
	using namespace lvv;
                int
main() {

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
}

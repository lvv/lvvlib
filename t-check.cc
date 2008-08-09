
#include "../lvv/lvv.h"
#include "../lvv/lvvcheck.h"
#include <limits>
using namespace std;
using namespace lvv;


template <typename T>   bool equal      (T   arg1, T   arg2)    { /*PR(arg1); PR(arg2);*/ return arg1 == arg2; };
template <>             bool equal<int> (int arg1, int arg2)    { /*PR(arg1); PR(arg2);*/ return arg1 == arg2; };

                int
main() {

    int i0=0;
    int i1=1;
    int i2=2;

    float f0=0.0;
    float f1=1.0;
    float f2=2.0;

    cout << std::boolalpha;

    CHECK(!equal(f1,f2));
    CHECK( equal(f1,f1));
    CHECK(!equal(f0,f1));
    CHECK(!equal(f1,f0));
    CHECK( equal(f0,f0));

    CHECK(!equal(i1,i2));
    CHECK( equal(i1,i1));
    CHECK(!equal(i0,i1));
    CHECK(!equal(i1,i0));
    CHECK( equal(i0,i0));

    CHECK(false);
    CHECK_ARE_EQUAL(1,2);
    CHECK_NOT_EQUAL(1,2);
    CHECK_ARE_EQUAL(1,1);

    CHECK_NOT_EQUAL(f1,f2);
    CHECK_ARE_EQUAL(f1,f1);
    CHECK_NOT_EQUAL(f0,f1);
    CHECK_NOT_EQUAL(f1,f0);
    CHECK_ARE_EQUAL(f0,f0);

    CHECK_NOT_EQUAL(i1,i2);
    CHECK_ARE_EQUAL(i1,i1);
    CHECK_NOT_EQUAL(i0,i1);
    CHECK_NOT_EQUAL(i1,i0);
    CHECK_ARE_EQUAL(i0,i0);

    cout << (all_pass ? "\n------------ all pass ------------\n" : "\n!!!!!!!!!  SOME FAILED  !!!!!!!!\n");
    exit(all_pass ? 0 : 1);
}

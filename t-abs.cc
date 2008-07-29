
#include <limits>
#include "../lvvlib/lvvlib.h"
#include "../lvvlib/lvvmath.h"
using namespace std;
using namespace lvv;
///////////////////////////////////////////////////////////////////
                int
main() {
    setup_fpe();
    cerr << setprecision(numeric_limits<double>::digits10+4) << boolalpha;
    cout << setprecision(numeric_limits<double>::digits10+4) << boolalpha;

#include "../lvvlib/lvvcheck.h"

    cout << "\n\n *** Test equal<integral>() ***\n";
    cout << std::boolalpha;
    CHECK(abs(1)==1);
    CHECK(abs(1u)==1);
    CHECK(abs((char)-1)==1);
    CHECK(abs(1UL)==1);
    CHECK(abs((long)-1)==1);
    CHECK(abs(9999)==9999);
    CHECK(abs(-31)==31);
    CHECK(abs(0)==0);
   
    CHECK(abs(1.0f)==1.f);
    CHECK(abs(-1.f)==1.f);
    CHECK(abs(-1.0)==1.);
    CHECK(abs(-1E10l)==1E10);
    CHECK(abs(9999)==9999);
    CHECK(abs(-31.f)==31.f);
    CHECK(abs(0.0f)==0.0);
   

    cout << (all_pass ? "\n------------ all pass ------------\n" : "\n!!!!!!!!!  SOME FAILED  !!!!!!!!\n");
    exit(all_pass ? 0 : 1);
}



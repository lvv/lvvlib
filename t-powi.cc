
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

    cout << "\n\n *** Test POWI() ***\n";
    cout << std::boolalpha;

    CHECK(eq(powi(3.33, 0), 1.          ));
    CHECK(eq(powi(3.33, 1), 3.33        ));
    CHECK(eq(powi(3.33, 2), 11.0889     ));
    CHECK(eq(powi(3.33, 3), 36.926037   ));
    CHECK(eq(powi(3.33, 4), 122.96370321));
    CHECK(eq(powi(0.  , 4), 0.          ));
   

    cout << (all_pass ? "\n------------ all pass ------------\n" : "\n!!!!!!!!!  SOME FAILED  !!!!!!!!\n");
    exit(all_pass ? 0 : 1);
}



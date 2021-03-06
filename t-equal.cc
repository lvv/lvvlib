
#include <limits>
#include <lvv/lvv.h>
#include <lvv/check.h>

#include <lvv/math.h>
using namespace std;
using namespace lvv;

///////////////////////////////////////////////////////////////////
                int
main() {
    lvv::setup_fpe();

    int		const i0   = 0;
    int		const i1   = 1;
    int		const i2   = 2;

    float	const f0 = 0.0;
    float	const f1 = 1.0;
    float	const f2 = 2.0;
    float	const f3 = 3.0;
    double	const d2= 2.0;
    float	const	f1_ulp = std::numeric_limits<float>::epsilon();
    float	const	d1_ulp = std::numeric_limits<double>::epsilon();

    cerr << setprecision(numeric_limits<double>::digits10+4) << boolalpha;
    cout << setprecision(numeric_limits<double>::digits10+4) << boolalpha;

    cout << "\n\n *** Test promote trait ***\n";
    PR1(eq(i0,i1))
    PR1(eq(i0,i0))
    PR1(eq(i0,f0))
    PR1(eq(f0,f0))


    cout << "\n\n *** Test eq<integral>() ***\n";
    cout << std::boolalpha;
    CHECK(!eq(1,2));
    CHECK(!eq(1,2l));
    CHECK( eq(1,1u));
    CHECK( eq(0,0.0));
    CHECK( eq(0.0,0.0));
    CHECK( eq(1.0,1.0));
    CHECK(!eq(i1,i2));
    CHECK( eq(i1,i1));
    CHECK(!eq(i0,i1));
    CHECK(!eq(i1,i0));
    CHECK( eq(i0,i0));


    cout << "\n\n *** Test eq<fp>() ***\n";
    // triv
    CHECK(!eq(f1,d2));
    CHECK( eq(f1,f1));
    CHECK(!eq(f0,f1));
    CHECK(!eq(f1,f0));
    CHECK( eq(f0,f0));

    // compile time const evaluation
    CHECK( eq(1/3.0l,0.5l/1.5l));
    CHECK( eq(1/7.0l,2.0l/14.0l));

    CHECK( eq((f1*f2)/f3, 1/(f3/2)));
    CHECK(!eq(0.0f,   0.1*numeric_limits<float> ::epsilon()));
    CHECK( eq(d2, d2+     numeric_limits<double>::epsilon()));
    CHECK( eq(d2, d2+ 0.5*numeric_limits<double>::epsilon()));
    CHECK( eq(d2, d2+   2*numeric_limits<double>::epsilon()));
    CHECK( eq(d2, d2+  10*numeric_limits<double>::epsilon()));
    CHECK( eq(d2, d2+  20*numeric_limits<double>::epsilon()));
    CHECK(!eq(d2, d2+ 500*numeric_limits<double>::epsilon()));

    // big numbers
    float f=1e20;
    CHECK(!eq(f*0.0001     , f*(-0.0001)                                       )); 
    CHECK( eq(f*(f1*f2)/f3 , f*(1/(f3/2))                                      )); 
    CHECK(!eq(f*0.0f       , f*(0.1*    f1_ulp)          )); 
    CHECK( eq(f*d2         , f*(d2+     numeric_limits<double>::epsilon())  )); 
    CHECK( eq(f*d2         , f*(d2+0.5* numeric_limits<double>::epsilon())  )); 
    CHECK( eq(f*d2         , f*(d2+  2* numeric_limits<double>::epsilon())  )); 
    CHECK( eq(f*d2         , f*(d2+  10*numeric_limits<double>::epsilon()) )); 
    CHECK( eq(f*d2         , f*(d2+  20*numeric_limits<double>::epsilon()) )); 
    CHECK(!eq(f*d2         , f*(d2+ 500*numeric_limits<double>::epsilon()) )); 
    CHECK(!eq(f*0.0001     , f*((-0.0001))                                     )); 

    // small
    f=-1e-20;
    CHECK(!eq(f*0.0001     , f*(-0.0001)                                       )); 
    CHECK( eq(f*(f1*f2)/f3 , f*(1/(f3/2))                                      )); CHECK(!eq(f*0.0f       , f*(0.1*numeric_limits<float>::epsilon())          )); 
    CHECK( eq(f*d2         , f*(d2+     numeric_limits<double>::epsilon())  )); 
    CHECK( eq(f*d2         , f*(d2+ 0.5*numeric_limits<double>::epsilon())  )); 
    CHECK( eq(f*d2         , f*(d2+   2*numeric_limits<double>::epsilon())  )); 
    CHECK( eq(f*d2         , f*(d2+  10*numeric_limits<double>::epsilon()) )); 
    CHECK( eq(f*d2         , f*(d2+  20*numeric_limits<double>::epsilon()) )); 
    CHECK(!eq(f*d2         , f*(d2+ 500*numeric_limits<double>::epsilon()) )); 
    CHECK(!eq(f*0.0001     , f*((-0.0001))                                     )); 

    // near zero
    CHECK( eq(1.1E-20     , 0, 100,  1.                                           )); 


    cout << (all_pass ? "\n------------ all pass ------------\n" : "\n!!!!!!!!!  SOME FAILED  !!!!!!!!\n");
    exit(all_pass ? 0 : 1);
}

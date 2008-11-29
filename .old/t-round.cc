
#include <limits>
#include "../lvv/lvv.h"
#include "../lvv/lvvmath.h"


template<typename F, typename I> I round(F x)  { return I(x+0.5); }

///////////////////////////////////////////////////////////////////
                int
main() {

    cout << "\n\n *** Test equal<integral>() ***\n";
    cout << std::boolalpha;
    float pi=3.1415;
    float f9=9.999;
    cout << round<float,int>(pi) << endl;
    cout << round<float,int>(f9) << endl;
}



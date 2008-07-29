#include "lvvlib.h"
#include <cassert>
#include <boost/numeric/conversion/converter.hpp>

int main() {

    using namespace boost::numeric;
    typedef boost::numeric::converter<int,double> Int2Double ;

    PR1(Int2Double::convert(2.0));
    PR1(Int2Double()(3.14)); // As a function object.  The default rounding is trunc.

    try {
        double m = boost::numeric::bounds<double>::highest();
        PR1(Int2Double::convert(m)); // By default throws positive_overflow()
    }
    catch ( boost::numeric::positive_overflow const& ) {
        cout << "OVERFLOW\n";
    }

    return 0;
}


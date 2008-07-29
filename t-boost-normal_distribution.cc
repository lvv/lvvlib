#include <boost/math/distributions/normal.hpp>
using boost::math::normal; 
#include <boost/math/distributions/students_t.hpp>
using boost::math::students_t;

#include <iostream>
  using std::cout; using std::endl; using std::left; using std::showpoint; using std::noshowpoint;
#include <iomanip>
  using std::setw; using std::setprecision;
#include <limits>
  using std::numeric_limits;

int main() {
  cout << "Normal distribution";

    double step   = 1.; // in z
    double range  = 4; // min and max z                                                  = -range to +range.
    int precision = 17; // traditional tables are only computed to much lower precision.

    
    normal s; // standard normal distribution s(default mean = zero, and standard deviation = unity)
    cout << "Standard normal distribution, mean = "<< s.mean() << ", standard deviation = " << s.standard_deviation() << endl;

    // pdf  - probability distribution function
    for (double z = -range; z < range + step; z += step) { cout  <<  "pdf(z=" << z << ") = "  <<  pdf(s, z) << endl; }


    // p = cdf(z)    p of x being  < z
    for (double z = -range; z < range + step; z += step)   { cout << "p = cdf(z=" << z << ") = " << cdf(s, z) << endl; }



    cout << "z = quantile(p=0.01 ) =  " << quantile(s, 0.01) << endl;
    cout << "z = quantile(p=0.1  ) =  " << quantile(s, 0.1 ) << endl;
    cout << "z = quantile(p=0.2  ) =  " << quantile(s, 0.2 ) << endl;
    cout << "z = quantile(p=0.3  ) =  " << quantile(s, 0.3 ) << endl;
    cout << "z = quantile(p=0.4  ) =  " << quantile(s, 0.4 ) << endl;
    cout << "z = quantile(p=0.5  ) =  " << quantile(s, 0.5 ) << endl;
    cout << "z = quantile(p=0.6  ) =  " << quantile(s, 0.6 ) << endl;
    cout << "z = quantile(p=0.7  ) =  " << quantile(s, 0.7 ) << endl;
    cout << "z = quantile(p=0.8  ) =  " << quantile(s, 0.8 ) << endl;
    cout << "z = quantile(p=0.9  ) =  " << quantile(s, 0.9 ) << endl;
    cout << "z = quantile(p=0.99 ) =  " << quantile(s, 0.99) << endl;

    cout.precision(3);
    cout << showpoint << "\ncdf(s, s.standard_deviation()) = " << cdf(s, s.standard_deviation()) << endl;  // from -infinity to 1 sd
    cout << "cdf(complement(s, s.standard_deviation())) = " << cdf(complement(s, s.standard_deviation())) << endl;
    cout << "Fraction 1 standard deviation within either side of mean is " << 1 -  cdf(complement(s, s.standard_deviation())) * 2 << endl;
    cout << "Fraction 2 standard deviations within either side of mean is " << 1 -  cdf(complement(s, 2 * s.standard_deviation())) * 2 << endl;
    cout << "Fraction 3 standard deviations within either side of mean is " << 1 -  cdf(complement(s, 3 * s.standard_deviation())) * 2 << endl;

    exit(0);
}
//#include "stats.h"

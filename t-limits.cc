#include <iostream>
#include <limits>

using namespace std;

int main() {
    cout << " 1 The minimum value for char is " << (int)numeric_limits<char>::min() << endl;
    cout << " 2 The minimum value for int is  " << numeric_limits<int>::min() << endl;
    cout << " 3 The maximum value for char is " << (int)numeric_limits<char>::max() << endl;
    cout << " 4 The maximum value for int is  " << numeric_limits<int>::max() << endl;
    cout << " 5 The number of bits to represent a char is " << numeric_limits<char>::digits << endl;
    cout << " 6 The number of bits to represent an int is " << numeric_limits<int>::digits << endl;
    cout <<" 7 The number of digits representable in base 10 for float is " << numeric_limits<float>::digits10 << endl;
    cout << " 8 Is a char signed?              " << numeric_limits<char>::is_signed << endl;
    cout << " 9 Is an unsigned integer signed? " << numeric_limits<unsigned int>::is_signed << endl;
    cout << "10 Is an integer an integer? " << numeric_limits<int>::is_integer << endl;
    cout << "11 Is a float an integer?   " << numeric_limits<float>::is_integer << endl;
    cout << "12 Is an integer exact? " << numeric_limits<int>::is_exact << endl;
    cout << "13 Is a float exact?  " << numeric_limits<float>::is_exact << endl;
    cout << "14 The radix for float is            "  << numeric_limits<float>::radix << endl;
    cout << "15 The epsilon for float is          " << numeric_limits<float>::epsilon() << endl;
    cout << "16 The round error for float is      " << numeric_limits<float>::round_error() << endl;
    cout << "17 The minimum exponent for float is " << numeric_limits<float>::min_exponent << endl;
    cout << "18 The minimum exponent in base 10   " << numeric_limits<float>::min_exponent10 << endl;
    cout << "19 The maximum exponent is           " << numeric_limits<float>::max_exponent << endl;
    cout << "20 The maximum exponent in base 10   " << numeric_limits<float>::max_exponent10 << endl;
    cout << "21 Can float represent positive infinity?  " << numeric_limits<float>::has_infinity << endl;
    cout << "22 Can double represent positive infinity? " << numeric_limits<double>::has_infinity << endl;
    cout << "23 Can int represent positive infinity? " << numeric_limits<int>::has_infinity << endl;
    cout << "24 Can float represent a NaN?           " << numeric_limits<float>::has_quiet_NaN << endl;
    cout << "25 Can float represent a signaling NaN? " << numeric_limits<float>::has_signaling_NaN << endl;
    cout << "26 Does float allow denormalized values?   " << numeric_limits<float>::has_denorm << endl;
    cout << "27 Does float detect denormalization loss? " << numeric_limits<float>::has_denorm_loss << endl;
    cout << "28 Representation of positive infinity for float " << numeric_limits<float>::infinity() << endl;
    cout << "29 Representation of quiet NaN for float         " << numeric_limits<float>::quiet_NaN() << endl;
    cout << "30 Minimum denormalized number for float         " << numeric_limits<float>::denorm_min() << endl;
    cout << "31 Minimum positive denormalized value for float " << numeric_limits<float>::denorm_min() << endl;
    cout << "32 Does float adhere to IEC 559 standard?  " << numeric_limits<float>::is_iec559 << endl;
    cout << "33 Is float bounded? " << numeric_limits<float>::is_bounded << endl;
    cout << "34 Is float modulo?  " << numeric_limits<float>::is_modulo << endl;
    cout << "35 Is int modulo?    " << numeric_limits<float>::is_modulo << endl;
    cout << "36 Is trapping implemented for float?    " << numeric_limits<float>::traps << endl;
    cout << "37 Is tinyness detected before rounding? " << numeric_limits<float>::tinyness_before << endl;
    cout << "38 What is the rounding style for float? " << (int)numeric_limits<float>::round_style << endl;
    cout << "39 What is the rounding style for int? " << (int)numeric_limits<int>::round_style << endl;
    cout << "40 How does a float represent a signaling NaN? " << numeric_limits<float>::signaling_NaN() << endl;
    cout << "41 Is int specialized? " << numeric_limits<float>::is_specialized << endl;
}

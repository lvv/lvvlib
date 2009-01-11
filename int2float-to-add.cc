Nice trick :) Here is a generalized implementation:

First some supporting code.

Code: Select all
    template<
        uint taNumber>
    struct NumberOfSignificantBits;

    template<>
    struct NumberOfSignificantBits<0>
    {
        enum { VALUE = 0 };
    };

    template<
        uint taNumber>
    struct NumberOfSignificantBits
    {
        enum { VALUE = 1 + NumberOfSignificantBits<(taNumber >> 1)>::VALUE };
    };

    template<
        uint taNumber>
    struct FloatConvertShift
    {
        enum
        {
            SHIFT_LEFT = NumberOfSignificantBits<taNumber>::VALUE < 23,
            SHIFT_AMOUNT = SHIFT_LEFT ?
                23 - NumberOfSignificantBits<taNumber>::VALUE :
                NumberOfSignificantBits<taNumber>::VALUE - 23
        };
    };



And then the actual function:

Code: Select all
    template<
        uint taMaxValue>
    float convertToFloat01(
        const uint aValue)
    {
        union { int i; float f; };

        // this branch will be optimized away by the compiler
        if(FloatConvertShift<taMaxValue>::SHIFT_LEFT)
        {
            i = 0x3F800000 | (aValue << FloatConvertShift<taMaxValue>::SHIFT_AMOUNT);
        }
        else
        {
            i = 0x3F800000 | (aValue >> FloatConvertShift<taMaxValue>::SHIFT_AMOUNT);
        }

        return f - 1.0f;
    }



You just throw it the number and the maximum value your integer could get:

Code: Select all
    convertToFloat01<15>(8);           // returns 0.5
    convertToFloat01<255>(8);          // returns 0.03125
    convertToFloat01<RAND_MAX>(10000); // returns 0.305176



With a bit more work (e.g. traits for the size of the mantissa) you could generalize it to work with any common floating point type (float, double, long double).
-----------------------------------------------------------------------------


    * Reply with quote

Re: gdb and C give different numerical results....

Postby tbp on 27 Nov 2008, 06:36
Err, except your generalization is leaking bits everywhere and that defeats the purpose; if you insist about obfuscating generalizing then something to the tune of

Code: Select all
    typedef unsigned int uint32_t;
    typedef unsigned long long uint64_t;

    template<typename T> struct fp_details;
    template<> struct fp_details<float> { enum { w = 32, mnt_w = 23, exp_w = 8, sgn_w = 1 }; typedef uint32_t base_type; };
    template<> struct fp_details<double> { enum { w = 64, mnt_w = 53, exp_w = 11, sgn_w = 1 }; typedef uint64_t base_type; };

    template<typename T> struct twiddler : fp_details<T> {
       typedef typename fp_details<T>::base_type base_type;
       typedef T fp_type;
       enum { exp_bias = (1 << (exp_w - 1)) - 1, mnt_fix = w - mnt_w };
       template<unsigned sgn, int exp> static fp_type construct(base_type bits) {
          union { base_type u; fp_type f; } num = {
             (base_type(sgn) << (w - sgn_w)) |
             (((base_type(exp_bias+exp) << (w - exp_w)) >> sgn_w)) |
             (bits >> mnt_fix)
          };
          return num.f;
       }
       // [2^exp_scale, 2^exp_scale+1) + sgn_offset*2^exp_offset
       template<int exp_scale, int exp_offset, unsigned sgn_offset> static fp_type ranged(base_type bits) {
          return construct<0, exp_scale>(bits) + construct<sgn_offset, exp_offset>(0);
       }
       // [2^exp_scale, 2^exp_scale+1) + sgn_offset*1.5*2^exp_offset
       template<int exp_scale, int exp_offset, unsigned sgn_offset> static fp_type centered(base_type bits) {
          return construct<0, exp_scale>(bits) + construct<sgn_offset, exp_offset>(1 << (mnt_w+mnt_fix-1));
       }
    };

    int main(int argc, char *argv[]) {
       float foo = twiddler<float>::ranged<+0, +0, 1>(rand());   // [2^0, 2^1) - 2^+0 -> [0, 1)
       double bar = twiddler<double>::centered<+1, +1, 1>(rand());   // [2^1, 2^2) - 1.5*2^1 -> [-1, +1)
       return 0;
    }



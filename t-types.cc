#include <iostream>
#include <limits>
#include <typeinfo>
#include <iomanip>
using namespace std;

template <class Type>
void printLimits(const Type& t) {
    cout << "\ninformation for " << typeid(t).name() << endl;
    cout << "min =\t" << numeric_limits<Type>::min() << endl;
    cout << "max =\t" << numeric_limits<Type>::max() << endl;
    cout << "#bits=\t" << numeric_limits<Type>::digits << endl;
    cout << "is integral? " << boolalpha << numeric_limits<Type>::is_integer << endl;
}

int main() {
    printLimits(0);
    printLimits(0u);
    printLimits(0L);
    printLimits('a');
    printLimits(static_cast<unsigned char>('a'));
    printLimits(0.0);
    printLimits(static_cast<float>(0.0));
    return 0;
}

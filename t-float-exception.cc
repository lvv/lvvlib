#include "lvv.h"
#include <iostream>
#include <fenv.h>
#include <limits>

using namespace std;

//extern "C" int feenableexcept (int excepts)

int main () {

    float f999=999;
    float   f1=1;
    float   f0=0;
    char    c1=1;
    int     iMAX=numeric_limits<int>::max();
    unsigned     ui0=0;

    PR1(iMAX+1000);
    PR1(c1+999.0);
    
    PR1(int(char(f999)));
    
    ui0=ui0-1;
    PR1(ui0);


    cout << " f1/f0 = " << flush << f1/ f0  << endl;
    cout << " f1/f0 = " << flush ;
        cout << f1/f0 << endl;
    ////////////////////////////////////////////////////////////////////////////
    feenableexcept (FE_ALL_EXCEPT);  // see: man fenv
    cout << " enabled \n";

    PR1(iMAX+1000);
    PR1(c1+999.0);
    
    PR1(int(char(f999)));

    ui0=ui0-1;
    PR1(ui0);

    cout << " f1/f0 = " << flush << f1/ f0  << endl;
    cout << " f1/f0 = " << flush ;
        cout << f1/f0 << endl;

}

#include <iostream>
#include <lvv/lvv.h>
#include <lvv/math.h>


using namespace std;

int main() {

    lvv::setup_fpe();


    ////////////////////////////////////////////////////// INTS
    char    c1=1;
    int     iMAX=numeric_limits<int>::max();
    unsigned volatile int  random;
    unsigned     ui0=0;

    PR1(iMAX+1000);
    PR1(c1+999.0);
    
    PR1(int(char((float)999)));
    
    ui0=ui0-1;
    PR1(ui0);
    PR1(iMAX+1000);
    PR1(c1+999.0);
    ui0=ui0-1;
    PR1(ui0);

    /////////////////////////////////////////////////////// FLOAT
    float   fMAX=numeric_limits<float>::max();
    float   fMIN=numeric_limits<float>::min();
    float   f999=999;
    float   f1=1;
    float   f0=0;

    cout << " UNDEFLOW?   f999+r=fMIN = " << flush ;   cout << f999+random+fMIN  << endl; 
    cout << " UNDEFLOW? - no      0/1 = " << flush ;   cout << 0.0/1.0  << endl; 
    cout << " UNDEFLOW? - no      0/1 = " << flush ;   cout << 0.0/1.0  << endl; 
    cout << " OVERFLOW:     fMAX*fMAX = " << flush ;   cout << fMAX*fMAX  << endl;  
    cout << " UNDEFLOW:     fMIN/fMAX = " << flush ;   cout << fMIN/fMAX  << endl; 
    cout << " DEV-BY-ZERO:  f1/f0     = " << flush;    cout << f1/f0 << endl;     

    return 0;

} // vim:nu noic: 

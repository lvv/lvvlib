
#include <unistd.h>
#include <iostream>
#include <cmath>
#include <lvv/lvv.h>
#include <asmlib.h>
using namespace std;
using namespace lvv;

#include "../lvv/timer.h"
using lvv::Timer;


int main() {
    Timer t;

    t.print("timer.print() MSG test");

    FMT("timer()=%d\n") % t();

    double sum =0;
    for (long i = 0; i< 1000000; i++)
    	sum += sqrt(i);

    cout << t.interval_ticks() / 1000000. << flush << endl;
    t.print("2nd print()");

    for (long i = 0; i< 100000000; i++)
    	sum += sqrt(i);

    t.print("3rd print()");

    cout << "stream << test "  <<  t << endl;

    sleep(1); // this is CPU timer, not a real time timer

    cout << "Last line will be from Timer destructor \n";
    return 0;
}

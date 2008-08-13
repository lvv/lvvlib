
#include <unistd.h>
#include <iostream>
using namespace std;

#include "../lvv/lvv.h"
using lvv::Timer;


int main() {
    Timer t;

    t.print("timer.print() test");

    FMT("timer()=%d\n") % t();

    cout << "stream << test "  <<  t << endl;

    sleep(1); // this is CPU timer, not a real time timer
    cout << "Last line will be from Timer destructor \n";
    return 0;
}

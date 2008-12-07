
#include <iostream>
//#include <cmath>
//#include <lvv/lvv.h>
//#include <asmlib.h>



using namespace std;
//using namespace lvv;

#include "../lvv/timer.h"
using lvv::Timer;


int main() {

	
	cout << lvv::read_tick() << "  -- 1 \n";
	cout << lvv::read_tick() << "  -- 1 \n";
	cout << lvv::read_tick() << "  -- 1 \n";
	cout << lvv::read_tick() << "  -- 1 \n";
	cout << lvv::read_tick() << "  -- 1 \n";
	cout << lvv::read_tick() << "  -- 1 \n";
	cout << lvv::read_tick() << "  -- 1 \n";
	cout << lvv::read_tick() << "  -- 1 \n";
	cout << lvv::read_tick() << "  -- 1 \n";
	cout << "Timer CTOR\n";
	Timer verboze_t(true);
	Timer t;
	t.print("timer.print() MSG test");

	cout << "timer()=" <<  t() << endl;
	cout << "\n***  usleep 1000\n";
	usleep(useconds_t(10000));
		cout << "interval_ticks(): " << t.interval_ticks()  << flush << endl;
		t.print("2nd print()");

	cout << "\n***  usleep 2000\n";
	usleep(useconds_t(20000));
		t.print("3rd print()");
		cout << "stream << test "  <<  t << endl;

	cout << "\n***  usleep 3000\n";
	usleep(useconds_t(30000));

    cout << "Last line will be from Timer destructor \n";
    return 0;
}

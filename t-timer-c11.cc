
#include <iostream>

using namespace std;
//using namespace lvv;

#include <stdint.h>
#include <lvv/timer.h>
#include <chrono>
#include <unistd.h>
//using lvv::timer_t;


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
	cout << "timer_t CTOR\n";
	lvv::timer_t verboze_t(true);
	lvv::timer_t t;
	auto  start_t = std::chrono::system_clock::now();
	t.print("timer.print() MSG test");

	cout << "timer()=" <<  t() << endl;
	cout << "\n***  usleep 1000\n";
	usleep(useconds_t(10000));
		cout << "interval_ticks(): " << t.interval_ticks()  << '\n';
		t.print("2nd print()");

	cout << "\n***  usleep 2000\n";
	usleep(useconds_t(20000));
		t.print("3rd print()");
		cout << "stream << test "  <<  t << endl;

	cout << "\n***  usleep 3000\n";
	usleep(useconds_t(30000));
	auto  end_t = std::chrono::system_clock::now();
	auto  dur_t = end_t - start_t;
	auto  dur_ms = std::chrono::duration_cast <std::chrono::milliseconds>(dur_t);
	cout << "\nchrono timer: " << dur_ms.count() << " ms\n";

    cout << "Last line will be from timer_t destructor \n";
}

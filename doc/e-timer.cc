#include <lvv/timer.h>
	using lvv::Timer;
	using lvv::read_tick;

int main() {
	Timer	tm;	// CTOR inits total counters and interval counters
			// any timer read, resets conresponding interval counter
			// reset() - resets all intervals timers

	cout << "\n usleep(30000) ... \n";  		usleep(useconds_t(30000));

	cout << "\n interval_ticks(): 	" <<		tm.interval_ticks();
	cout << "\n interval_wall():  	" <<		tm.interval_wall();
	cout << "\n interval_cpu():   	" <<		tm.interval_cpu();

	cout << "\n\n usleep(20000) ... \n";		usleep(useconds_t(20000));

	cout << "\n total_ticks():    	" <<		tm.total_ticks();
	cout << "\n total_wall():     	" <<		tm.total_wall();
	cout << "\n total_cpu():      	" <<		tm.total_cpu();

	cout << "\n\n Raw CPU tick reader:   "	<<	read_tick()	<< endl;
}

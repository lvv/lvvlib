	
				#ifndef LVV_BENCHMARK_H
				#define LVV_BENCHMARK_H

	#ifndef		REPEAT	
	#define		REPEAT		7
	#endif

		
	///////////////////////////////////
	#include <cstdint>
	#include <iostream>
		using  namespace std;

	#include <lvv/array.h>
		using lvv::array;
		using lvv::mk_array;

	#include <lvv/timer.h>
		using lvv::timer_t;




///////////////////////////////////////////////////////////////////////////////////////////// STATIC  VARS
	array<float,REPEAT>	tick;
	timer_t			t(true);
	float			sec, ticks;



///////////////////////////////////////////////////////////////////////////////////////////// ONE-TEST -> ONE-LINE PRINT
// called multile time from test-cycle (cycle var: r)
// print EXPR value (on r==0), individual times,  minumal time,  test name
#define PRINT(NAME,EXPR)	\
	tick[r] = ticks = t.interval_ticks() / float (N);     sec = t.interval_cpu();		\
	if (r==0)		cerr	<< setprecision(6) << setw(11) << (EXPR) << "  " << setprecision(3) << setw(8) << sec <<"\t";\
	/* any r */		cerr	<< "\t" <<  std::fixed << ticks; \
	if (r==(REPEAT-1))	cerr	<< "\t\t" <<  tick.min() << "  \t" << NAME << endl;\
	t.interval_ticks();

///////////////////////////////////////////////////////////////////////////////////////////// ONLY TICKS
// called multile time from test-cycle (cycle var: r)
#define PRINT1	\
	tick[r] = ticks = t.interval_ticks() / float (N);     sec = t.interval_cpu();		\
	if (r==(REPEAT-1))	cerr	<<  setprecision(3) << setw(8) <<  tick.min() ;\
	t.interval_ticks();

////////////////////////////////////////////////////////////////////////////////////////////  PRINT CONFIG
#define BENCHMARK_HEADER	  cerr	/*<< "*** TYPE:  "  << LVV_STR(TYPE) << endl*/ \
					<< "*** REPEAT:"  << REPEAT << endl\
					<< "*** ID:    "  << "" ID << endl; \
				cerr <<  "\nValue\tSeconds\t\tTick/Cycle ...   Min-Tick/Cycle \t Method\n" << setprecision(4);

				#endif  // LVV_BENCHMARK_H

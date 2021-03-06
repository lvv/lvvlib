//
// TODO
// 	http://bryanstamour.com/2012/05/13/timing-functions-with-chrono.html
//	http://solarianprogrammer.com/2012/10/14/cpp-11-timing-code-performance/

	#ifndef  LVV_TIMER_H
	#define  LVV_TIMER_H

	// this is for uint64_t on gcc-4.4
	//#define _GLIBCXX_USE_C99_STDINT_TR1

	#include <sys/time.h>
	#include <sys/resource.h>

	#include <cstdlib>
	#include <cstdint>
	#include <iostream>
	#include <iomanip>
		using std::ostream;
		using std::endl;
		using std::cerr;
		using std::cout;
		using std::setprecision;
	#include <string>


	namespace lvv {

// TR http://www.viva64.com/en/b/0097/

/*  OpenMP thread time?
         double omp_time = 0;
         double last_omp_time;
         last_omp_time = omp_time;
         omp_time = omp_get_wtime();

         int static cnt = 0;
         MSG("(%d/%.1fs ? :%.1fs elapsed)%8t") % cnt++  %timer() %(omp_time-last_omp_time);  
	--------------------------------
	Timers:  http://www.strchr.com/performance_measurements_with_rdtsc
*/

/////////////////////////////////////////////////////////////////////////////////////  READ_TICK

// TODO:  new stop start seq  --- http://blog.regehr.org/archives/330
#if defined(__x86_64) || defined (__i386)

	uint64_t static	read_tick() {				// tested with with x86_64 only. 
		uint64_t now_tick;
		asm volatile (	"subl	%%eax,	%%eax;"
			"cpuid;"
			"rdtsc;"
			#if defined(__x86_64)
				"shlq	$32,	%%rdx;"
				"orq	%%rdx,	%%rax;"		// combine into 64 bit register
				"movq	%%rax,	%[now_tick];"
			#endif
			#if defined(__i386)
				"movl	%%eax,	%[now_tick];"
				"lea	%0, 	%%eax;"
				"movl	%%edx,	4(%%eax);"
			#endif
			"cpuid;"
				 :[now_tick] "=m"(now_tick)        // output
				 :
			#if defined(__x86_64)
				 :"rax", "rdx", "rbx","rcx", "rdx"         // clobbered register
			#else
				 :"ebx","ecx", "edx"         // clobbered register
			#endif
		 );
		return now_tick;
	}
#endif

	class timer_t;
	static ostream&   operator<< (ostream& os, timer_t& t) __attribute__((unused)) ;

class timer_t { //=========================================== TIMER
			// TR http://www.viva64.com/en/b/0097/
			// -------------
			// article about hi-res timers: http://www.devx.com/cplus/Article/35375/0/page/2
			// see also OpenMP timer: http://gcc.gnu.org/onlinedocs/libgomp/omp_005fget_005fwtime.html#omp_005fget_005fwtime
			// ---
			//      > how do you get the divide by 10?
			//
			//      The TSC updates at the rate the bus clock ticks, and when it updates
			//      it adds the (processor clock speed)/(bus clock speed) ratio, rather
			//      than 1. Since my processor clock speed is 2.67 GHz and the bus clock
			//      is 267 MHz, this ratio is 10 and so every TSC reading will be divisible
			//      by 10. Just copy and paste some of your raw TSC measurements here
			//      and the readers will be able to figure out your bus clock ratio.
			//      When the ratio is 10, it is quite obvious because the last digit of
			//      every measurement is zero, but for other ratios it might not be so
			//      evident at a glance.
			//
    private:
		bool		verbose_dtor;

		// Tick (cpu cycle)
		#if defined(__x86_64) || defined (__i386)
		uint64_t ctor_tick;
		uint64_t interval_start_tick;
		uint64_t now_tick;
		uint64_t overhead;
		#endif

		// TV - wall clock time
		timeval		ctor_tv;
		timeval		interval_start_tv;
		timeval		now_tv;

		// RU - CPU time
		struct rusage	ctor_ru;
		struct rusage	interval_start_ru;
		struct rusage	now_ru;

		double
	wall_time_at(timeval tv) { return tv.tv_sec + tv.tv_usec / 1000000.;  };

		double
	cpu_time_at(struct rusage ru) {
            return
                ru.ru_utime.tv_sec + ru.ru_utime.tv_usec / 1000000. +
                ru.ru_stime.tv_sec + ru.ru_stime.tv_usec / 1000000.;
        };

public:



timer_t(bool verbose_dtor=false) : verbose_dtor(verbose_dtor)     {
	#if defined(__x86_64) || defined (__i386)
	ctor_tick = interval_start_tick = read_tick();
	overhead = interval_ticks();
	#endif
	gettimeofday(&now_tv, NULL);		ctor_tv = interval_start_tv = now_tv;
	getrusage(RUSAGE_SELF, &now_ru);	ctor_ru = interval_start_ru = now_ru;
 };

~timer_t()    {
	if (verbose_dtor) {
		if (total_cpu() < 0.001)   cerr  << "(*) on exit: cpu time: "  << std::fixed << total_cpu()/1000000  << " μs    " << "wall time: " << total_wall()/1000000 << " μs " << endl; 
		else 			   cerr  << "(*) on exit: cpu time: "  << std::fixed << total_cpu()  << " s    " << "wall time: " << total_wall() << " s " << endl; 
	}
	// memory report
	//system("egrep -r '^Vm(Peak|Size|RSS|Data|Stk|Exe|Lib)' /proc/$PPID/status |sed 's/^Vm//; s/ kB/k/; s/  *//'|tr '	\n' ' '");
	    // amount of unrequested memory  -   CommitLimit - Committed_AS
 };

void reset() {
			#if defined(__x86_64) || defined (__i386)
	interval_ticks();
			#endif
	interval_cpu();
	interval_wall();
 }
	
			#if defined(__x86_64) || defined (__i386)
                        uint64_t
interval_ticks()                { 
	uint64_t now_tick = read_tick();
	uint64_t ticks = now_tick - interval_start_tick;
	interval_start_tick = now_tick;
	return  ticks;
 }
			 #endif

			double
interval_wall()		{ 
	gettimeofday(&now_tv, NULL);
	double sec =  wall_time_at(now_tv) - wall_time_at(interval_start_tv); 
	interval_start_tv = now_tv; 
	return  sec;
 }
			double
interval_cpu()		{ 
	getrusage(RUSAGE_SELF, &now_ru);
	double sec =  cpu_time_at(now_ru) - cpu_time_at(interval_start_ru); 
	interval_start_ru = now_ru; 
	return  sec;
 }


			#if defined(__x86_64) || defined (__i386)
uint64_t total_ticks	()	{ return  read_tick() - ctor_tick; }
			#endif
double	total_wall	()	{ gettimeofday(&now_tv, NULL);		return  wall_time_at(now_tv) - wall_time_at(ctor_tv); }

double	total_cpu	()	{ getrusage(RUSAGE_SELF, &now_ru);	return  cpu_time_at (now_ru) - cpu_time_at (ctor_ru); }

double	operator() 	()	{ return interval_wall(); }

	void
print(std::string msg="") {

	if (msg=="") 
		std::cerr << std::setw(13) << "(timer)   " << std::flush;
	else {
		std::cerr <<"   ⌛ " << msg << "    " << std::flush; 
	};

	std::cerr << std::setprecision(4);
			#if defined(__x86_64) || defined (__i386)
	std::cerr << "overhead:" << overhead << "t   " ;
	std::cerr << "interval:" << interval_ticks() << "t   " ;
	std::cerr << "total:   " << total_ticks(   ) << "t   " ;
			#endif
	std::cerr << "interval-wall:" << interval_wall() << "s   " ;
	std::cerr << "interval-cpu: " << interval_cpu( ) << "s   " ;
	std::cerr << "total-wall:   " << total_wall(   ) << "s   " ;
	std::cerr << "total-cpu:    " << total_cpu(    ) << "s   " ;
	std::cerr << std::endl;
 };

        friend std::ostream& operator<< (std::ostream& os, timer_t& t);
};


	static ostream& 
operator<< (ostream& os, timer_t& t)   {
	os << setprecision(5) << " " << t() << "s ";
	return os;
 }


        void static  __attribute__((unused))
progress_dots(long var, long first, long last, std::string msg="" ) { //=============================================== progress_dots()

	static bool first_time = true;
	static int  columns = 0; 
	static int  width;
	
	if (first_time)  {
	
		first_time=false;
		char* columns_str=getenv("COLUMNS");
		
		if (columns_str)
		    columns=atoi(columns_str);
		    
		width = columns - msg.length();
	}
	
	if (!columns)   return;
	if ( var==first)   cerr << msg; 
	int div=(last-first)/width;
	if ( (var-first) % (div+1) == 0 )   cerr << "." << std::flush;
	if ( var == last )   cerr << endl;
 }

	} // namespace lvv
	#endif // LVV_TIMER_H

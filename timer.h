
	#ifndef  LVV_TIMER_H
	#define  LVV_TIMER_H

	// this is for uint64_t on gcc-4.4
	//#define _GLIBCXX_USE_C99_STDINT_TR1

	#include <sys/time.h>
	#include <sys/resource.h>

	#include <stdlib.h>
	#include <stdint.h>
	#include <iostream>
	#include <iomanip>
		using std::ostream;
		using std::endl;
		using std::cout;
		using std::setprecision;
	#include <string>


	namespace lvv {

/*  OpenMP thread time?
         double omp_time = 0;                                                                                                                               
         double last_omp_time;
         last_omp_time = omp_time;
         omp_time = omp_get_wtime();
 
         int static cnt = 0;   
         MSG("(%d/%.1fs ? :%.1fs elapsed)%8t") % cnt++  %timer() %(omp_time-last_omp_time);  
*/

/////////////////////////////////////////////////////////////////////////////////////  READ_TICK
#if defined(__x86_64) || defined (__i386)
uint64_t	read_tick() {				// tested with with x86_64 only. 
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

class Timer { //=========================================== TIMER
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

        double wall_time_at(timeval tv) { return tv.tv_sec + tv.tv_usec / 1000000.;  };

double cpu_time_at(struct rusage ru) {
            return 
                ru.ru_utime.tv_sec + ru.ru_utime.tv_usec / 1000000. +
                ru.ru_stime.tv_sec + ru.ru_stime.tv_usec / 1000000.; 
        };

public:



Timer(bool dtor=false) : verbose_dtor(dtor)     {
	#if defined(__x86_64) || defined (__i386)
	ctor_tick = interval_start_tick = read_tick();
	overhead = interval_ticks();
	#endif
	gettimeofday(&now_tv, NULL);		ctor_tv = interval_start_tv = now_tv;
	getrusage(RUSAGE_SELF, &now_ru);	ctor_ru = interval_start_ru = now_ru;
 };

~Timer()    {
	if (verbose_dtor)
		cout  << "(*) on exit: cpu time: "  << total_cpu()  << "s    " << "wall time: " << total_wall() << "s " << endl; 
	// memory report
	//system("egrep -r '^Vm(Peak|Size|RSS|Data|Stk|Exe|Lib)' /proc/$PPID/status |sed 's/^Vm//; s/ kB/k/; s/  *//'|tr '	\n' ' '");
	    // amount of unrequested memory  -   CommitLimit - Committed_AS
};

void reset() {
			#if defined(__x86_64) || defined (__i386)
	interval_ticks();
			#endif
	interval_cpu();
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
double	total_ticks	()	{ return  read_tick() - ctor_tick; }
			#endif
double	total_wall	()	{ gettimeofday(&now_tv, NULL);		return  wall_time_at(now_tv) - wall_time_at(ctor_tv); }
double	total_cpu	()	{ getrusage(RUSAGE_SELF, &now_ru);	return  cpu_time_at (now_ru) - cpu_time_at (ctor_ru); }
double	operator() 	()	{ return interval_wall(); }

	void
print(std::string msg="") {

	if (msg=="") 
		std::cout << std::setw(13) << "(timer)   ";
	else {
		std::cout <<"   ⌛ " << msg << "    "; 
	};

	std::cout << std::setprecision(4);
			#if defined(__x86_64) || defined (__i386)
	std::cout << "overhead:" << overhead << "t   " ;
	std::cout << "interval:" << interval_ticks() << "t   " ;
	std::cout << "total:   " << total_ticks(   ) << "t   " ;
			#endif
	std::cout << "interval-wall:" << interval_wall() << "s   " ;
	std::cout << "interval-cpu: " << interval_cpu( ) << "s   " ;
	std::cout << "total-wall:   " << total_wall(   ) << "s   " ;
	std::cout << "total-cpu:    " << total_cpu(    ) << "s   " ;
	std::cout << std::endl;
 };

        friend std::ostream& operator<< (std::ostream& os, Timer& t);
 };

ostream& operator<< (ostream& os, Timer& t) {
	os << setprecision(5) << " " << t() << "s ";
	return os;
 }


        void
progress_dots(long var, long first, long last, std::string msg="" ) { //=============================================== progress_dots()

	static bool first_time = true;
	static int  columns = 0; 
	static int  width;
	
	if (first_time) {
	
		first_time=false;
		char* columns_str=getenv("COLUMNS");
		
		if (columns_str)
		    columns=atoi(columns_str);
		    
		width = columns - msg.length();
	}
	
	if (!columns)   return;
	if ( var==first)   cout << msg; 
	int div=(last-first)/width;
	if ( (var-first) % (div+1) == 0 )   cout << "." << std::flush;
	if ( var == last )   cout << endl;
 }

	} // namespace lvv
	#endif // LVV_TIMER_H


	#ifndef  LVV_TIMER_H
	#define  LVV_TIMER_H

	#include <sys/time.h>
	#include <sys/resource.h>

	#include <stdlib.h>
                    
	namespace lvv {

/*  OpenMP thread time?
         double omp_time = 0;                                                                                                                               
         double last_omp_time;
         last_omp_time = omp_time;
         omp_time = omp_get_wtime();
 
         int static cnt = 0;   
         MSG("(%d/%.1fs ? :%.1fs elapsed)%8t") % cnt++  %timer() %(omp_time-last_omp_time);  
*/

class Timer { //=========================================== TIMER
                        // too late, I've found almost the same impl at http://www.boost.org/doc/libs/1_35_0/libs/timer/timer.htm
			// article about hi-res timers: http://www.devx.com/cplus/Article/35375/0/page/2
			// see also OpenMP timer: http://gcc.gnu.org/onlinedocs/libgomp/omp_005fget_005fwtime.html#omp_005fget_005fwtime
    private: 
	// RU - CPU time
	// TV - wall clock time

        timeval		ctor_tv; 
        timeval		interval_start_tv; 
        timeval		now_tv; 

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

Timer()     {
	gettimeofday(&now_tv, NULL);	ctor_tv = interval_start_tv = now_tv;
	getrusage(RUSAGE_SELF, &now_ru);	ctor_ru = interval_start_ru = now_ru;
 };

~Timer()    {
	cout  << "(*) on exit: cpu time: "  << total_cpu()  << "s    " << "wall time: " << total_wall() << "s " << endl; 
	// memory report
	//system("egrep -r '^Vm(Peak|Size|RSS|Data|Stk|Exe|Lib)' /proc/$PPID/status |sed 's/^Vm//; s/ kB/k/; s/  *//'|tr '	\n' ' '");
	    // amount of unrequested memory  -   CommitLimit - Committed_AS
};

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


double	total_wall	()	{ gettimeofday(&now_tv, NULL);		return  wall_time_at(now_tv) - wall_time_at(ctor_tv); }
double	total_cpu	()	{ getrusage(RUSAGE_SELF, &now_ru);	return  cpu_time_at (now_ru) - cpu_time_at (ctor_ru); }
double	operator() 	()	{ return interval_wall(); }

	void
print(string msg="") {

	if (msg=="") 
		cout << setw(13) << "(timer)   ";
	else {
		cout <<"          ⌛ " << msg << "    "; 
	};

	cout << "interval-wall:" << interval_wall() << "s   " ;
	cout << "interval-cpu: " << interval_cpu( ) << "s   " ;
	cout << "total-wall:   " << total_wall(   ) << "s   " ;
	cout << "total-cpu:    " << total_cpu(    ) << "s   " ;
	cout << endl;
 };

        friend ostream& operator<< (ostream& os, Timer& t);
 };

ostream& operator<< (ostream& os, Timer& t) {
	os << setprecision(5) << " " << t() << "s ";
	return os;
 }


        void
progress_dots(long var, long first, long last, string msg="" ) { //========================================================= progress_dots()

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
	if ( (var-first) % (div+1) == 0 )   cout << "." << flush;
	if ( var == last )   cout << endl;
 }

	} // namespace lvv
	#endif // LVV_TIMER_H

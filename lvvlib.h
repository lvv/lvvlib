    #ifndef  LVVLIB_H
    #define  LVVLIB_H

    #include <iostream> 
    #include <iomanip>
    #include <sys/time.h>
    #include <sys/resource.h>

	#include <boost/lexical_cast.hpp>
	using boost::lexical_cast; 

	#include <boost/format.hpp>
	using boost::format; 
	#define FMT(f)	cout << format(f)


    #if  defined(NDEBUG) && defined(DEBUG)
        #undef DEBUG
    #endif

    #if  ! defined(NDEBUG)  && ! defined(DEBUG)
        #define NDEBUG
    #endif


///////////////////////////////////////////////////////////////////////////   MAP SELECTION

    #ifdef      UNORDERED_MAP
        #include    <tr1/unordered_map>
        #define     MAP    tr1::unordered_map          
    #endif

    #ifdef      BT
        #include    <map>
        #define     MAP    map
    #endif
    
    // FIXME add || http://developer.apple.com/documentation/DeveloperTools/gcc-4.0.1/cpp/Defined.html#Defined
    #ifndef     MAP
        // SPARSE HASH (default)
        #include    <google/sparse_hash_map>
        #define     MAP    google::sparse_hash_map
    #endif

    #ifndef     SET
        #include    <google/sparse_hash_set>
        #define     SET    google::sparse_hash_set
    #endif

    using std::flush;
    using std::string;
    using std::cout;
    using std::cerr;
    using std::endl;
    using std::setw;
    using std::ostream;
    using std::setprecision;

    namespace lvv {

 ////////////////////////////////////////////////////////////////////////////////////////////////////   
                    
class Timer { //=========================================== TIMER
                        // ther is similar impl at http://www.boost.org/doc/libs/1_35_0/libs/timer/timer.htm
						// article about hi-res timers: http://www.devx.com/cplus/Article/35375/0/page/2
    private: 
        timeval  creator_tv; 
        timeval  tv; 

        struct rusage creator_ru;        
        struct rusage ru;        

        double cpu_s(struct rusage ru) {
            return 
                ru.ru_utime.tv_sec + ru.ru_utime.tv_usec / 1000000. +
                ru.ru_stime.tv_sec + ru.ru_stime.tv_usec / 1000000.; 
        };

    public:
        Timer()     {
            // FIXME add prefix lable
            gettimeofday(&tv, NULL);        creator_tv=tv;
            getrusage(RUSAGE_SELF, &ru);    creator_ru=ru;
        };

        ~Timer()    {
            // calc real time 
            timeval  now_tv; 
            gettimeofday(&now_tv, NULL);
            double real_sec =
                    (now_tv.tv_sec  - creator_tv.tv_sec) +
                    (now_tv.tv_usec - creator_tv.tv_usec)/1000000.;

            // calc cpu time 
            ru=creator_ru;
            double cpu_sec=(*this)(); 
            // print
            cout  << "(*) on exit: cpu time: "  << cpu_sec  << "s "
                  << "real time: " << real_sec << "s " << flush; 
            // memory report
            //system("egrep -r '^Vm(Peak|Size|RSS|Data|Stk|Exe|Lib)' /proc/$PPID/status |sed 's/^Vm//; s/ kB/k/; s/  *//'|tr '	\n' ' '");
                // amount of unrequested memory  -   CommitLimit - Committed_AS
            cout << endl;
        };

                double
        operator() (){ 
            struct rusage  before_ru=ru; 
            getrusage(RUSAGE_SELF, &ru);
            return cpu_s(ru) - cpu_s(before_ru); 
        }

                void
        print(string msg="") {
            if (msg=="") 
                cout << setw(13) << "timer: ";
            else {
                cout <<"          ⌛ " << msg << ":  "; 
            };
            cout  << (*this)() << "s " << endl; 
        };

        friend ostream& operator<< (ostream& os, Timer& t);
 };

ostream& operator<< (ostream& os, Timer& t) {
    os << setprecision(5) << " " << t() << "s ";
    return os;
 }


        #include <stdlib.h>
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

    if (!columns) 
        return;

    if ( var==first)
        cout << msg; 

    int div=(last-first)/width;
    if ( (var-first) % (div+1) == 0 )
        cout << "." << flush;

    if ( var == last )
        cout << endl;
 }

 ///////////////////////////////////////////////////////////////////////////////////

	// TODO replace lexica_cast with boost::format  
    #define STR(x)              (string(" " #x "=")+lexical_cast<string>(x))
    #define PR(x)               cerr << " " #x " = " << (x) << "  "<< flush;

    #define PR1(x1)             cerr << "-- "; PR(x1)                            ; cerr <<"   --- "<<__PRETTY_FUNCTION__<< ":" <<__LINE__<<"\n"<<flush; 
    #define PR2(x1,x2)          cerr << "-- "; PR(x1) PR(x2)                     ; cerr <<"   --- "<<__PRETTY_FUNCTION__<< ":" <<__LINE__<<"\n"<<flush; 
    #define PR3(x1,x2,x3)       cerr << "-- "; PR(x1) PR(x2) PR(x3)              ; cerr <<"   --- "<<__PRETTY_FUNCTION__<< ":" <<__LINE__<<"\n"<<flush; 
    #define PR4(x1,x2,x3,x4)    cerr << "-- "; PR(x1) PR(x2) PR(x3) PR(x4)       ; cerr <<"   --- "<<__PRETTY_FUNCTION__<< ":" <<__LINE__<<"\n"<<flush; 
    #define PR5(x1,x2,x3,x4,x5) cerr << "-- "; PR(x1) PR(x2) PR(x3) PR(x4) PR(x5); cerr <<"   --- "<<__PRETTY_FUNCTION__<< ":" <<__LINE__<<"\n"<<flush; 
    #define PR6(x1,x2,x3,x4,x5,x6) cerr << "-- "; PR(x1) PR(x2) PR(x3) PR(x4) PR(x5) PR(x6); cerr <<"   --- "<<__PRETTY_FUNCTION__<< ":" <<__LINE__<<"\n"<<flush; 
    #define PR7(x1,x2,x3,x4,x5,x6,x7) cerr << "-- "; PR(x1) PR(x2) PR(x3) PR(x4) PR(x5) PR(x6) PR(x7); cerr <<"   --- "<<__PRETTY_FUNCTION__<< ":" <<__LINE__<<"\n"<<flush; 

    
///////////////////////////////////////////////////////////////////////////////////// DEBUG MACROS
 #ifdef DEBUG
    #define DBG             ;

    #define dPR(x)               PR(x)

    #define dPR1(x1)             PR1(x1)
    #define dPR2(x1,x2)          PR2(x1,x2)          
    #define dPR3(x1,x2,x3)       PR3(x1,x2,x3)       
    #define dPR4(x1,x2,x3,x4)    PR4(x1,x2,x3,x4)    
    #define dPR5(x1,x2,x3,x4,x5) PR5(x1,x2,x3,x4,x5)
 #else

    #define DBG             if(false) 
    #define dPR(x)               ; 
    #define dPR1(x)              ; 
    #define dPR2(x1,x2)          ; 
    #define dPR3(x1,x2,x3)       ; 
    #define dPR4(x1,x2,x3,x4)    ; 
    #define dPR5(x1,x2,x3,x4,x5) ; 
 #endif


 // copied from malloc.h
 struct mallinfo {
     int arena;    /* non-mmapped space allocated from system */
     int ordblks;  /* number of free chunks */
     int smblks;   /* number of fastbin blocks */
     int hblks;    /* number of mmapped regions */
     int hblkhd;   /* space in mmapped regions */
     int usmblks;  /* maximum total allocated space */
     int fsmblks;  /* space available in freed fastbin blocks */
     int uordblks; /* total allocated space */
     int fordblks; /* total free space */
     int keepcost; /* top-most, releasable (via malloc_trim) space */
 };

    /* Returns a copy of the updated current mallinfo. */
    extern  struct mallinfo mallinfo (void);

 };  // namespace lvv
    #endif // LVVLIB_H

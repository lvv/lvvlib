    #ifndef  LVV_H
    #define  LVV_H

    #include <iostream> 
    #include <iomanip>

	#include <boost/lexical_cast.hpp>
	using boost::lexical_cast; 

	#include <boost/format.hpp>
	using boost::format; 
	#define FMT(f)	std::cout << boost::format(f)
	#define MSG(f)	std::cerr << boost::format(f)
	#define LOG(f)	std::clog << boost::format(f)
	


	#define TABLE2(x)	(x x)
	#define TABLE3(x)	(x x x)
	#define TABLE4(x)	(x x x x)
	#define TABLE5(x)	(x x x x x)
	#define TABLE6(x)	(x x x x x x)
	#define TABLE7(x)	(x x x x x x x)
	#define TABLE8(x)	(x x x x x x x x)
	#define TABLE9(x)	(x x x x x x x x x)
	#define TABLE10(x)	(x x x x x x x x x x)
	#define TABLE11(x)	TABLE(10) (x)
	#define TABLE12(x)	TABLE(10) (x x)
	#define TABLE13(x)	TABLE(10) (x x x)
	#define TABLE14(x)	TABLE(10) (x x x x)
	#define TABLE15(x)	TABLE(10) (x x x x x)
	#define TABLE16(x)	TABLE(10) (x x x x x x)
	#define TABLE17(x)	TABLE(10) (x x x x x x x)
	#define TABLE18(x)	TABLE(10) (x x x x x x x x)
	#define TABLE19(x)	TABLE(10) (x x x x x x x x x)

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
	 	//SPARSE HASH (default)
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

 ///////////////////////////////////////////////////////////////////////////////////
	#define STR(x) REAL_STR(x)                                                                                                                         
	#define REAL_STR(x) #x

	// TODO replace lexica_cast with boost::format  
	
    #define _STR(x)              (string(" " #x "=")+lexical_cast<string>(x))
    #define PR(x)               std::cerr << " " #x " = " << (x) << "  "<< flush;

    #define PR1(x1)             std::cerr << "-- "; PR(x1)                            ; std::cerr <<"   --- "<<__PRETTY_FUNCTION__<< ":" <<__LINE__<<std::endl; 
    #define PR2(x1,x2)          std::cerr << "-- "; PR(x1) PR(x2)                     ; std::cerr <<"   --- "<<__PRETTY_FUNCTION__<< ":" <<__LINE__<<std::endl; 
    #define PR3(x1,x2,x3)       std::cerr << "-- "; PR(x1) PR(x2) PR(x3)              ; std::cerr <<"   --- "<<__PRETTY_FUNCTION__<< ":" <<__LINE__<<std::endl;
    #define PR4(x1,x2,x3,x4)    std::cerr << "-- "; PR(x1) PR(x2) PR(x3) PR(x4)       ; std::cerr <<"   --- "<<__PRETTY_FUNCTION__<< ":" <<__LINE__<<std::endl;
    #define PR5(x1,x2,x3,x4,x5) std::cerr << "-- "; PR(x1) PR(x2) PR(x3) PR(x4) PR(x5); std::cerr <<"   --- "<<__PRETTY_FUNCTION__<< ":" <<__LINE__<<std::endl;
    #define PR6(x1,x2,x3,x4,x5,x6) std::cerr << "-- "; PR(x1) PR(x2) PR(x3) PR(x4) PR(x5) PR(x6); std::cerr <<"   --- "<<__PRETTY_FUNCTION__<< ":" <<__LINE__<<std::endl;
    #define PR7(x1,x2,x3,x4,x5,x6,x7) std::cerr << "-- "; PR(x1) PR(x2) PR(x3) PR(x4) PR(x5) PR(x6) PR(x7); std::cerr <<"   --- "<<__PRETTY_FUNCTION__<< ":" <<__LINE__<<std::endl;
    #define PR8(x1,x2,x3,x4,x5,x6,x7,x8) std::cerr << "-- "; PR(x1) PR(x2) PR(x3) PR(x4) PR(x5) PR(x6) PR(x7) PR(x8); std::cerr <<"   --- "<<__PRETTY_FUNCTION__<< ":" <<__LINE__std::endl;
    #define PR9(x1,x2,x3,x4,x5,x6,x7,x8,x9) std::cerr << "-- "; PR(x1) PR(x2) PR(x3) PR(x4) PR(x5) PR(x6) PR(x7) PR(x8) PR(x9); std::cerr <<"   --- "<<__PRETTY_FUNCTION__<< ":" <<__LINE__std::endl;

    
///////////////////////////////////////////////////////////////////////////////////// MACROS

#define  FOR_ARRAY_I(i,A)   for(int i  = A.ibegin(); i  <  A.iend();  i++)

// from BOOST mailing list.  Not works with breakes
#define XXX_FOR_EACH(a, A) \
	for(typeof(A.begin()) _for_each_i = A.begin(), _for_each_e = A.end();\
	_for_each_i != _for_each_e; ++_for_each_i)\
	if(bool _for_each_continue = false) {}\
	else\
	for(typeof(*A.begin()) a = *_for_each_i; !_for_each_continue; _for_each_continue=true) 


#define SKIP continue


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
    #endif // LVV_H

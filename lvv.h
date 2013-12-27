// General/Misc utilities
// Part of lvvlib - https://github.com/lvv/lvvlib
// Copyright (c) 2000-2013
// Leonid Volnitsky (Leonid@Volnitsky.com)


    #ifndef  LVV_H
    #define  LVV_H

    #include <iostream> 
    #include <iomanip>


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

	#ifdef	GOOGLE_SPARSE
		#include    <google/sparse_hash_map>
		#ifndef     MAP
			//SPARSE HASH (default)
		       #define     MAP    google::sparse_hash_map
		#endif
		#ifndef     SET
			#include    <google/sparse_hash_set>
			#define     SET    google::sparse_hash_set
		#endif
	#endif

	#ifndef     MAP
	       #define     MAP   std::map
	#endif
	
	#ifndef     SET
		#define     SET    std::set
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

// from linux kernel
#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

///////////////////////////////////////////////////////////////////////////////////
 
 	
	#define LVV_STR(x) __LVV_STR__(x)
	#define __LVV_STR__(x) #x

	// TODO reimplement with __VA_ARGS__ 
	//  #define A_(a, ...)   << a  A(__VA_ARGS__)
	//  #define A (...)   cout A_(__VA_ARGS__) ;

	
	#define _STR(x)              (string(" " #x "=")+lexical_cast<string>(x))
	#undef __PRETTY_FUNCTION__

	#ifdef NOPR
		#define PR(x)
		#define PR1(x1)
		#define PR2(x1,x2)
		#define PR3(x1,x2,x3)
		#define PR4(x1,x2,x3,x4)
		#define PR5(x1,x2,x3,x4,x5)
		#define PR6(x1,x2,x3,x4,x5,x6)
		#define PR7(x1,x2,x3,x4,x5,x6,x7)
		#define PR8(x1,x2,x3,x4,x5,x6,x7,x8)
		#define PR9(x1,x2,x3,x4,x5,x6,x7,x8,x9)
	#else
		#define 	PR(x)		std::cerr << " " #x " = " << (x) << "  "<< flush;

		#define PR1(x1)             			std::cerr << "--("<<__LINE__<< ")-- "; PR(x1)                            ;				std::cerr <<std::endl;
		#define PR2(x1,x2)          			std::cerr << "--("<<__LINE__<< ")-- "; PR(x1) PR(x2)                     ;				std::cerr <<std::endl;
		#define PR3(x1,x2,x3)       			std::cerr << "--("<<__LINE__<< ")-- "; PR(x1) PR(x2) PR(x3)              ;				std::cerr <<std::endl;
		#define PR4(x1,x2,x3,x4)    			std::cerr << "--("<<__LINE__<< ")-- "; PR(x1) PR(x2) PR(x3) PR(x4)       ;				std::cerr <<std::endl;
		#define PR5(x1,x2,x3,x4,x5)			std::cerr << "--("<<__LINE__<< ")-- "; PR(x1) PR(x2) PR(x3) PR(x4) PR(x5);				std::cerr <<std::endl;
		#define PR6(x1,x2,x3,x4,x5,x6)			std::cerr << "--("<<__LINE__<< ")-- "; PR(x1) PR(x2) PR(x3) PR(x4) PR(x5) PR(x6);				std::cerr <<std::endl;
		#define PR7(x1,x2,x3,x4,x5,x6,x7)		std::cerr << "--("<<__LINE__<< ")-- "; PR(x1) PR(x2) PR(x3) PR(x4) PR(x5) PR(x6) PR(x7);			std::cerr <<std::endl;
		#define PR8(x1,x2,x3,x4,x5,x6,x7,x8)		std::cerr << "--("<<__LINE__<< ")-- "; PR(x1) PR(x2) PR(x3) PR(x4) PR(x5) PR(x6) PR(x7) PR(x8);		std::cerr <<std::endl;
		#define PR9(x1,x2,x3,x4,x5,x6,x7,x8,x9)		std::cerr << "--("<<__LINE__<< ")-- "; PR(x1) PR(x2) PR(x3) PR(x4) PR(x5) PR(x6) PR(x7) PR(x8) PR(x9);	std::cerr <<std::endl;
	#endif
    
///////////////////////////////////////////////////////////////////////////////////// MACROS

#define SKIP continue


///////////////////////////////////////////////////////////////////////////////////// DEBUG MACROS
 #if !defined(NDEBUG) || defined(DEBUG)
    #define DBG             ;

    #define dPR(x)               PR(x)
    #define dPR1(x1)             PR1(x1)
    #define dPR2(x1,x2)          PR2(x1,x2)          
    #define dPR3(x1,x2,x3)       PR3(x1,x2,x3)       
    #define dPR4(x1,x2,x3,x4)    PR4(x1,x2,x3,x4)    
    #define dPR5(x1,x2,x3,x4,x5) PR5(x1,x2,x3,x4,x5)
    #define dPR6(x1,x2,x3,x4,x5,x6) PR6(x1,x2,x3,x4,x5,x6)
 #else

    #define DBG             if(false) 
    #define dPR(x)               ; 
    #define dPR1(x)              ; 
    #define dPR2(x1,x2)          ; 
    #define dPR3(x1,x2,x3)       ; 
    #define dPR4(x1,x2,x3,x4)    ; 
    #define dPR5(x1,x2,x3,x4,x5) ; 
    #define dPR6(x1,x2,x3,x4,x5,x6) ; 
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

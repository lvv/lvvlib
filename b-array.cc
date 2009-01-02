	
	///////////////////   CONFIG
	//#define		I16
	#define		F32
	#define		REPEAT		7


	#ifndef INCLUDE
		//#define 	INCLUDE		"b-lower_bound.h"
		//#define 	INCLUDE		"b-cmp.h"
		#define 	INCLUDE		"b-sum.h"
	#endif
		
	#ifdef	F32
		#define		TYPE		float
		//#define		CANUSE_OMP
		#define		CANUSE_SSE
		#define		CANUSE_SSE2
		//#define		CANUSE_SSE3
		//#define		CANUSE_SSE4
		//		_mm_minpos_epu16  

			#define		SSE_SIZE	4
			#define		MM_ADD_OP 	_mm_add_ps
			#define		MM_CMP_OP 	_mm_max_ps
			#define		CMP_OP 		>
			#define		REG_T		__m128
			#define		MK_REG		mk_m128

				#define		DO_PLAIN
				#define		DO_SIMD
				#define		DO_OMP
	#endif

	#ifdef	I16
		#define		TYPE		int16_t
		#define		CANUSE_SSE
		#define		CANUSE_SSE2
		#define		CANUSE_SSE3
		#define		CANUSE_OMP

			#define		SSE_SIZE	8
			#define		MM_CMP_OP 		_mm_max_epi16
			#define		CMP_OP 		>
			#define		REG_T		__m128i
			#define		MK_REG		mk_m128i
				#define		DO_PLAIN
				#define		DO_SIMD
				//#define		DO_OMP
	#endif

	#ifndef TYPE
		#error "type  (F32/I16/...) not defined"
	#endif


	#define dID 1

	///////////////////////////////////
	#include <iostream>
		using  namespace std;

	#include <lvv/array.h>
		using lvv::array;
		using lvv::sse;
		using lvv::sse2;
		using lvv::plain;
		using lvv::mk_array;

	#include <lvv/timer.h>
		using lvv::Timer;

	#include <lvv/sse.h>
	#include <lvv/math.h>

	#include <algorithm>


int main(int argc, char *argv[]) {

	///////////////////////////////////  ID
	cout << ID   //<< "    << " 
		#ifdef CANUSE_MMX
			<< " mmx "
		#endif
		#ifdef CANUSE_SSE
			<< " sse "
		#endif
		#ifdef CANUSE_SSE2
			<< " sse2 "
		#endif
		#ifdef CANUSE_OMP
			<< " omp "
		#endif
	<< ">>" << endl;

	///////////////////////////////////


	Timer	t(true);
	float sec, ticks;

	cout <<  "\nValue\tSeconds\t\tTick/Cycle ...   Min-Tick/Cycle \t Method\n" << setprecision(4);

	array<float,REPEAT> tick;

	#define PRINT(NAME,EXPR)	\
		tick[r] = ticks = t.interval_ticks() / float (N); sec = t.interval_cpu();		\
		if (r==0)		cout	<< setprecision(6) << setw(11) << (EXPR) << "  " << setprecision(3) << setw(8) << sec <<"\t\t" << ticks;\
		else			cout	<< "\t" <<  ticks; \
		if (r==(REPEAT-1))	cout	<< "\t\t" <<  tick.min() << "  \t" << NAME << endl;\
		t.interval_ticks();

	#include INCLUDE
	cerr << endl;  
	return 0;
 }


	///////////////////   CONFIG
	//#define		I16
	#define		F32

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

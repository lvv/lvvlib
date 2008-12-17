
cout << "*** COMPARE  type:"  << typeid(TYPE).name() << endl;


for (int r=0; r<REPEAT; r++) { TYPE m = A.max<plain>();	PRINT("max<plain>:	", m ); }
for (int r=0; r<REPEAT; r++) { TYPE m = A.max();  	PRINT("max():		", m ); }
for (int r=0; r<REPEAT; r++) { TYPE m = A.max<sse2>();  	PRINT("max<sse2>():		", m ); }
for (int r=0; r<REPEAT; r++) { TYPE m = A.max_impl(sse2(),int16_t());  	PRINT("max_impl(sse2(),T()):		", m ); }

 for (int r=0; r<REPEAT; r++) {
	TYPE max=A[0];
	for (size_t i=1; i<N-8; i+=8) {
		TYPE m0 = (A[i+0] CMP_OP A[i+1] ? A[i+0] : A[i+1]); 
		TYPE m2 = (A[i+2] CMP_OP A[i+3] ? A[i+2] : A[i+3]); 
		TYPE m4 = (A[i+4] CMP_OP A[i+5] ? A[i+4] : A[i+5]); 
		TYPE m6 = (A[i+6] CMP_OP A[i+7] ? A[i+6] : A[i+7]); 
		TYPE m02 = (m0 CMP_OP m2 ? m0 : m2); 
		TYPE m46 = (m4 CMP_OP m6 ? m4 : m6); 
		TYPE m   = (m02 CMP_OP m46 ? m02 : m46);

		if (m CMP_OP max) max = m;
	}
PRINT("?+ooo8:		",max);
 }

 for (size_t r=0; r<REPEAT; r++) {
	TYPE max=A[0];
	for (size_t i=1; i<N-7; i+=7) {
		TYPE m0 = (A[i+0] CMP_OP A[i+1] ? A[i+0] : A[i+1]); 
		TYPE m2 = (A[i+2] CMP_OP A[i+3] ? A[i+2] : A[i+3]); 
		TYPE m4 = (A[i+4] CMP_OP A[i+5] ? A[i+4] : A[i+5]); 
		TYPE m6 = A[i+6] CMP_OP max  ? A[i+6] : max; 
		TYPE m02 = (m0 CMP_OP m2 ? m0 : m2); 
		TYPE m46 = m4  CMP_OP m6 ? m4 : m6; 
		     max = m02 CMP_OP m46 ? m02 : m46;
	}
PRINT("?+ooo7+reod:	",max);
 }

 for (size_t r=0; r<REPEAT; r++) {
	TYPE max=A[0];
	for (size_t i=1; i<N-7; i+=7) {
		TYPE m0 = (A[i+0] CMP_OP A[i+1] ? A[i+0] : A[i+1]); 
		TYPE m2 = (A[i+2] CMP_OP A[i+3] ? A[i+2] : A[i+3]); 
		TYPE m4 = (A[i+4] CMP_OP A[i+5] ? A[i+4] : A[i+5]); 
		TYPE m6 = (__builtin_expect(A[i+6] CMP_OP max, 0)  ? A[i+6] : max); 
		TYPE m02 = (m0 CMP_OP m2 ? m0 : m2); 
		TYPE m46 = (__builtin_expect(m4  CMP_OP m6,  0) ? m4 : m6); 
		     max = (__builtin_expect(m02 CMP_OP m46, 0) ? m02 : m46);
	}
PRINT("?+ooo7+ex+reod:	",max);
}


 for (size_t r=0; r<REPEAT; r++) {
	TYPE max=0;
	for (size_t i=0; i<N-7; i+=7) {
		TYPE m0 = (A[i+0] CMP_OP A[i+1] ? A[i+0] : A[i+1]); 
		TYPE m2 = (A[i+2] CMP_OP A[i+3] ? A[i+2] : A[i+3]); 
		TYPE m4 = (A[i+4] CMP_OP A[i+5] ? A[i+4] : A[i+5]); 
		TYPE m6 = (__builtin_expect(A[i+6] CMP_OP max, 0)  ? A[i+6] : max); 
		TYPE m02 = (m0 CMP_OP m2 ? m0 : m2); 
		TYPE m46 = (__builtin_expect(m4 CMP_OP m6, 0  ) ? m4 : m6); 
		      max = (__builtin_expect(m02 CMP_OP m46, 0) ? m02 : m46);
	}
PRINT("?+ooo7+ex+reod:	",max);			// race, incorrect result
}

 for (size_t r=0; r<REPEAT; r++) {
	TYPE max=0;
	TYPE m;
	for (size_t i=0; i<N; i+=4) {

		if (A[i] CMP_OP A[i+1]) {
			if (A[i+2] CMP_OP A[i+3]) {
				if (A[i] CMP_OP A[i+2])
					m = A[i];
				else
					m = A[i+2];
			} else {
				if (A[i] CMP_OP A[i+3])
					m = A[i];
				else
					m = A[i+3];
			}
		} else {
			if (A[i+2] CMP_OP A[i+3]) {
				if (A[i+1] CMP_OP A[i+2])
					m = A[i+1];
				else
					m = A[i+2];
			} else {
				if (A[i+1] CMP_OP A[i+3])
					m = A[i+1];
				else
					m = A[i+3];
			}
		}
		if (m CMP_OP max) max = m;
	}
PRINT("IF+ooo4:	",max);
}

 for (size_t r=0; r<REPEAT; r++) {
	TYPE m1=0, m2=0;
	for (size_t i=0; i<N/2; i++)    if (A[i] CMP_OP m1) m1 = A[i];
	for (size_t i=N/2; i<N; i++)    if (A[i] CMP_OP m2) m2 = A[i];
	if (m2 CMP_OP m1)    m1 = m2;
PRINT("IF-split-loop:		",m1);
}

for (size_t r=0; r<REPEAT; r++) { TYPE max=0; for (size_t i=0; i<N; i++) if (__builtin_expect(A[i] CMP_OP max, 0)) max = A[i];	PRINT("IF+ex:		",max); }


for (size_t r=0; r<REPEAT; r++) { TYPE max=0; for (long i=N-1; i >= 0; i--) if (A[i] CMP_OP max) max = A[i];	PRINT("IF--:		",max); }

for (size_t r=0; r<REPEAT; r++) { TYPE max=0; for (array_t::iterator it=A.begin(); it != A.end(); it++) if (*it CMP_OP max) max = *it;	PRINT("IF+iter:		",max); }

for (size_t r=0; r<REPEAT; r++) { TYPE max=0; for (size_t i=0; i<N; i++) max = max CMP_OP A[i]? max : A[i];	PRINT("?op:		",max); }

for (size_t r=0; r<REPEAT; r++) { TYPE max=0; for (size_t i=0; i<N; i++) max = std::max(max,A[i]);	PRINT("STL::MAX:	",max); }

for (size_t r=0; r<REPEAT; r++) { TYPE max = *std::max_element (A.begin(), A.end()); 		PRINT("STL::MAX_ELEMENT:",max); }

//for (size_t r=0; r<REPEAT; r++) { TYPE max = *__gnu_parallel::max_element (A.begin(), A.end()); 		PRINT("STL::MAX_ELEMENT __gnu_parallel",max); }

for (size_t r=0; r<REPEAT; r++) { TYPE max=A[0]; for (size_t i=1; i<N; i++) { if (A[i] CMP_OP max) max = A[i]; } PRINT("IF++:		",max); }

for (size_t r=0; r<REPEAT; r++) { TYPE max=A[0]; for (TYPE* p = &A[0]; p != &A[N]; p++) { if (*p CMP_OP max) max = *p; } PRINT("p++:		",max); }

 for (size_t r=0; r<REPEAT; r++) {
	TYPE* p = &A[0]; TYPE max=*p; 
	do {
		if (*p CMP_OP max) max = *p;
		p++;
	} while (p != &A[N]);

PRINT("while p++:	",max);
 }

 for (size_t r=0; r<REPEAT; r++) {
	TYPE* p = &A[0]; TYPE max=*p; 
	do {
		if (__builtin_expect(*p CMP_OP max, 0)) max = *p;
		p++;
	} while (p != &A[N]);

PRINT("while p++ + ex:	",max);
 }

 for (size_t r=0; r<REPEAT; r++) {
	TYPE max=A[0];
	for (size_t i=1; i<N-4; i+=4) {
		if (A[i] CMP_OP max) max = A[i];
		if (A[i+1] CMP_OP max) max = A[i+1];
		if (A[i+2] CMP_OP max) max = A[i+2];
		if (A[i+3] CMP_OP max) max = A[i+4];
	}
PRINT("IF+unr4:		",max);
 }

 for (size_t r=0; r<REPEAT; r++) {
	TYPE max=A[0];
	for (size_t i=1; i<N-4; i+=4) {
		__builtin_prefetch((void*)&A[i+512],0,0);	
		if (A[i] CMP_OP max) max = A[i];
		if (A[i+1] CMP_OP max) max = A[i+1];
		if (A[i+2] CMP_OP max) max = A[i+2];
		if (A[i+3] CMP_OP max) max = A[i+4];
	}
PRINT("IF+unr4+pf512:		",max);
 }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   OMP
#ifdef CANUSE_OMP

 for (size_t r=0; r<REPEAT; r++) {
	TYPE max=A[0];
	#pragma omp parallel for shared(max)
	for (long i=1; i<N; i+=8) {
		TYPE m0 = (A[i+0] CMP_OP A[i+1] ? A[i+0] : A[i+1]); 
		TYPE m2 = (A[i+2] CMP_OP A[i+3] ? A[i+2] : A[i+3]); 
		TYPE m4 = (A[i+4] CMP_OP A[i+5] ? A[i+4] : A[i+5]); 
		TYPE m6 = (A[i+6] CMP_OP A[i+7] ? A[i+6] : A[i+7]); 
		TYPE m02 = (m0 CMP_OP m2 ? m0 : m2); 
		TYPE m46 = (m4 CMP_OP m6 ? m4 : m6); 
		TYPE m   = (m02 CMP_OP m46 ? m02 : m46);
		if (__builtin_expect(m CMP_OP max,1)) max = m;
	}
PRINT("?+ooo8+omp+ex:	",max);
}

 for (size_t r=0; r<REPEAT; r++) {
	TYPE max=A[0];
	#pragma omp parallel for shared(max)
	for (long i=1; i<N; i+=8) {
		TYPE m0 = (A[i+0] CMP_OP A[i+1] ? A[i+0] : A[i+1]); 
		TYPE m2 = (A[i+2] CMP_OP A[i+3] ? A[i+2] : A[i+3]); 
		TYPE m4 = (A[i+4] CMP_OP A[i+5] ? A[i+4] : A[i+5]); 
		TYPE m6 = (A[i+6] CMP_OP A[i+7] ? A[i+6] : A[i+7]); 
		TYPE m02 = (m0 CMP_OP m2 ? m0 : m2); 
		TYPE m46 = (m4 CMP_OP m6 ? m4 : m6); 
		TYPE m   = (m02 CMP_OP m46 ? m02 : m46);
		if (m CMP_OP max) max = m;
	}
PRINT("?+ooo8+omp:	",max);
}


 for (size_t r=0; r<REPEAT; r++) {
	TYPE max=0;
	#pragma omp parallel for shared(max)
	for (long i=0; i<N-7; i+=7) {
		TYPE m0 = (A[i+0] CMP_OP A[i+1] ? A[i+0] : A[i+1]); 
		TYPE m2 = (A[i+2] CMP_OP A[i+3] ? A[i+2] : A[i+3]); 
		TYPE m4 = (A[i+4] CMP_OP A[i+5] ? A[i+4] : A[i+5]); 
		TYPE m6 = (__builtin_expect(A[i+6] CMP_OP max, 0)  ? A[i+6] : max); 
		TYPE m02 = (m0 CMP_OP m2 ? m0 : m2); 
		TYPE m46 = (__builtin_expect(m4 CMP_OP m6, 0  ) ? m4 : m6); 

		if (__builtin_expect(m02 CMP_OP m46, 0))	max = m02;
		else						max = m46;
	      //max = (__builtin_expect(m02 CMP_OP m46, 0) ? m02 : m46); 	// race, incorrect result
	}
PRINT("?+ooo7+omp+ex+reod:	",max);		
}

 for (size_t r=0; r<REPEAT; r++) {
	TYPE max=0;
	#pragma omp parallel for shared(max) 
	for (long i=0; i<N; i++) if (A[i] CMP_OP max) max = A[i];

PRINT("IF+omp:		",max);	 	// race, incorrect result
}

 #endif // CANUSE_OMP


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    SIMD

for (int r=0; r<REPEAT; r++) { TYPE m = A.max();  	PRINT("max():		", m ); }

//for (int r=0; r<REPEAT; r++) { TYPE m = A.max<sse2>();  	PRINT("max<sse2>():		", m ); }

 for (size_t r=0; r<REPEAT; r++) { 

	REG_T m1 = MK_REG(A[0]);
	REG_T m2 = MK_REG(A[SSE_SIZE]);
	for (size_t i=2*SSE_SIZE; i<N; i+=2*SSE_SIZE) {
		  m1 = MM_CMP_OP(m1, MK_REG(A[i]) );
		  m2 = MM_CMP_OP(m2, MK_REG(A[i+SSE_SIZE]) );
	}
	m1 = MM_CMP_OP(m1, m2);
PRINT("SSE+unroll2+ooo2:", (mk_array<TYPE,SSE_SIZE,0>(m1).max()) );
 }

#ifdef  DO_SIMD
 for (size_t r=0; r<REPEAT; r++) {
	REG_T m = MK_REG(A[0]);
	REG_T m0, m4, m8, m12; //, m16, m20, m24, m28;
	//m0 =  m4 =  m8 = m12 = m16 = m20 = m24 = m28 = m;
	m0 =  m4 =  m8 = m12 = m;
	for (size_t i=4*SSE_SIZE; i<N; i+=4*SSE_SIZE) {
		  m0 = MM_CMP_OP(m0, MK_REG(A[i]));
		  m4 = MM_CMP_OP(m4, MK_REG(A[i+SSE_SIZE]));
		  m8 = MM_CMP_OP(m8, MK_REG(A[i+2*SSE_SIZE]));
		  m12 = MM_CMP_OP(m12, MK_REG(A[i+3*SSE_SIZE]));
		  //m16 = MM_CMP_OP(m16, MK_REG(A[i+16]));
		  //m20 = MM_CMP_OP(m20, MK_REG(A[i+20]));
		  //m24 = MM_CMP_OP(m24, MK_REG(A[i+24]));
		  //m28 = MM_CMP_OP(m28, MK_REG(A[i+28]));

	}
	  m0 = MM_CMP_OP(m0, m4);
	  m8 = MM_CMP_OP(m8, m12);
	  //m16 = MM_CMP_OP(m16, m20);
	  //m24 = MM_CMP_OP(m24, m28);

	  //m0 = MM_CMP_OP(m0, m4);
	  //m8 = MM_CMP_OP(m8, m12);
	  //m16 = MM_CMP_OP(m16, m20);
	  //m24 = MM_CMP_OP(m24, m28);

	  m0 = MM_CMP_OP(m0, m8);
	  //m16 = MM_CMP_OP(m16, m24);

	  //m = MM_CMP_OP(m0, m16);
	  m = m0;
PRINT("SSE+unroll4+ooo4:", (mk_array<TYPE,SSE_SIZE,0>(m).max()) );
 }

 for (size_t r=0; r<REPEAT; r++) {
	REG_T m = MK_REG(A[0]);
	for (size_t i=SSE_SIZE; i<N-8*SSE_SIZE; i+=8*SSE_SIZE) {
		  m = MM_CMP_OP(m, MK_REG(A[i]));
		  m = MM_CMP_OP(m, MK_REG(A[i+SSE_SIZE]));
		  m = MM_CMP_OP(m, MK_REG(A[i+2*SSE_SIZE]));
		  m = MM_CMP_OP(m, MK_REG(A[i+3*SSE_SIZE]));
		  m = MM_CMP_OP(m, MK_REG(A[i+4*SSE_SIZE]));
		  m = MM_CMP_OP(m, MK_REG(A[i+5*SSE_SIZE]));
		  m = MM_CMP_OP(m, MK_REG(A[i+6*SSE_SIZE]));
		  m = MM_CMP_OP(m, MK_REG(A[i+7*SSE_SIZE]));
	}
PRINT("SSE+unroll8:	", (mk_array<TYPE,SSE_SIZE,0>(m).max()) );
 }

 for (size_t r=0; r<REPEAT; r++) {
	REG_T m = MK_REG(A[0]);
	for (size_t i=SSE_SIZE; i<N-8*SSE_SIZE; i+=8*SSE_SIZE) {
		  m = MM_CMP_OP(m, MK_REG(A[i]));
		  m = MM_CMP_OP(m, MK_REG(A[i+1*SSE_SIZE]));
		  m = MM_CMP_OP(m, MK_REG(A[i+2*SSE_SIZE]));
		  m = MM_CMP_OP(m, MK_REG(A[i+3*SSE_SIZE]));
		  m = MM_CMP_OP(m, MK_REG(A[i+4*SSE_SIZE]));
		  m = MM_CMP_OP(m, MK_REG(A[i+5*SSE_SIZE]));
		  m = MM_CMP_OP(m, MK_REG(A[i+6*SSE_SIZE]));
		  m = MM_CMP_OP(m, MK_REG(A[i+7*SSE_SIZE]));
		 __builtin_prefetch((void*)&A[i+500],0,0);	
	}
PRINT("SSE+unroll8+pf500:	", (mk_array<TYPE,SSE_SIZE,0>(m).max()) );
 }

 for (size_t r=0; r<REPEAT; r++) {
	REG_T m = MK_REG(A[0]);
	#pragma omp parallel for shared(m)
	for (long i=SSE_SIZE; i<N; i+=SSE_SIZE) {	m = MM_CMP_OP(m, MK_REG(A[i])); }
PRINT("SSE+omp:	", (mk_array<TYPE,SSE_SIZE,0>(m).max()));
 }

 for (size_t r=0; r<REPEAT; r++) { //////////// 
	REG_T m = MK_REG(A[0]);
	for (size_t i=SSE_SIZE; i<N; i+=SSE_SIZE) { __builtin_prefetch((void*)&A[i+1024+512],0,0);	m = MM_CMP_OP(m, MK_REG(A[i]) );	}
PRINT("SSE+pf1530:		", (mk_array<TYPE,SSE_SIZE,0>(m).max()) );
 }

 for (size_t r=0; r<REPEAT; r++) { //////////// 
	REG_T m = MK_REG(A[0]);
	for (size_t i=SSE_SIZE; i<N; i+=SSE_SIZE) { __builtin_prefetch((void*)&A[i+1024+256],0,0);	m = MM_CMP_OP(m, MK_REG(A[i]) );	}
PRINT("SSE+pf1260:		", (mk_array<TYPE,SSE_SIZE,0>(m).max()) );
 }

 for (size_t r=0; r<REPEAT; r++) { //////////// 
	REG_T m = MK_REG(A[0]);
	for (size_t i=SSE_SIZE; i<N; i+=SSE_SIZE) { __builtin_prefetch((void*)&A[i+1024+128],0,0);	m = MM_CMP_OP(m, MK_REG(A[i]) );	}
PRINT("SSE+pf1130:		", (mk_array<TYPE,SSE_SIZE,0>(m).max()) );
 }

 for (size_t r=0; r<REPEAT; r++) { //////////// 
	REG_T m = MK_REG(A[0]);
	for (size_t i=SSE_SIZE; i<N; i+=SSE_SIZE) { __builtin_prefetch((void*)&A[i+1024],0,0);	m = MM_CMP_OP(m, MK_REG(A[i]) );	}
PRINT("SSE+pf1024:		", (mk_array<TYPE,SSE_SIZE,0>(m).max()) );
 }

 for (size_t r=0; r<REPEAT; r++) {
	REG_T m = MK_REG(A[0]);
	for (size_t i=SSE_SIZE; i<N; i+=SSE_SIZE) { __builtin_prefetch((void*)&A[i+700],0,0);	m = MM_CMP_OP(m, MK_REG(A[i]) );	}
PRINT("SSE+pf700:		", (mk_array<TYPE,SSE_SIZE,0>(m).max()) );
 }


 for (size_t r=0; r<REPEAT; r++) {
	REG_T m = MK_REG(A[0]);
	for (size_t i=SSE_SIZE; i<N; i+=SSE_SIZE) { __builtin_prefetch((void*)&A[i+300],0,0);	m = MM_CMP_OP(m, MK_REG(A[i]) );	}
PRINT("SSE+pf300:		", (mk_array<TYPE,SSE_SIZE,0>(m).max()) );
 }

 for (size_t r=0; r<REPEAT; r++) {
	REG_T m = MK_REG(A[0]);
	for (size_t i=SSE_SIZE; i<N; i+=SSE_SIZE) { __builtin_prefetch((void*)&A[i+200],0,0);	m = MM_CMP_OP(m, MK_REG(A[i]) );	}
PRINT("SSE+pf200:		", (mk_array<TYPE,SSE_SIZE,0>(m).max()) );
 }

 for (size_t r=0; r<REPEAT; r++) {
	REG_T m = MK_REG(A[0]);
	for (size_t i=SSE_SIZE; i<N; i+=SSE_SIZE) { m = MM_CMP_OP(m, MK_REG(A[i]) );	}
PRINT("SSE:		", (mk_array<TYPE,SSE_SIZE,0>(m).max()) );
 }

 for (size_t r=0; r<REPEAT; r++) {
	REG_T m = MK_REG(A[0]);
	for (size_t i=SSE_SIZE; i<N-SSE_SIZE; i+=SSE_SIZE) { __builtin_prefetch((void*)&A[i+500],0,0);	m = MM_CMP_OP(m, MK_REG(A[i]) );	}
PRINT("SSE+pf500:		", (mk_array<TYPE,SSE_SIZE,0>(m).max<plain>()) );
	//cout << mk_array<TYPE,SSE_SIZE,0>(m);
 }

 for (size_t r=0; r<REPEAT; r++) { //////////// 
	REG_T m = MK_REG(A[0]);
	for (size_t i=SSE_SIZE; i<N; i+=SSE_SIZE) { __builtin_prefetch((void*)&A[i+1024+512+128],0,0);	m = MM_CMP_OP(m, MK_REG(A[i]) );	}
PRINT("SSE+pf1800:		", (mk_array<TYPE,SSE_SIZE,0>(m).max()) );
 }

 for (size_t r=0; r<REPEAT; r++) { //////////// 
	REG_T m = MK_REG(A[0]);
	for (size_t i=SSE_SIZE; i<N; i+=SSE_SIZE) { __builtin_prefetch((void*)&A[i+2048],0,0);	m = MM_CMP_OP(m, MK_REG(A[i]) );	}
PRINT("SSE+pf2048:		", (mk_array<TYPE,SSE_SIZE,0>(m).max()) );
 }

 for (size_t r=0; r<REPEAT; r++) {

	REG_T m1 = MK_REG(A[0]);
	REG_T m2 = MK_REG(A[SSE_SIZE]);
	for (size_t i = 2*SSE_SIZE; i<N-2*SSE_SIZE; i+=2*SSE_SIZE) {
		  m1 = MM_CMP_OP(m1, MK_REG(A[i]) );
		  m2 = MM_CMP_OP(m2, MK_REG(A[i+SSE_SIZE]) );
		 __builtin_prefetch((void*)&A[i+512],0,0);	
	}
	m1 = MM_CMP_OP(m1, m2);

PRINT("SSE+unroll2+ooo2+pf500:", (mk_array<TYPE,SSE_SIZE,0>(m1).max<plain>()) );
 }

 for (size_t r=0; r<REPEAT; r++) {

	REG_T m1 = MK_REG(A[0]);
	REG_T m2 = MK_REG(A[SSE_SIZE]);
	REG_T m3 = MK_REG(A[2*SSE_SIZE]);

	for (size_t i = 3*SSE_SIZE; i<N-3*SSE_SIZE; i+=3*SSE_SIZE) {
		  m1 = MM_CMP_OP(m1, MK_REG(A[i]) );
		  m2 = MM_CMP_OP(m2, MK_REG(A[i+SSE_SIZE]) );
		  m3 = MM_CMP_OP(m3, MK_REG(A[i+SSE_SIZE]) );
		 __builtin_prefetch((void*)&A[i+256],0,0);	
	}
	m1 = MM_CMP_OP(m1, m2);
	m1 = MM_CMP_OP(m1, m3);

PRINT("SSE+unroll3+ooo3+pf256:", (mk_array<TYPE,SSE_SIZE,0>(m1).max<plain>()) );
 }

 for (size_t r=0; r<REPEAT; r++) {

	REG_T m1 = MK_REG(A[0]);
	REG_T m2 = MK_REG(A[SSE_SIZE]);
	REG_T m3 = MK_REG(A[2*SSE_SIZE]);

	for (size_t i = 3*SSE_SIZE; i<N-3*SSE_SIZE; i+=3*SSE_SIZE) {
		  m1 = MM_CMP_OP(m1, MK_REG(A[i]) );
		  m2 = MM_CMP_OP(m2, MK_REG(A[i+SSE_SIZE]) );
		  m3 = MM_CMP_OP(m3, MK_REG(A[i+SSE_SIZE]) );
		 __builtin_prefetch((void*)&A[i+512],0,0);	
	}
	m1 = MM_CMP_OP(m1, m2);
	m1 = MM_CMP_OP(m1, m3);

PRINT("SSE+unroll3+ooo3+pf500:", (mk_array<TYPE,SSE_SIZE,0>(m1).max<plain>()) );
 }


 for (size_t r=0; r<REPEAT; r++) {

	REG_T m1 = MK_REG(A[0]);
	REG_T m2 = MK_REG(A[SSE_SIZE]);
	for (size_t i = 2*SSE_SIZE; i<N-2*SSE_SIZE; i+=2*SSE_SIZE) {
		  m1 = MM_CMP_OP(m1, MK_REG(A[i]) );
		  m2 = MM_CMP_OP(m2, MK_REG(A[i+SSE_SIZE]) );
		 __builtin_prefetch((void*)&A[i+1024],0,0);	
	}
	m1 = MM_CMP_OP(m1, m2);

PRINT("SSE+unroll2+ooo2+pf1000:", (mk_array<TYPE,SSE_SIZE,0>(m1).max<plain>()) );
 }

 for (size_t r=0; r<REPEAT; r++) {

	REG_T m1 = MK_REG(A[0]);
	REG_T m2 = MK_REG(A[SSE_SIZE]);
	REG_T m3 = MK_REG(A[2*SSE_SIZE]);

	for (size_t i = 3*SSE_SIZE; i<N-3*SSE_SIZE; i+=3*SSE_SIZE) {
		  m1 = MM_CMP_OP(m1, MK_REG(A[i]) );
		  m2 = MM_CMP_OP(m2, MK_REG(A[i+SSE_SIZE]) );
		  m3 = MM_CMP_OP(m3, MK_REG(A[i+SSE_SIZE]) );
		 __builtin_prefetch((void*)&A[i+1524],0,0);	
	}
	m1 = MM_CMP_OP(m1, m2);
	m1 = MM_CMP_OP(m1, m3);

PRINT("SSE+unroll3+ooo3+pf1524:", (mk_array<TYPE,SSE_SIZE,0>(m1).max<plain>()) );
 }

 for (size_t r=0; r<REPEAT; r++) {

	REG_T m1 = MK_REG(A[0]);
	REG_T m2 = MK_REG(A[SSE_SIZE]);
	REG_T m3 = MK_REG(A[2*SSE_SIZE]);

	for (size_t i = 3*SSE_SIZE; i<N-3*SSE_SIZE; i+=3*SSE_SIZE) {
		  m1 = MM_CMP_OP(m1, MK_REG(A[i]) );
		  m2 = MM_CMP_OP(m2, MK_REG(A[i+SSE_SIZE]) );
		  m3 = MM_CMP_OP(m3, MK_REG(A[i+SSE_SIZE]) );
		 __builtin_prefetch((void*)&A[i+1024],0,0);	
	}
	m1 = MM_CMP_OP(m1, m2);
	m1 = MM_CMP_OP(m1, m3);

PRINT("SSE+unroll3+ooo3+pf1024:", (mk_array<TYPE,SSE_SIZE,0>(m1).max<plain>()) );
 }

 for (size_t r=0; r<REPEAT; r++) {
	REG_T m = MK_REG(A[0]);
	REG_T m0, m4, m8, m12;
	m0 =  m4 =  m8 = m12 = m;
	for (size_t i=4*SSE_SIZE; i<N; i+=4*SSE_SIZE) {
		  m0 = MM_CMP_OP(m0, MK_REG(A[i]));
		  m4 = MM_CMP_OP(m4, MK_REG(A[i+SSE_SIZE]));
		  m8 = MM_CMP_OP(m8, MK_REG(A[i+2*SSE_SIZE]));
		  m12 = MM_CMP_OP(m12, MK_REG(A[i+3*SSE_SIZE]));
		 __builtin_prefetch((void*)&A[i+1524],0,0);	

	}
	  m0 = MM_CMP_OP(m0, m4);
	  m8 = MM_CMP_OP(m8, m12);
	  m0 = MM_CMP_OP(m0, m8);
	  m = m0;
PRINT("SSE+unroll4+ooo4+pf1524:", (mk_array<TYPE,SSE_SIZE,0>(m).max()) );
 }

 for (size_t r=0; r<REPEAT; r++) {
	REG_T m = MK_REG(A[0]);
	REG_T m0, m4, m8, m12;
	m0 =  m4 =  m8 = m12 = m;
	for (size_t i=4*SSE_SIZE; i<N; i+=4*SSE_SIZE) {
		  m0 = MM_CMP_OP(m0, MK_REG(A[i]));
		  m4 = MM_CMP_OP(m4, MK_REG(A[i+SSE_SIZE]));
		  m8 = MM_CMP_OP(m8, MK_REG(A[i+2*SSE_SIZE]));
		  m12 = MM_CMP_OP(m12, MK_REG(A[i+3*SSE_SIZE]));
		 __builtin_prefetch((void*)&A[i+1024],0,0);	

	}
	  m0 = MM_CMP_OP(m0, m4);
	  m8 = MM_CMP_OP(m8, m12);
	  m0 = MM_CMP_OP(m0, m8);
	  m = m0;
PRINT("SSE+unroll4+ooo4+pf1024:", (mk_array<TYPE,SSE_SIZE,0>(m).max()) );
 }

//for (size_t r=0; r<REPEAT; r++) { PRINT("max<sse>:", A.max<sse>() ); }

 #endif // CANUSE_SSE


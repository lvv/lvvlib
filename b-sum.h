
#ifdef DO_OO
 for(int r=0; r<REPEAT; r++) { ////////////  OUT-OF-ORDER-LOOP-F2+4
	float fsum1=0;
	float fsum2=0;
	for (int i=0; i<N; i+=8) {
		fsum1 += A[i] + A[i+1] + A[i+2] + A[i+3];
		fsum2 += A[i+4]+ A[i+5]+ A[i+6] + A[i+7];
	}
PRINT("O-ORDER ooo2+4(para):",fsum1+fsum2)
 }

 for(int r=0; r<REPEAT; r++) { ////////////  OUT-OF-ORDER-LOOP-F2+3
	float fsum1=0;
	float fsum2=0;
	for (int i=0; i<N; i+=6) {
		fsum1 += A[i] + A[i+1] + A[i+2];
		fsum2 += A[i+3]+ A[i+4]+ A[i+5];
	}
PRINT("O-ORDER ooo2+3(para):", fsum1+fsum2);
 }

 for(int r=0; r<REPEAT; r++) { ////////////  OUT-OF-ORDER-LOOP-F2+2
	float fsum1=0;
	float fsum2=0;
	for (int i=0; i<N; i+=4) {
		fsum1 += A[i] + A[i+1];
		fsum2 += A[i+2]+ A[i+3];
	}
PRINT("O-ORDER OPT ooo2+2(para):", fsum1+fsum2);
 }		

 for(int r=0; r<REPEAT; r++) { ////////////  OUT-OF-ORDER-LOOP-F2
	float fsum1=0;
	float fsum2=0;
	for (int i=0; i<N; i+=2) {
		fsum1 += A[i];
		fsum2 += A[i+1];
	}
PRINT( "O-ORDER ooo2(para):", fsum1+fsum2);
 }

 for(int r=0; r<REPEAT; r++) { ////////////  OUT-OF-ORDER-LOOP-F3
	float fsum1=0;
	float fsum2=0;
	float fsum3=0;
	for (int i=0; i<N; i+=3) {
		fsum1 += A[i];
		fsum2 += A[i+1];
		fsum3 += A[i+2];
	}
PRINT("O-ORDER ooo3(para):", fsum1+fsum2+fsum3);
 }

 for(int r=0; r<REPEAT; r++) { ////////////  OUT-OF-ORDER-LOOP-F4
	float fsum1=0;
	float fsum2=0;
	float fsum3=0;
	float fsum4=0;
	for (int i=0; i<N; i+=4) {
		fsum1 += A[i];
		fsum2 += A[i+1];
		fsum3 += A[i+2];
		fsum4 += A[i+3];
	}
PRINT("O-ORDER ooo4(para):", fsum1+fsum2+fsum3+fsum4);
 }
 #endif

 for(int r=0; r<REPEAT; r++) { //////////// PLAIN-LOOP-D
	double dsum=0;
	for (int i=0; i<N; i++) dsum += A[i];
PRINT("PLAIN LOOP-D:",dsum);
 }

#ifdef DO_PLAIN

 for(int r=0; r<REPEAT; r++) { ////////////  PLAIN-LOOP-F-omp
	float fsum=0;
	#pragma omp parallel for reduction(+:fsum)
	for (int i=0; i<N; i++) fsum += A[i];
PRINT("PLAIN LOOP-omp:", fsum);
 }

 for(int r=0; r<REPEAT; r++) { ////////////  PLAIN-LOOP-F
	float fsum=0;
	for (int i=0; i<N; i++) fsum += A[i];
PRINT("PLAIN LOOP:", fsum);
 }

 for(int r=0; r<REPEAT; r++) { ////////////  PLAIN-LOOP-F+4
	float fsum=0;
	for (int i=0; i<N; i+=4) fsum += A[i] + A[i+1] +A[i+2] +A[i+3];
PRINT("PLAIN LOOP-unr4:", fsum);
 }

 for(int r=0; r<REPEAT; r++) { ////////////  PLAIN-LOOP-F+8
	float fsum=0;
	for (int i=0; i<N; i+=8) fsum += A[i] + A[i+1] +A[i+2] +A[i+3] +A[i+4] + A[i+5] +A[i+6] +A[i+7];
PRINT("PLAIN LOOP-unr8:", fsum);
 }

 for(int r=0; r<REPEAT; r++) {
	float fsum=0;
	for (int i=0; i<N; i+=8) fsum += ((A[i] + A[i+1]) +(A[i+2] +A[i+3])) +((A[i+4] + A[i+5]) + (A[i+6] +A[i+7]));
PRINT("PLAIN LOOP-ooo8(by2):", fsum);
 }
 
 for(int r=0; r<REPEAT; r++) {
	float fsum=0;
	for (int i=0; i<N; i+=8) fsum += (A[i] + A[i+1] +A[i+2] +A[i+3]) +(A[i+4] + A[i+5] + A[i+6] +A[i+7]);
PRINT("PLAIN LOOP-ooo8(by4):", fsum);
 }
#endif

 for(int r=0; r<REPEAT; r++) {
	double dsum=0;
	for (int i=0; i<N; i+=8) dsum += ((A[i] + A[i+1]) + (A[i+2] +A[i+3])) + ((A[i+4] + A[i+5]) + (A[i+6] +A[i+7]));
PRINT("PLAIN LOOP-ooo8F->2D:", dsum);
 }

 for(int r=0; r<REPEAT; r++) {
	double dsum=0;
	#pragma omp parallel for reduction(+:dsum)
	for (int i=0; i<N; i+=8) dsum += ((A[i] + A[i+1]) + (A[i+2] +A[i+3])) + ((A[i+4] + A[i+5]) + (A[i+6] +A[i+7]));
PRINT("PLAIN LOOP-DF+8+omp:", dsum);
 }

#ifdef   DO_SIMD
 for(int r=0; r<REPEAT; r++) {
	float  __attribute__((aligned(16))) sum4[4] = {};
	__m128 s4, A4;
	s4 = _mm_load_ps(sum4);

	for (int i=0; i<N; i+=4) {
		  A4 = _mm_load_ps(&A[i]);
		  s4 = _mm_add_ps(s4, A4);
	}
	_mm_store_ps(sum4,s4);
PRINT("SSE:", sum4[0]+sum4[1]+sum4[2]+sum4[3]);
 }

 for(int r=0; r<REPEAT; r++) { ////////////  PLAIN-LOOP-FD+8gg
	float  __attribute__((aligned(16))) sum4[4] = {};
	double sum = 0;
	__m128 _0, _1, _2, _3, _4;

	for (int i=0; i<N; i+=32) {
		  _0 = _mm_load_ps(&A[i]);
		  _1 = _mm_load_ps(&A[i+4]);
		  _0 = _mm_add_ps(_0, _1);

		  _1 = _mm_load_ps(&A[i+8]);
		  _2 = _mm_load_ps(&A[i+12]);
		  _1 = _mm_add_ps(_1, _2);

		  _2 = _mm_load_ps(&A[i+16]);
		  _3 = _mm_load_ps(&A[i+20]);
		  _2 = _mm_add_ps(_2, _3);

		  _3 = _mm_load_ps(&A[i+24]);
		  _4 = _mm_load_ps(&A[i+28]);
		  _3 = _mm_add_ps(_3, _4);

		  //
		  _0 = _mm_add_ps(_0, _1);
		  _1 = _mm_add_ps(_2, _3);
		  _0 = _mm_add_ps(_0, _1);
		_mm_store_ps(sum4,_0);
		sum +=  (sum4[0]+sum4[1]) + (sum4[2]+sum4[3]);
	}

PRINT("SSE ooo8*f2d:", sum);
 }

 for(int r=0; r<REPEAT; r++) { ////////////  PLAIN-LOOP-FD+8gg
	float  __attribute__((aligned(16))) sum4[4] = {};
	double sum = 0;
	__m128 _0, _1, _2, _3, _4;

	#pragma omp parallel for private(_0, _1, _2, _3, _4, sum4) reduction(+:sum)
	for (int i=0; i<N; i+=32) {
		  _0 = _mm_load_ps(&A[i]);
		  _1 = _mm_load_ps(&A[i+4]);
		  _0 = _mm_add_ps(_0, _1);

		  _1 = _mm_load_ps(&A[i+8]);
		  _2 = _mm_load_ps(&A[i+12]);
		  _1 = _mm_add_ps(_1, _2);

		  _2 = _mm_load_ps(&A[i+16]);
		  _3 = _mm_load_ps(&A[i+20]);
		  _2 = _mm_add_ps(_2, _3);

		  _3 = _mm_load_ps(&A[i+24]);
		  _4 = _mm_load_ps(&A[i+28]);
		  _3 = _mm_add_ps(_3, _4);

		  //
		  _0 = _mm_add_ps(_0, _1);
		  _1 = _mm_add_ps(_2, _3);
		  _0 = _mm_add_ps(_0, _1);
		_mm_store_ps(sum4,_0);
		sum +=  (sum4[0]+sum4[1]) + (sum4[2]+sum4[3]);
	}

PRINT("SSE 8*f2d+omp:", sum);
 }

 for(int r=0; r<REPEAT; r++) { double sum = A.sum(); PRINT(".sum()", sum); }
 
 for(int r=0; r<REPEAT; r++) { double sum = A.sum<plain>(); PRINT(".sum<plain>()", sum); }

#endif

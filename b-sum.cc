

	#include "b-array.h"
	//////////////////////////  CONFIG
	const static unsigned long	N = 	100*1000*1000;
	///////////////////////////

	#include <lvv/benchmark.h>

		using lvv::sse;
		using lvv::sse2;
		using lvv::plain;
		using lvv::mk_array;
	#include <algorithm>
	


int main() {


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

///////////////////////////////////////////////////////////////////////////   TESTS
				

////////////   CREATE ARRAY
typedef array<TYPE, N> array_t;
array_t  A;
for (size_t i=0; i<N-1; i+=2) {
	A[i]  =1;
	A[i+1]=2;
}
A[333] = 3; // for max() testing
///////////////////////////////////////////
	

cout << "*** SUM  type:"  << typeid(TYPE).name() << endl;

#ifdef DO_PLAIN

cout << "*** PLAIN ***" << endl;

 for(int r=0; r<REPEAT; r++) { ////////////  OUT-OF-ORDER-LOOP-F2+4
	float fsum1=0;
	float fsum2=0;
	for (int i=0; i<N; i+=8) {
		fsum1 += A[i] + A[i+1] + A[i+2] + A[i+3];
		fsum2 += A[i+4]+ A[i+5]+ A[i+6] + A[i+7];
	}
	PRINT("O-ORDER ooo2+4:",fsum1+fsum2)
 }

 for(int r=0; r<REPEAT; r++) { ////////////  OUT-OF-ORDER-LOOP-F2+3
	float fsum1=0;
	float fsum2=0;
	for (int i=0; i<N; i+=6) {
		fsum1 += A[i] + A[i+1] + A[i+2];
		fsum2 += A[i+3]+ A[i+4]+ A[i+5];
	}
	PRINT("O-ORDER ooo2+3:", fsum1+fsum2);
 }

 for(int r=0; r<REPEAT; r++) { ////////////  OUT-OF-ORDER-LOOP-F2+2
	float fsum1=0;
	float fsum2=0;
	for (int i=0; i<N; i+=4) {
		fsum1 += A[i] + A[i+1];
		fsum2 += A[i+2]+ A[i+3];
	}
	PRINT("O-ORDER OPT ooo2+2:", fsum1+fsum2);
 }		

 for(int r=0; r<REPEAT; r++) { ////////////  OUT-OF-ORDER-LOOP-F2
	float fsum1=0;
	float fsum2=0;
	for (int i=0; i<N; i+=2) {
		fsum1 += A[i];
		fsum2 += A[i+1];
	}
	PRINT( "O-ORDER ooo2:", fsum1+fsum2);
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
	PRINT("O-ORDER ooo3:", fsum1+fsum2+fsum3);
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
	PRINT("O-ORDER ooo4:", fsum1+fsum2+fsum3+fsum4);
 }

 for(int r=0; r<REPEAT; r++) { //////////// PLAIN-LOOP-D
	double dsum=0;
	for (int i=0; i<N; i++) dsum += A[i];
	PRINT("PLAIN LOOP-D:",dsum);
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

 for(int r=0; r<REPEAT; r++) {
	double dsum=0;
	for (int i=0; i<N; i+=8) dsum += ((A[i] + A[i+1]) + (A[i+2] +A[i+3])) + ((A[i+4] + A[i+5]) + (A[i+6] +A[i+7]));
	PRINT("PLAIN LOOP-ooo8F->2D:", dsum);
 }

 #endif


 #ifdef     DO_OMP
cout << "*** OMP ***" << endl;

 for(int r=0; r<REPEAT; r++) { ////////////  PLAIN-LOOP-F-omp
	float fsum=0;
	#pragma omp parallel for reduction(+:fsum)
	for (long i=0; i<N; i++) fsum += A[i];
	PRINT("PLAIN LOOP-omp:", fsum);
 }

 for(int r=0; r<REPEAT; r++) {
	double dsum=0;
	#pragma omp parallel for reduction(+:dsum)
	for (long i=0; i<N; i+=8) dsum += ((A[i] + A[i+1]) + (A[i+2] +A[i+3])) + ((A[i+4] + A[i+5]) + (A[i+6] +A[i+7]));
	PRINT("PLAIN LOOP-DF+8+omp:", dsum);
 }

 for(int r=0; r<REPEAT; r++) {
	float  __attribute__((aligned(16))) sum4[4] = {};
	double sum = 0;
	__m128 _0, _1, _2, _3;

	#pragma omp parallel for private(_0, _1, _2, _3, sum4) reduction(+:sum)
	for (long i=0; i<N; i+=32) {
		  _0 = MK_REG(A[i]);		_0 = MM_ADD_OP(_0, MK_REG(A[i+4]));
		  _1 = MK_REG(A[i+8]);		_1 = MM_ADD_OP(_1, MK_REG(A[i+12]));
		  _2 = MK_REG(A[i+16]);		_2 = MM_ADD_OP(_2, MK_REG(A[i+20]));
		  _3 = MK_REG(A[i+24]);		_3 = MM_ADD_OP(_3, MK_REG(A[i+28]));

		  _0 = MM_ADD_OP(_0, _1);
		  _1 = MM_ADD_OP(_2, _3);
		  _0 = MM_ADD_OP(_0, _1);
		_mm_store_ps(sum4,_0);
		sum +=  (sum4[0]+sum4[1]) + (sum4[2]+sum4[3]);
	}

	PRINT("SSE 4*f2d+omp:", sum);
 }

 for(int r=0; r<REPEAT; r++) {
	float  __attribute__((aligned(16))) sum4[4] = {};
	double sum = 0;
	__m128 _0, _1, _2, _3;

	#pragma omp parallel for private(_0, _1, _2, _3, sum4) reduction(+:sum)
	for (long i=0; i<N; i+=32) {
		  _0 = MK_REG(A[i]);		_0 = MM_ADD_OP(_0, MK_REG(A[i+4]));
		  _1 = MK_REG(A[i+8]);		_1 = MM_ADD_OP(_1, MK_REG(A[i+12]));
		  _2 = MK_REG(A[i+16]);		_2 = MM_ADD_OP(_2, MK_REG(A[i+20]));
		  _3 = MK_REG(A[i+24]);		_3 = MM_ADD_OP(_3, MK_REG(A[i+28]));

		  _0 = MM_ADD_OP(_0, _1);
		  _1 = MM_ADD_OP(_2, _3);
		  _0 = MM_ADD_OP(_0, _1);
		 __builtin_prefetch((void*)&A[i+512],0,0);      
		_mm_store_ps(sum4,_0);
		sum +=  (sum4[0]+sum4[1]) + (sum4[2]+sum4[3]);
	}

	PRINT("SSE 4*f2d+omp+pf512:", sum);
 }

 #endif


 #ifdef   DO_SIMD

cout << "*** SIMD ***" << endl;

 for(int r=0; r<REPEAT; r++) {
	float  __attribute__((aligned(16))) sum4[4] = {};
	__m128 s4, A4;
	s4 = MK_REG(sum4);

	for (int i=0; i<N; i+=4) {
		  A4 = MK_REG(A[i]);
		  s4 = MM_ADD_OP(s4, A4);
	}
	_mm_store_ps(sum4,s4);
	PRINT("sse in plain loop", sum4[0]+sum4[1]+sum4[2]+sum4[3]);
 }

for(int r=0; r<REPEAT; r++) { double sum = std::accumulate(A.begin(), A.end(), float());  PRINT("stl::accumulate(,,float())", sum); }
for(int r=0; r<REPEAT; r++) { double sum = std::accumulate(A.begin(), A.end(), double());  PRINT("stl::accumulate(,,double())", sum); }
#define GLIBCXX_PARALLEL 1
for(int r=0; r<REPEAT; r++) { double sum = std::accumulate(A.begin(), A.end(), 0.0f);  PRINT("stl::accumulate() parallel", sum); }

for(int r=0; r<REPEAT; r++) { double sum = A.sum(); PRINT(".sum()", sum); }

for(int r=0; r<REPEAT; r++) { double sum = A.sum<plain>(); PRINT(".sum<plain>()", sum); }


 #ifdef __SSE3__
 for(int r=0; r<REPEAT; r++) {
	double sum;
	__m128d _sum = _mm_set1_pd(0.0);
	//__m128d _0d;
	REG_T _0, _1, _2, _3;

	for (int i=0; i<N-8*4; i+=8*4) {
		  _0 = MK_REG(A[i+0]);	_0 = MM_ADD_OP(_0, MK_REG(A[i+4 ]));
		  _1 = MK_REG(A[i+8]);	_1 = MM_ADD_OP(_1, MK_REG(A[i+12]));
		  _2 = MK_REG(A[i+16]); _2 = MM_ADD_OP(_2, MK_REG(A[i+20]));
		  _3 = MK_REG(A[i+24]); _3 = MM_ADD_OP(_3, MK_REG(A[i+28]));

		  _0 = MM_ADD_OP(_0, _1);
		  _2 = MM_ADD_OP(_2, _3);
		  _0 = MM_ADD_OP(_0, _2);

		_0 = _mm_hadd_ps(_0,_0);
		_0 = _mm_hadd_ps(_0,_0);
		(__m128d&)_0 = _mm_cvtss_sd((__m128d)_0,_0);
		_sum = _mm_add_sd(_sum, (__m128d)_0);
	}
	_mm_store_sd(&sum, _sum);

	PRINT("SSE3 ooo4*f2d (Hadd):", sum);
 }
 #endif

 #ifdef __SSE3__
 for(int r=0; r<REPEAT; r++) {
	double sum;
	__m128d _sum = _mm_set1_pd(0.0);
	REG_T _0, _1, _2, _3;

	for (int i=0; i<N-8*4; i+=8*4) {
		  _0 = MK_REG(A[i+0]);	_0 = MM_ADD_OP(_0, MK_REG(A[i+4 ]));
		  _1 = MK_REG(A[i+8]);	_1 = MM_ADD_OP(_1, MK_REG(A[i+12]));
		  _2 = MK_REG(A[i+16]); _2 = MM_ADD_OP(_2, MK_REG(A[i+20]));
		  _3 = MK_REG(A[i+24]); _3 = MM_ADD_OP(_3, MK_REG(A[i+28]));

		 __builtin_prefetch((void*)&A[i+512],0,0);      

		  _0 = MM_ADD_OP(_0, _1);
		  _2 = MM_ADD_OP(_2, _3);
		  _0 = MM_ADD_OP(_0, _2);

		_0 = _mm_hadd_ps(_0,_0);
		_0 = _mm_hadd_ps(_0,_0);
		(__m128d&)_0 = _mm_cvtss_sd((__m128d)_0,_0);
		_sum = _mm_add_sd(_sum,(__m128d)_0);
	}
	_mm_store_sd(&sum, _sum);

	PRINT("SSE3 ooo4*f2d +pf512 (Hadd):", sum);
 }

 for(int r=0; r<REPEAT; r++) {
	double sum = 0;
	REG_T _0, _1, _2, _3;

	for (int i=0; i<N; i+=32) {
		  _0 = MK_REG(A[i+0]);	_0 = MM_ADD_OP(_0, MK_REG(A[i+4 ]));
		  _1 = MK_REG(A[i+8]);	_1 = MM_ADD_OP(_1, MK_REG(A[i+12]));
		  _2 = MK_REG(A[i+16]); _2 = MM_ADD_OP(_2, MK_REG(A[i+20]));

		  _3 = MK_REG(A[i+24]); _3 = MM_ADD_OP(_3, MK_REG(A[i+28]));

		  _0 = MM_ADD_OP(_0, _1);
		  _1 = MM_ADD_OP(_2, _3);
		  _0 = MM_ADD_OP(_0, _1);

		sum +=
			((*(array<float,4> *)&_0)[0]
			+(*(array<float,4> *)&_0)[1])
			+
			((*(array<float,4> *)&_0)[2]
			+(*(array<float,4> *)&_0)[3])
		;
	}

	PRINT("SSE ooo4*f2d (no-load, no-store):", sum);
 }

 for(int r=0; r<REPEAT; r++) {
	float  __attribute__((aligned(16))) sum4[4] = {};
	double sum = 0;
	REG_T _0, _1, _2, _3;

	for (int i=0; i<N; i+=32) {
		  _0 = MK_REG(A[i+0]);	_0 = MM_ADD_OP(_0, MK_REG(A[i+4 ]));
		  _1 = MK_REG(A[i+8]);	_1 = MM_ADD_OP(_1, MK_REG(A[i+12]));
		  _2 = MK_REG(A[i+16]); _2 = MM_ADD_OP(_2, MK_REG(A[i+20]));

		  _3 = MK_REG(A[i+24]); _3 = MM_ADD_OP(_3, MK_REG(A[i+28]));

		  _0 = MM_ADD_OP(_0, _1);
		  _1 = MM_ADD_OP(_2, _3);
		  _0 = MM_ADD_OP(_0, _1);
		_mm_store_ps(sum4,_0);
		sum +=  (sum4[0]+sum4[1]) + (sum4[2]+sum4[3]);
	}

	PRINT("SSE ooo4*f2d (no-load, store):", sum);
 }

 for(int r=0; r<REPEAT; r++) {
	float  __attribute__((aligned(16))) sum4[4] = {};
	double sum = 0;
	__m128 _0, _1, _2, _3, _4;

	for (int i=0; i<N; i+=32) {
		  _0 = MK_REG(A[i]);
		  _1 = MK_REG(A[i+4]);
		  _0 = MM_ADD_OP(_0, _1);

		  _1 = MK_REG(A[i+8]);
		  _2 = MK_REG(A[i+12]);
		  _1 = MM_ADD_OP(_1, _2);

		  _2 = MK_REG(A[i+16]);
		  _3 = MK_REG(A[i+20]);
		  _2 = MM_ADD_OP(_2, _3);

		  _3 = MK_REG(A[i+24]);
		  _4 = MK_REG(A[i+28]);
		  _3 = MM_ADD_OP(_3, _4);

		  _0 = MM_ADD_OP(_0, _1);
		  _1 = MM_ADD_OP(_2, _3);
		  _0 = MM_ADD_OP(_0, _1);
		_mm_store_ps(sum4,_0);
		sum +=  (sum4[0]+sum4[1]) + (sum4[2]+sum4[3]);
	}

	PRINT("SSE ooo4*f2d (with load)", sum);
 }

 for(int r=0; r<REPEAT; r++) {
	double sum = 0;
	REG_T _0, _1, _2, _3;

	for (int i=0; i<N; i+=32) {
		  _0 = MK_REG(A[i+0]);	_0 = MM_ADD_OP(_0, MK_REG(A[i+4 ]));
		  _1 = MK_REG(A[i+8]);	_1 = MM_ADD_OP(_1, MK_REG(A[i+12]));
		  _2 = MK_REG(A[i+16]); _2 = MM_ADD_OP(_2, MK_REG(A[i+20]));

		  _3 = MK_REG(A[i+24]); _3 = MM_ADD_OP(_3, MK_REG(A[i+28]));

		  _0 = MM_ADD_OP(_0, _1);
		  _2 = MM_ADD_OP(_2, _3);
		  _0 = MM_ADD_OP(_0, _2);

		sum +=
			((*(array<float,4> *)&_0)[0]
			+(*(array<float,4> *)&_0)[1])
			+
			((*(array<float,4> *)&_0)[2]
			+(*(array<float,4> *)&_0)[3])
		;
	}

	PRINT("SSE ooo4*f2d: (no load; no store sum )", sum);
 }

 for(int r=0; r<REPEAT; r++) {
	float  __attribute__((aligned(16))) sum4[4] = {};
	double sum = 0;
	REG_T _0, _1, _2, _3;

	for (int i=0; i<N; i+=64) {
		  _0 = MK_REG(A[i+0]);	_0 = MM_ADD_OP(_0, MK_REG(A[i+4 ]));
		  _1 = MK_REG(A[i+8]);	_1 = MM_ADD_OP(_1, MK_REG(A[i+12]));
		  _0 = MM_ADD_OP(_0, _1);

		  _1 = MK_REG(A[i+16]);	_1 = MM_ADD_OP(_1, MK_REG(A[i+20]));
		  _2 = MK_REG(A[i+24]); _2 = MM_ADD_OP(_2, MK_REG(A[i+28]));
		  _1 = MM_ADD_OP(_1, _2);

		  _0 = MM_ADD_OP(_0, _1);

		  _1 = MK_REG(A[i+32]);	_1 = MM_ADD_OP(_1, MK_REG(A[i+36 ]));
		  _2 = MK_REG(A[i+40]);	_2 = MM_ADD_OP(_2, MK_REG(A[i+44]));
		  _1 = MM_ADD_OP(_1, _2);

		  _2 = MK_REG(A[i+48]); _2 = MM_ADD_OP(_2, MK_REG(A[i+52]));
		  _3 = MK_REG(A[i+56]); _3 = MM_ADD_OP(_3, MK_REG(A[i+60]));
		  _2 = MM_ADD_OP(_2, _3);

		  _1 = MM_ADD_OP(_1, _2);

		  _0 = MM_ADD_OP(_0, _1);
		 __builtin_prefetch((void*)&A[i+128],0,0);      


		_mm_store_ps(sum4,_0);
		sum +=  (sum4[0]+sum4[1]) + (sum4[2]+sum4[3]);
	}

	PRINT("SSE ooo8*f2d +pf128: (no load; inline-sum)", sum);
 }

 for(int r=0; r<REPEAT; r++) {
	float  __attribute__((aligned(16))) sum4[4] = {};
	double sum = 0;
	REG_T _0, _1, _2, _3;

	for (int i=0; i<N; i+=64) {
		  _0 = MK_REG(A[i+0]);	_0 = MM_ADD_OP(_0, MK_REG(A[i+4 ]));
		  _1 = MK_REG(A[i+8]);	_1 = MM_ADD_OP(_1, MK_REG(A[i+12]));
		  _0 = MM_ADD_OP(_0, _1);

		  _1 = MK_REG(A[i+16]);	_1 = MM_ADD_OP(_1, MK_REG(A[i+20]));
		  _2 = MK_REG(A[i+24]); _2 = MM_ADD_OP(_2, MK_REG(A[i+28]));
		  _1 = MM_ADD_OP(_1, _2);

		  _0 = MM_ADD_OP(_0, _1);

		  _1 = MK_REG(A[i+32]);	_1 = MM_ADD_OP(_1, MK_REG(A[i+36 ]));
		  _2 = MK_REG(A[i+40]);	_2 = MM_ADD_OP(_2, MK_REG(A[i+44]));
		  _1 = MM_ADD_OP(_1, _2);

		  _2 = MK_REG(A[i+48]); _2 = MM_ADD_OP(_2, MK_REG(A[i+52]));
		  _3 = MK_REG(A[i+56]); _3 = MM_ADD_OP(_3, MK_REG(A[i+60]));
		  _2 = MM_ADD_OP(_2, _3);

		  _1 = MM_ADD_OP(_1, _2);

		  _0 = MM_ADD_OP(_0, _1);

		 __builtin_prefetch((void*)&A[i+256],0,0);      

		_mm_store_ps(sum4,_0);
		sum +=  (sum4[0]+sum4[1]) + (sum4[2]+sum4[3]);
	}

	PRINT("SSE ooo8*f2d +pf256: (no load; inline-sum;)", sum);
 }

 for(int r=0; r<REPEAT; r++) {
	float  __attribute__((aligned(16))) sum4[4] = {};
	double sum = 0;
	REG_T _0, _1, _2, _3;

	for (int i=0; i<N; i+=64) {
		  _0 = MK_REG(A[i+0]);	_0 = MM_ADD_OP(_0, MK_REG(A[i+4 ]));
		  _1 = MK_REG(A[i+8]);	_1 = MM_ADD_OP(_1, MK_REG(A[i+12]));
		  _0 = MM_ADD_OP(_0, _1);

		  _1 = MK_REG(A[i+16]);	_1 = MM_ADD_OP(_1, MK_REG(A[i+20]));
		  _2 = MK_REG(A[i+24]); _2 = MM_ADD_OP(_2, MK_REG(A[i+28]));
		  _1 = MM_ADD_OP(_1, _2);

		  _0 = MM_ADD_OP(_0, _1);

		  _1 = MK_REG(A[i+32]);	_1 = MM_ADD_OP(_1, MK_REG(A[i+36 ]));
		  _2 = MK_REG(A[i+40]);	_2 = MM_ADD_OP(_2, MK_REG(A[i+44]));
		  _1 = MM_ADD_OP(_1, _2);

		  _2 = MK_REG(A[i+48]); _2 = MM_ADD_OP(_2, MK_REG(A[i+52]));
		  _3 = MK_REG(A[i+56]); _3 = MM_ADD_OP(_3, MK_REG(A[i+60]));
		  _2 = MM_ADD_OP(_2, _3);

		  _1 = MM_ADD_OP(_1, _2);

		  _0 = MM_ADD_OP(_0, _1);


		_mm_store_ps(sum4,_0);
		sum +=  (sum4[0]+sum4[1]) + (sum4[2]+sum4[3]);
	}

	PRINT("SSE unr8*f2d", sum);
 }


 for(int r=0; r<REPEAT; r++) {
	float  __attribute__((aligned(16))) sum4[4] = {};
	double sum = 0;
	REG_T _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10;

	for (int i=0; i<N-64; i+=64) {
		  _0 = MK_REG(A[i+0]);	_0 = MM_ADD_OP(_0, MK_REG(A[i+4 ]));
		  _1 = MK_REG(A[i+8]);	_1 = MM_ADD_OP(_1, MK_REG(A[i+12]));
		  _0 = MM_ADD_OP(_0, _1);

		  _2 = MK_REG(A[i+16]);	_2 = MM_ADD_OP(_2, MK_REG(A[i+20]));
		  _3 = MK_REG(A[i+24]); _3 = MM_ADD_OP(_3, MK_REG(A[i+28]));
		  _2 = MM_ADD_OP(_2, _3);


		  _4 = MK_REG(A[i+32]);	_4 = MM_ADD_OP(_4, MK_REG(A[i+36 ]));
		  _5 = MK_REG(A[i+40]);	_5 = MM_ADD_OP(_5, MK_REG(A[i+44]));
		  _4 = MM_ADD_OP(_4, _5);

		  _6 = MK_REG(A[i+48]); _6 = MM_ADD_OP(_6, MK_REG(A[i+52]));
		  _7 = MK_REG(A[i+56]); _7 = MM_ADD_OP(_7, MK_REG(A[i+60]));
		  _6 = MM_ADD_OP(_6, _7);

		  _8 = MM_ADD_OP(_0, _2);
		  _9 = MM_ADD_OP(_4, _6);

		  _10 = MM_ADD_OP(_8, _9);


		_mm_store_ps(sum4,_10);
		sum +=  (sum4[0]+sum4[1]) + (sum4[2]+sum4[3]);
	}

	PRINT("SSE ooo8*f2d: ", sum);
 }


 for(int r=0; r<REPEAT; r++) {
	float  __attribute__((aligned(16))) sum4[4] = {};
	double sum = 0;
	REG_T _0, _1, _2, _3;

	for (int i=0; i<N; i+=32) {
		  _0 = MK_REG(A[i+0]);	_0 = MM_ADD_OP(_0, MK_REG(A[i+4 ]));
		  _1 = MK_REG(A[i+8]);	_1 = MM_ADD_OP(_1, MK_REG(A[i+12]));
		  _2 = MK_REG(A[i+16]); _2 = MM_ADD_OP(_2, MK_REG(A[i+20]));

		  _3 = MK_REG(A[i+24]); _3 = MM_ADD_OP(_3, MK_REG(A[i+28]));

		  _0 = MM_ADD_OP(_0, _1);
		  _2 = MM_ADD_OP(_2, _3);
		  _0 = MM_ADD_OP(_0, _2);

		_mm_store_ps(sum4,_0);
		sum +=  (sum4[0]+sum4[1]) + (sum4[2]+sum4[3]);		// TODO: inline assambly
	}

	PRINT("SSE ooo4*f2d: (no load; inline-sum)", sum);
 }
 #endif  // sse3
 #endif  // DO_SIMD

	cerr << endl;  
 }

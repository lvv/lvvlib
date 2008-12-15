	#include <immintrin.h>
	#include <stdio.h>
	#include <stdint.h>

int main(int argc, char *argv[]) {

	int16_t  A[2000];    for (int i=0; i<(2000-2); i+=2) { A[i]=1;  A[i+1]=2; };  A[333] = 3; 

	 #define mk_m128i(x) *(__m128i*)&(x)
	__m128i m1 = mk_m128i(A[0]);
	__m128i m2 = mk_m128i(A[8]);

	for (int i= 16;  i < 2000-16; i+=16) { 			// SSE
		 m1 = _mm_max_epi16(m1, mk_m128i(A[i]) );
		 m2 = _mm_max_epi16(m2, mk_m128i(A[i+8]) );
	}

	m1 = _mm_max_epi16(m1, m2);

	int16_t* ip  = (int16_t*)&m1;  
	printf("%hi %hi %hi %hi  %hi %hi %hi %hi \n", *ip++, *ip++, *ip++, *ip++, *ip++, *ip++, *ip++, *ip);	

	return 0;
 }

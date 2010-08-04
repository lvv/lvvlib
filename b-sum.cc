

	#include "b-array.h"
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

	///////////////////////////////////
	#include "b-sum.h"
				

	cerr << endl;  
 }

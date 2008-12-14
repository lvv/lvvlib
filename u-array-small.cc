
	#define CANUSE_SSE
	#define CANUSE_SSE2
	#define CANUSE_SSE3
//#include <iostream>

#include <lvv/math.h>
	using lvv::eq;
#include <lvv/array.h>
	using lvv::array;
	using lvv::sse;
	using lvv::sse2;
	using lvv::plain;
	using lvv::openmp;
	using lvv::select_method;

#include <lvv/lvv.h>

#include <lvv/check.h>
	using namespace std;

                int
main() {
	array<int16_t,1000> h1000 = {{1,2,3,4,5,6,7,8,9,10}};	
	CHECKeq((h1000.max_impl(sse2(),int16_t())),10);
}

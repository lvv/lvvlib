== LvvLib - C++ utility library

//  HTML rendered version of this file is at:  http://volnitsky.com/project/lvvlib

:gh-ll:		http://github.com/lvv/lvvlib/tree/master/

Initially collection of headers that I used in my projects.  'LVV' are my initials (Leonid V. Volnitsky).
Needs some cleanup, dependency pruning and documentation. 

=== http://github.com/lvv/lvvlib/tree/master/array.h[array.h]

Enhanced version of http://www.boost.org/doc/libs/1_37_0/doc/html/array.html[`boost::array`] 
which is plain C array wrapped in class to make it STL compatible
container.  If you look in such array in debugger its looks exactly like C
arrays (which means you can freely cast to and from C array).
There are no mallocs,  no extra pointers, no extraneous class members.
Because it doesn't have constructor, it is an agrigate type, meaning that it can be initialised like C arrays,
some vector operation are supported. Sample use:

---------------------------------
using lvv:array;
array<float,3>	A = {{1., 2., 3.}};
array<float,3>	B;
B = 1.;
A += B;
cout  << "vector A: "  <<  A  << endl;
cout  << "vector B: "  <<  B  << endl;
cout  << "dot product: "  <<  dot_prod(A,B)  << endl;
------------------------------

Second set of curly braces needed because this is an array inside a class. 
All `B` elements are assigned scalar `1.f`, then vector `B` added to `A`, you can
send `lvv::array` to `iostream`.
GCC 4.4 promoted `boost::array` to `tr1::array`.

.lvv::array have following added capabilities:
- Vector operation
- Optimized template specialization for specific combination of CPU capabilities,  array size and type.
	* explicit SSE vectorization (gcc not very good yet in auto-vectorization).
	* parallelization with OpenMP
	* out-of order execution optimization
- Index of first element defaults to 0, but can be any number.
- Index value tested if it is in valid range when `NDEBUG` macro  is not defined (not optimized compile). 
- basic linear algebra functions:  `norm2(A)`, `distance_norm2(A1,A2)`, `dot_product(A1,A2)`, etc

==== Specialization
Template specialization is technique which allow with zero overhead to select
most appropriate implementation.  Zero overhead means no run-time
implementation-selection code, everything done in compile time. This is similar
to run time CPU dispatch, but it is done in compile time. Selection logic is based on data-type, performed
operation, target cpu, array size.  Below is benchmark of specialised
operations. Benchmarks are done on Core2 Duo, 2.2Ghz, with GCC-4.4.  Benchmark
source is at `b-*.h` files. 

.Sum of 100,000,000 float-s with values {1, 2, 1, 2, 1, 2 ...}
[cols="3,^2,^2, 16",frame="topbot",options="header"]
|============================================================================================
| *Method* 			| *Ticks per cycle* | *Computed Value*  | *Source*
| lvv::array member fn		| 1.74              | 1.5e+08           | `float  sum = A.sum();`  // same as `sum<sse>()`
| lvv::array, explicit OpenMP	| 1.67              | 1.5e+08           | `float  sum = A.sum<omp>();`
| plain for-loop, double	| 3.14              | 1.5e+08           | `double sum=0;  for (int i=0; i<N; i++) sum += A[i];`
| plain for-loop, float		| 3.06              | 3.35e+07		| `float  sum=0;  for (int i=0; i<N; i++) sum += A[i];`
| std::accumulate<float>()	| 3.06              | 3.35e+07		| `float  sum = accumulate(A.begin(), A.end(), 0.f));`
|============================================================================================
Note that two last lines have big rounding error. Benchmark source is at b-array.cc.
Further optimizatin is difficult as it is obviously memory bound. 

.Maximum of 100,000,000 float-s
[cols="2,^1,11",frame="topbot",options="header"]
|=======================================================================================================================
| *Method* 		| *Ticks per cycle* | * *Source*
| lvv::array member fn	| 1.63              | `float  max = A.max()`
| plain for-loop	| 5.81              | `float  max=0;  for (size_t i=0; i<N; i++) if (A[i] >  max) max = A[i];`
| OpenMP		| 1.88              | `(source same as above, 2xCPU, no check for race)`
| std::max_element()	| 5.81              | `float  max = *std::max_element (A.begin(), A.end());`
| SSE intrinsics	| 1.67              | `__m128 m = mk_m128(A[0]);  for (size_t i=4; i<N; i+=4) { m = _mm_max_ps(m, mk_m128(A[i]) ); } ...`
|========================================================================================================================

So far I implemented only combinations needed for my work. Hopefully there will
be less blank space in table bellow as I will have more time or there will be outside contributions.

.Implemented combinations
[cols="1,^1,^1,^1,^1,^1,^1,^1,^1",frame="topbot",options="header"]
|=============================================================================================
| *Type*         |  *sum*  | *max* | *min* | *lower_bound* | *find* | *V1 += V2* | *V1 -= V2* | *...*
| *generic*      |  std::  |  std::|       |   std::       | std::  | for-loop   | for-loop   |
| *float*        |  sse    |  sse  |       |               |        |            |            |
| *double*       |         |       |       |               |        |            |            |
| *long double*  |         |       |       |               |        |            |            |
| *int8_t*       |         |       |       |               |        |            |            |
| *int16_t*      |         |  sse2 |       |               |        |            |            |
| *int32_t*      |         |       |       |               |        |            |            |
| *int64_t*      |         |       |       |               |        |            |            |
| *uint8_t*      |         |       |       |               |        |            |            |
| *uint16_t*     |         |       |       |               |        |            |            |
| *uint32_t*     |         |       |       |               |        |            |            |
| *uint64_t*     |         |       |       |               |        |            |            |
|==============================================================================================


=== *eq()* - numeric comparison template function (http://github.com/lvv/lvvlib/tree/master/math.h[math.h])
Used for numeric comparison in generic programming.  For floating point types
comparison precision will scale proportionally to type used and will still work if
integral type used. If different types are compared, ulp of lowest precision type is used. 

Error in floating point expression is proportional to absolute value of a
number and precision of a type used.  Error will be bigger for `10000` than for
`0.00001` and bigger for `float` than for `double`. This absolute value here is
called  _characteristic value_.  Usually characteristic value is equal to value
that we want to compare, and that is what `eq` defaults to: average of
absolutes of compared values (1st and 2nd argument).  But in chain of calculations characteristic
value can be different.  For example in: `x=1000.1;  y=x-1000.` characteristic
value of `y` is `1000` even though it is approximately equal `0.1`

Type-precision is expressed as http://en.wikipedia.org/wiki/Unit_in_the_last_place[ULP]
for value `1.0`  (`== std::numeric_limits<T>::epsilon()`).  This is only possible way to make it
invariant to type used. That is error expressed in ULP is about the same when
we change type (needed for generic programming).

The longer chain of calculation is the bigger accumulated error is. 
In `eq` acceptable error specified as integer ULP
multiplier (3th template argument). Default is 100. 

For integers: If one of arguments is `unsigned` then other argument converted to unsigned type too (to avoid overflows).
It is  assumed that if comparison is  with `unsigned` then it is guaranted that other value is positive (TODO: add assert check)


=== check.h

Very basic unit testing. I had to write my own unit testing because gcc44 can not
compile BOOST_CHECK. Implemented mostly in macros. See examples in any ++u-*.cc++  file.

=== Other

[width="80%",cols="3,3,6",frame="none",options="header"]
|==========================
| Header                 | Sample Use                    | Description
| {gh-ll}mmap.h[mmap.h]  | {gh-ll}t-mmap.cc[t-mmap.cc]   | simplified mmap files ops.
| {gh-ll}timer.h[timer.h]| {gh-ll}t-timer.cc[t-timer.cc] | timer of interval/total for cpu/wall/tick time.
| {gh-ll}meta.h[meta.h]  | {gh-ll}u-meta.cc[u-meta.cc]   | meta programming
| {gh-ll}float.h[float.h]  | {gh-ll}u-float.cc[u-float.cc]| floating point traits and bit-twiddling
|==========================

include::~/p/volnitsky.com/project/howto-submit-patch.txt[]

== Refrence
http://www.ddj.com/cpp/184401967?pgno=1[Dr. Dobb's Journal: Optimizing C/C++ with Inline Assembly Programming.  June 01, 2005 ]

// vim:ft=asciidoc:

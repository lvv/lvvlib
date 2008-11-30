== LvvLib - C++ utility library

Initially collection of headers that I created for use in my projects.  LVV stands for my
initials (Leonid V. Volnitsky). Needs some cleanup,
dependency pruning and documentation. 

=== http://github.com/lvv/lvvlib/tree/master/array.h[array.h]

Similar to http://http://www.boost.org/doc/libs/1_37_0/doc/html/array.html[`boost::array`]
which is basically plain C array wrapped in class to make it STL compatible
container.  If you look in such array in debugger its looks exactly like C
arrays (which means you can freely cast to and from C array). Because it
doesn't have constructor, it can be initialised like C arrays:

  lvv::array<float,3> A = {{1., 2., 3.}}  //  this is not C++0x,

Second set of curly braces needed because this is an array inside a class. 
There are no mallocs,  no extra pointers, no extraneous class members.

.lvv::array have following added capabilities:
- Index of first element defaults to 0, but can be any number
- Index `i` in `A[i]` is checked if it is in valid range when `NDEBUG` macro  is not defined (i.e. for  `gcc -g` ). 
- array can be sent to iostream:  `cout << A;`
- matrix type defined as array of arrays
- basic linear algebra functions:  `norm2(A)`, `distance_norm2(A1,A2)`, `dot_product(A1,A2)`, etc
- array assignment expressions: `A1 += A2;`

.Soon to be added:
- non-assignment array expressions (malloc free, through lazy evaluation) like: `A1 = A2 + A3;`
- explicit SSE vectorization for vector operations (gcc not very good yet in auto-vectorization).
- vector operation parallelization with OpenMP

=== http://github.com/lvv/lvvlib/tree/master/math.h[math.h]:  *eq()* - numeric comparison template function
Used for numeric comparison in generic programming.  For floating point types
comparison precision will scale proportionally to type used and will still work if
integral type used.

Error in floating point expression is proportional to absolute value of a
number and precision of a type used.  Error will be bigger for `10000` then for
`0.00001` and bigger for `float` then for `double`. This absolute value here
called  _characteristic value_.  Usually characteristic value is equal to value
that we want to compare, and that is what `eq` defaults to: average of
absolutes of 1st and 2nd argument.  But in chain of calculations characteristic
value can be different.  For example in: `x=1000.1;  y=x-1000.` characteristic
value of `y` is `1000` even though it is approximately equal `0.1`

Type-precision is expressed as http://docs.sun.com/source/806-3568/ncg_goldberg.html[ULP]
for value `1.0`  (`== std::numeric_limits<T>::epsilon()`).


The longer chain of calculation is the bigger accumulated error is.  Error also
depends on type of expression.  In `eq` acceptable error specified as integer ULP
multiplier in 3th template argument. Default is 100. 

If types have different types they are both converted to mutually compatible type.
Highest precision of two arguments are used.

For integers: If one of arguments is `unsigned` then other argument converted to unsigned type too.


=== Other

[width="80%",cols="3,3,6",frame="none",options="header"]
|==========================
| Header                                                    | Sample Use                                                      | Description
| http://github.com/lvv/lvvlib/tree/master/check.h[check.h] | http://github.com/lvv/lvvlib/tree/master/t-equal.h[`t-equal.cc`]| simple unit testing.        
| http://github.com/lvv/lvvlib/tree/master/mmap.h[mmap.h]   | http://github.com/lvv/lvvlib/tree/master/t-mmap.h[`t-mmap.cc`]  | simplified mmap files ops.  
| http://github.com/lvv/lvvlib/tree/master/timer.h[timer.h] | http://github.com/lvv/lvvlib/tree/master/t-timer.h[`t-timer.cc`]| interval and wall timer.        
|==========================


// vim:ft=asciidoc:

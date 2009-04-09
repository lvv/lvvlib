= LvvLib - C++ utility library

//  HTML rendered version of this file is at:  http://volnitsky.com/project/lvvlib

:gh-ll:		http://github.com/lvv/lvvlib/tree/master/

Initially collection of headers that I used in my projects.  'LVV' are my initials (Leonid V. Volnitsky).
Needs some cleanup, dependency pruning and documentation. 

== array.h
See link:array.html[array docs]


== math.h
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


== check.h

Very basic unit testing. I had to write my own unit testing because gcc44 can not
compile BOOST_CHECK. Implemented mostly in macros. See examples in any ++u-*.cc++  file.

== Other

[width="80%",cols="3,3,6",frame="none",options="header"]
|==========================
| Header   | Sample Use  | Description
| mmap.h   | t-mmap.cc   | simplified mmap files ops.
| timer.h  | t-timer.cc  | timer of interval/total for cpu/wall/tick time.
| meta.h   | u-meta.cc   | meta programming
| float.h  | u-float.cc  | floating point traits and bit-twiddling
|==========================

include::~/p/volnitsky.com/project/howto-submit-patch.txt[]

== Refrence
Dr. Dobb's Journal: 'Optimizing C/C++ with Inline Assembly Programming'.  June 01, 2005 -  www.ddj.com/cpp/184401967?pgno=1

// vim:ft=asciidoc:


//#include <iostream>

#include <lvv/math.h>
	using lvv::eq;
#include <lvv/array.h>
#include <lvv/lvv.h>
	using lvv::array;

#include <lvv/check.h>
//#include <lopti/convert-gsl.h>
	using namespace std;
	using namespace lvv;
 #include  <boost/type_traits/alignment_of.hpp>
 	using boost::alignment_of;

                int
main() {

	typedef array<int,5> a5_t;

	// CTOR
	array <int, 5   >       a0 = {{0,1,2,3,4}}; 			// index starts from 0 
		CHECK(a0.ibegin()==0);
		CHECK( a0.iend()==5);
		CHECK( a0.size()==5);
	
	array <int, 5, 1>	a1 = {{1,2,3,4,5}}; 			// index starts from 1
		CHECK( a1.ibegin()==1);
		CHECK( a1.iend()==6);
		CHECK( a1.size()==5);
	array <int, 5, -2>	an = {{-2,-1,0,1,2}}; 			// index starts from -2
		CHECK( an.ibegin()==-2);
		CHECK( an.iend()==3);
		CHECK( an.size()==5);

	array <int, 5, 1> const b1 = {{10,20,30,40,50}}; 			// index starts from 1

	//	cout << "a0: "       << a0 << endl;
	
	////////////////////////////////////////////////////  vector assignment
	// = scalar
	array<int,5,0> b0;
	b0 = 0;
	b0 = 2;
		CHECK( b0[0]		== 2 );
		CHECK( b0[3]		== 2 );

	// = diffrent type vector
	array<long,5,0> c0;
	c0 = a0;
		CHECK( c0[0]		== 0 );
		CHECK( c0[3]		== 3 );

	////////////////////////////////////////////////////  vector ops 
	//  array op= scalar : an+10 
	an += 10;
		CHECK( *an.begin()	== -2+10 );
		CHECK( an[-1]		== -1+10 );
		CHECK( an[an.iend()-1]	==  2+10 );

	//  array op= array 
	a1 += b1;
		CHECK( a1[1]		== 1+10 );
		CHECK( a1[5]		== 5+50 );

	// vector ops
	array<float,2> c1={{1,2}};
	array<float,2> c2={{2,2}};
	array<float,201> c201={};

	// dot prod:  {1,2} x {2,2} = "
	CHECK(	dot_prod(c1,c2) == 6 );

	// norm2: : |{2,2}|
	CHECK(	eq(norm2(c2), 2.82843f) );

	//distance_norm2: : |{1,2}-{2,2}| =
	array<double,2> v1 = {{3., 0.}};
	array<double,2> v2 = {{0., 4.}};
	CHECK(	eq(distance_norm2(v1,v2), 5.));

	////////////////////////////////////////////////////  gsl  convertion
	#ifdef CONVERT_GSl_H
	gsl_vector* gV; // 1st index == 0 
	gV  = gsl_vector_alloc(a0.size()); 
	gV <<= a0; 
	CHECK( gsl_vector_get(gV,0) == a0[0]);
	CHECK( gsl_vector_get(gV,2) == a0[2]);

	b0 <<= gV;
	CHECK( b0[2]== a0[2]);
	CHECK( b0 == a0);

	gV << a1;
	CHECK( gsl_vector_get(gV,0) == a1[1]);
	CHECK( gsl_vector_get(gV,2) == a1[3]);
	CHECK( gsl_vector_get(gV,4) == a1[5]);

	array<int,5,-2> b_m2;
	b_m2 << gV;
	CHECK( b_m2[-2]== a1[1]);
	CHECK( b_m2[2] == a1[5]);
	#endif
	//////////////////////////////////////////////////////

#define CHK(var)	cout << #var << " \t " << &var << " \t " <<  reinterpret_cast<size_t>(&var) % 16 << endl; 

	cout << "SUM: " << c1.sum() << endl;
	cout << "MAX: " << c1.max() << endl;
	cout << "MAX: " << c1.max<sse>() << " \t " << &c1 << "\t addr % 16 = " << (*(size_t *)&c1) % 16 << endl;
	cout << "MAX: " << c2.max<sse>() << " \t " << &c2 << "\t addr % 16 = " << (*(size_t *)&c2) % 16 << endl;
	CHK(c2);

	//PR1((alignment_of<array<int,3>::elem_t>::value));
	//PR1((alignment_of<array<char,1>::elem_t>::value));
	//PR1((alignment_of<array<char,3>::elem_t>::value));
	//PR1((alignment_of<array<float,3>::elem_t>::value));
	//PR1((alignment_of<array<float,3>::elem_align_t>::value));
	//PR1((alignment_of<typeof(c1)>::value));
	CHK(c0);
	CHK(c1);
	CHK(b0);
	array<float,1> f1;  CHK(f1);
	array<char,3> ch3;  CHK(ch3);
	array<float,7> f7;  CHK(f7);
	array<char,1> ch10;  CHK(ch10);
	array<char,1> ch11;  CHK(ch11);
	array<char,1> ch12;  CHK(ch12);
	array<char,1> ch13;  CHK(ch13);
	array<double,1> d1;  CHK(d1);
	array<char,1> ch14;  CHK(ch14);
	array<char,2> ch2;  CHK(ch2);
	array<float,4> f4; 
	CHK(f4);
	CHK(f4[1]);
	CHK(f4[2]);
	CHK(f4[3]);

	CHK(c201);

	typedef int       i4_t[101]; // __attribute__((aligned(16)));
	i4_t	i4;	
	PR1((alignment_of<typeof(i4)>::value));
	CHK(i4);


	cout << (all_pass ? "\n------------ all pass ------------\n" : "\n!!!!!!!!!  SOME FAILED  !!!!!!!!\n");
	exit(all_pass ? 0 : 1);


}

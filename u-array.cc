
#include <iostream>
	using namespace std;

#include <boost/foreach.hpp>

#include <lvv/math.h>
	using lvv::eq;
#include <lvv/array.h>
#include <lvv/lvv.h>
	using lvv::array;

#include <lopti/convert-gsl.h>

#define BOOST_TEST_MODULE lvv_array
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE( lvv_array )  { 

	typedef array<int,5> a5_t;

	// CTOR
	array <int, 5   >       a0 = {{0,1,2,3,4}}; 			// index starts from 0 
		BOOST_CHECK( a0.ibegin()==0);
		BOOST_CHECK( a0.iend()==5);
		BOOST_CHECK( a0.size()==5);
	
	array <int, 5, 1>	a1 = {{1,2,3,4,5}}; 			// index starts from 1
		BOOST_CHECK( a1.ibegin()==1);
		BOOST_CHECK( a1.iend()==6);
		BOOST_CHECK( a1.size()==5);
	array <int, 5, -2>	an = {{-2,-1,0,1,2}}; 			// index starts from -2
		BOOST_CHECK( an.ibegin()==-2);
		BOOST_CHECK( an.iend()==3);
		BOOST_CHECK( an.size()==5);

	array <int, 5, 1> const b1 = {{10,20,30,40,50}}; 			// index starts from 1

	//	cout << "a0: "       << a0 << endl;
	
	////////////////////////////////////////////////////  vector assignment
	// = scalar
	array<int,5,0> b0;
	b0 = 0;
	b0 = 2;
		BOOST_CHECK( b0[0]		== 2 );
		BOOST_CHECK( b0[3]		== 2 );

	// = diffrent type vector
	array<long,5,0> c0;
	c0 = a0;
		BOOST_CHECK( c0[0]		== 0 );
		BOOST_CHECK( c0[3]		== 3 );

	////////////////////////////////////////////////////  vector ops 
	//  array op= scalar : an+10 
	an += 10;
		BOOST_CHECK( *an.begin()	== -2+10 );
		BOOST_CHECK( an[-1]		== -1+10 );
		BOOST_CHECK( an[an.iend()-1]	==  2+10 );

	//  array op= array 
	a1 += b1;
		BOOST_CHECK( a1[1]		== 1+10 );
		BOOST_CHECK( a1[5]		== 5+50 );

	// vector ops
	array<float,2> c1={{1,2}};
	array<float,2> c2={{2,2}};

	// dot prod:  {1,2} x {2,2} = "
	BOOST_CHECK(	dot_prod(c1,c2) == 6 );

	// norm2: : |{2,2}|
	BOOST_CHECK(	eq(norm2(c2), 2.82843f) );

	//distance_norm2: : |{1,2}-{2,2}| =
	array<double,2> v1 = {{3., 0.}};
	array<double,2> v2 = {{0., 4.}};
	BOOST_CHECK(	eq(distance_norm2(v1,v2), 5.));

	////////////////////////////////////////////////////  gsl  convertion
	#ifdef CONVERT_GSl_H
	gsl_vector* gV; // 1st index == 0 
	gV  = gsl_vector_alloc(a0.size()); 
	gV <<= a0; 
	BOOST_CHECK( gsl_vector_get(gV,0) == a0[0]);
	BOOST_CHECK( gsl_vector_get(gV,2) == a0[2]);

	b0 <<= gV;
	BOOST_CHECK( b0[2]== a0[2]);
	BOOST_CHECK( b0 == a0);

	gV << a1;
	BOOST_CHECK( gsl_vector_get(gV,0) == a1[1]);
	BOOST_CHECK( gsl_vector_get(gV,2) == a1[3]);
	BOOST_CHECK( gsl_vector_get(gV,4) == a1[5]);

	array<int,5,-2> b_m2;
	b_m2 << gV;
	BOOST_CHECK( b_m2[-2]== a1[1]);
	BOOST_CHECK( b_m2[2] == a1[5]);
	#endif

}

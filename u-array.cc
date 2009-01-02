
	#define CANUSE_SSE
	#define CANUSE_SSE2
	#define CANUSE_SSE3
	#define GCC_BUG

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
//#include <lopti/convert-gsl.h>
	using namespace std;

                int
main() {

	typedef array<int,5> a5_t;

	cout << " *****  CTOR  *******\n"; //////////////////////////////////////////////////////////////////////
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
	
	{ cout << " *****  VECTOR ASSIGNMENT  *******\n"; ///////////////////////////////////////////////
	// = scalar
	array<short,3,0>	a0s;
	CHECK((a0s=0,	a0s[0]		== 0));
	CHECK((a0s = 9,	a0s.back()	== 9));


	// = diffrent dimentions
	array<int,3,0>		a0i = {{0,1,2}};

	CHECK((a0s=a0i,	a0s[0]		== 0));
	CHECK(( 	a0s.back()	== 2));


	// = diffrent type
	array<float,3,1>	b1f	= {{1.f,2.f,3.f}};
	array<double,3,-1>	bm1d;
	bm1d = b1f;
	CHECKeq(bm1d.front(), 1.f);

	}
	cout << " *****  VECTOR OPS  *******\n"; ///////////////////////////////////////////////
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

	#ifdef CONVERT_GSl_H
	cout << " *****  CONVERT_GSL  *******\n"; ///////////////////////////////////////////////
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



	cout << " *****  SSE ALIGNMENT  *******\n"; ///////////////////////////////////////////////

	//#define CHK(var)	cout << #var << " \t " << &var << " \t " <<  reinterpret_cast<size_t>(&var) % 16 << endl; 
	#define CHK(x)

	#define IS_ALIGN16(var)	((reinterpret_cast<size_t>(&var) % 16) == 0)

	//cout << "SUM: " << c1.sum() << endl;
	//cout << "MAX: " << c1.max() << endl;
	//cout << "MAX: " << c1.max<sse>() << " \t " << &c1 << "\t addr % 16 = " << reinterpret_cast<size_t>(&c1) % 16 << endl;
	//cout << "MAX: " << c2.max<sse>() << " \t " << &c2 << "\t addr % 16 = " << reinterpret_cast<size_t>(&c2) % 16 << endl;
	//CHK(c2);

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

	CHK(c201);   CHECK(IS_ALIGN16(c201)); 

	typedef int       i4_t[101]; // __attribute__((aligned(16)));
	i4_t	i4;	
	CHK(i4);     CHECK(IS_ALIGN16(i4)); 

	cout << " *****  SELECT_METHOD  *******\n"; ///////////////////////////////////////////////
	CHECK(typeid(select_method<double , 2>::type  )  ==  typeid(plain) ) ;
	CHECK(typeid(select_method<double , 200>::type)  ==  typeid(plain) ) ;
	CHECK(typeid(select_method<int8_t , 2>::type  )  ==  typeid(plain) ) ;
	CHECK(typeid(select_method<int8_t , 200>::type)  ==  typeid(plain) ) ;
	CHECK(typeid(select_method<int8_t ,200>::type )  ==  typeid(plain));

	cout << " *****  SSE SPECIALISATION  ******************************************\n"; ///////////////////////////////////////////////

	{		cout << " *****  FLOAT-32  *******\n";
	{  array<float,6> f6 = {{1,2,3,4,5,6}};		CHECK( f6.max() == 6 ); }

	CHECK(typeid(select_method<float  , 2>::type  )  ==  typeid(plain) ) ;
	CHECK(typeid(select_method<float  , 200>::type)  ==  typeid(sse) ) ;
	array<float,3> f3 = {{1,2,3}};
	array<float,10> f10 = {{1,2,3,4,5,6,7,8,9,10}};
	array<float,20> f20 = {{1,2,3,4,5,6,7,8,9,10}};
	#ifdef CANUSE_SSE
	// CHECKeq((f3.max<sse>()),3); 				should trigger static assert
	CHECKeq((f10.max<sse>()),10);
	#endif
	CHECKeq(f20.max(),10);
	
	}

	{		cout << " *****  INT-16  *******\n";
	CHECK(typeid(select_method<int16_t, 2>::type  )  ==  typeid(plain) ) ;
	CHECK(typeid(select_method<int16_t, 200>::type)  ==  typeid(sse2) ) ;
	array<int16_t,3>  h3 = {{1,2,3}};			CHECK(IS_ALIGN16(h3));
	array<int16_t,10> h10 = {{1,2,3,4,5,6,7,8,9,10}};	CHECK(IS_ALIGN16(h10));
	array<int16_t,1000> h1000 = {{1,2,3,4,5,6,7,8,9,10}};	CHECK(IS_ALIGN16(h1000));

	// CHECKeq((f3.max<sse>()),3); 				should trigger static assert
	CHECKeq((h10.max()),10);
	//CHECKeq((h10.max<sse>()),10); 	// should trigger static assert  (sould be: sse2)
	//CHECKeq((h10.max<sse2>()),10);	// assert will fail (no true:  10 > 8*2)

	#ifdef GCC_BUG
	CHECKeq((h1000.max<plain>()),10);
	CHECKeq((h1000.max()),10);
	CHECKeq((h1000.max_impl(sse2(),int16_t())),10);
	CHECKeq((h1000.max<sse2>()),10);
	#endif
	}

	CHECK_EXIT;
}

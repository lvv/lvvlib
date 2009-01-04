
#include <lvv/math.h>
	using lvv::eq;

#include <lvv/lvv.h>

#include <lvv/check.h>
//#include <lopti/convert-gsl.h>
	using namespace std;

#include <lvv/float.h>
	using lvv::floor;
	using lvv::trunc;
                int
main() {


	{		cout << " *****  FLOOR (DOUBLE)  *******\n";
	double d;
	CHECK((d = 0.0,  floor(d) == 0. )) ;
	CHECK((d = 0.2,  floor(d) == 0. )) ;
	CHECK((d = 0.9,  floor(d) == 0. )) ;
	CHECK((d = 1.0,  floor(d) == 1. )) ;
	CHECK((d = 1.1,  floor(d) == 1. )) ;
	CHECK((d = 1.9,  floor(d) == 1. )) ;
	CHECK((d = 99999.2,  floor(d) == 99999.f )) ;

	CHECK((d = -0.0,  floor(d) ==  0. )) ;
	CHECK((d = -0.2,  floor(d) == -1. )) ;
	CHECK((d = -0.9,  floor(d) == -1. )) ;
	CHECK((d = -1.0,  floor(d) == -1. )) ;
	CHECK((d = -1.1,  floor(d) == -2. )) ;
	CHECK((d = -1.9,  floor(d) == -2. )) ;
	CHECK((d = -12345.2,  floor(d) == -12346.f )) ;
	}

	{		cout << " *****  FLOOR (FLOAT)  *******\n";
	float f;
	CHECK((f = 0.0,  floor(f) == 0.f )) ;
	CHECK((f = 0.2,  floor(f) == 0.f )) ;
	CHECK((f = 0.9,  floor(f) == 0.f )) ;
	CHECK((f = 1.0,  floor(f) == 1.f )) ;
	CHECK((f = 1.1,  floor(f) == 1.f )) ;
	CHECK((f = 1.9,  floor(f) == 1.f )) ;
	CHECK((f = 99999.2,  floor(f) == 99999.f )) ;

	CHECK((f = -0.0,  floor(f) == 0.f )) ;
	CHECK((f = -0.2,  floor(f) == -1.f )) ;
	CHECK((f = -0.9,  floor(f) == -1.f )) ;
	CHECK((f = -1.0,  floor(f) == -1.f )) ;
	CHECK((f = -1.1,  floor(f) == -2.f )) ;
	CHECK((f = -1.9,  floor(f) == -2.f )) ;
	CHECK((f = -12345.2,  floor(f) == -12346.f )) ;
	}

	{		cout << " *****  TRUNC (FLOAT)  *******\n";
	float f;
	CHECK((f = 0.0     , trunc(f) == 0.f     ) ) ;
	CHECK((f = 0.2     , trunc(f) == 0.f     ) ) ;
	CHECK((f = 0.9     , trunc(f) == 0.f     ) ) ;
	CHECK((f = 1.0     , trunc(f) == 1.f     ) ) ;
	CHECK((f = 1.1     , trunc(f) == 1.f     ) ) ;
	CHECK((f = 1.9     , trunc(f) == 1.f     ) ) ;
	CHECK((f = 99999.2 , trunc(f) == 99999.f ) ) ;
	CHECK((f = -0.0    , trunc(f) == 0.f     ) ) ;
	CHECK((f = -0.2    , trunc(f) == -0.f    ) ) ;
	CHECK((f = -0.9    , trunc(f) == -0.f    ) ) ;
	CHECK((f = -1.0    , trunc(f) == -1.f    ) ) ;
	CHECK((f = -1.1    , trunc(f) == -1.f    ) ) ;
	CHECK((f = -1.9    , trunc(f) == -1.f    ) ) ;
	CHECK((f = -12345.2, trunc(f) == -12345.f) ) ;
	}

	CHECK_EXIT;
}
	/*
	#include <iostream>
	using namespace std;
	using namespace lvv;
	
int main () {

	float f;
	f = 0   ; cout << f << "->" << f - fme + fm -fm << endl;
	f = 0.2 ; cout << f << "->" << f - fme + fm -fm << endl;
	f = 0.9 ; cout << f << "->" << f - fme + fm -fm << endl;
	f = 1.8 ; cout << f << "->" << f - fme + fm -fm << endl;
	f = -0.2; cout << f << "->" << f - fme + fm -fm << endl;
	f = -1.2; cout << f << "->" << f - fme + fm -fm << endl;
	f = -1.9; cout << f << "->" << f - fme + fm -fm << endl;

	double d;
	d=0; cout << d << " -> " << d - dme + dm -dm << endl;
	d=0.2; cout << d << " -> " << d - dme + dm -dm << endl;
	d=0.9; cout << d << " -> " << d - dme + dm -dm << endl;
	d=1.8; cout << d << " -> " << d - dme + dm -dm << endl;
	d=-0.2; cout << d << " -> " << d - dme + dm -dm << endl;
	d=-1.2; cout << d << " -> " << d - dme + dm -dm << endl;
	d=-1.9; cout << d << " -> " << d - dme + dm -dm << endl;
}*/

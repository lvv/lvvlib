						#ifndef LVV_FLOAT_H
						#define LVV_FLOAT_H
						namespace lvv {

	////////////////////////////////////////////////////////////////////////////////////   FLOOR
	
	// floor(float)
	const float	fm 	= 0x1.0p23f*1.5f+1;	// 2^52 * 1.5,  uses limited precisicion to floor
	const float	fmd	= 1.5e-8;		// .5f + 1e^(number of exp bit)
	const float	fme	= .5f-fmd;		// .5f - 1e^(number of exp bit)

	float static 		floor(float x)	{ return x - fme + fm - fm; }
	float static 		trunc(float x)	{ return x  + 0x1.0p23f - 0x1.0p23f; }

	// floor(double)
	const double	dm 	= 6755399441055744.0;	//2^52 * 1.5,  uses limited precisicion to floor
	const double	dmd	= 1.5e-8;		//almost .5f = .5f + 1e^(number of exp bit)
	const double	dme	= .5f-dmd;		//almost .5f = .5f - 1e^(number of exp bit)

	double static 		floor(double x)	{ return x - dme + dm - dm; }

	////////////////////////////////////////////////////////////////////////////////////   INTEGER --> FP
	
	const double	 _double2fixmagic = 68719476736.0*1.5;     //2^36 * 1.5,  (52-_shiftamt=36) uses limited precisicion to floor
	const int32	_shiftamt        = 16;                    //16.16 fixed point representation,

	#if BigEndian_
		#define iexp_				0
		#define iman_				1
	#else
		#define iexp_				1
		#define iman_				0
	#endif 

	inline int32 double2int(double val) {
		val		= val + _double2fixmagic;
		return ((int32*)&val)[iman_] >> _shiftamt; 
	}

	inline int32 float2int(double val) { return (float) doulbe2int(val); }

					    }
					    #endif // LVV_MATH_H

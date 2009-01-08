						#ifndef LVV_FLOAT_H
						#define LVV_FLOAT_H
						namespace lvv {

	// TR floating point utils:  http://www.codeproject.com/KB/cpp/floatutils.aspx

//////////////////////////////////////////////////////////////////////////////////////////////  IEEE FLOATING POINT
	template<typename T, long M=0, long E=1>	struct 	fp {
		T const static value =  M *  (E > 0 ?  ipow<10,E>::value : ( E < 0 ?  T(1)/T(ipow<10,-E>::value) : 1) );
	};

	template<>		struct 	fp<float>	{
		enum {
			mantissa_size	= 23,
			mantissa_mask	= 0x7FFFFF,
			exponent_size	= 8, 
			sign_mask	= 0x80000000
		};
		typedef		uint32_t	uint_t;
		float static const	      one_ulp_magic	=  0x1.0p23f;
		float static const	floor_one_ulp_magic	=  0x1.0p23f*1.5f+1;
	};

	template<>		struct 	fp<double>	{
		enum {
			mantissa_size	= 52,
			exponent_size	= -1
		};
		typedef		uint64_t	uint_t;
		uint64_t static const	mantissa_mask	= (~(~1L<<52));
		uint64_t static const	sign_mask	= 0x8000000000000000;
		float static const	one_ulp_magic	= 6755399441055744.0;	//2^52 * 1.5
	};

////////////////////////////////////////////////////////////////////////////////////   TODO ABS
	/* make x = abs(x) */
	// TO TRY:  *(((int *) &x) + 1) &= 0x7fffffff;
	//
////////////////////////////////////////////////////////////////////////////////////   TODO COMPARE
	//  FROM http://aggregate.org/MAGIC/#Absolute%20Value%20of%20a%20Float
	//  #define FasI(f)  (*((int *) &(f)))
	//  #define FasUI(f) (*((unsigned int *) &(f)))
	//
	//  #define	lt0(f)	(FasUI(f) > 0x80000000U)
	//  #define	le0(f)	(FasI(f) <= 0)
	//  #define	gt0(f)	(FasI(f) > 0)
	//  #define	ge0(f)	(FasUI(f) <= 0x80000000U)
	//
	
////////////////////////////////////////////////////////////////////////////////////   TODO RECIPROCAL
	// This is about 2.12 times faster than using 1.0f / n
	//
	// r = 1/p
	/*
	 #define FP_INV(r,p) 	{ \
			int _i = 2 * 0x3F800000 - *(int *)&(p); \
			(r) = *(float *)&_i; \
			(r) = (r) * (2.0f - (p) * (r)); \
		}
	*/
	
////////////////////////////////////////////////////////////////////////////////////   FLOOR
	
	// floor(float)
	const float	fm 	= 0x1.0p23f*1.5f+1;	// 2^52 * 1.5,  uses limited precisicion to floor
	const float	fmd	= 1.5e-8;		// .5f + 1e^(number of exp bit)
	const float	fme	= .5f-fmd;		// .5f - 1e^(number of exp bit)

	float static inline	floor(float x)	{ return x - fme + fm - fm; }
	float static inline	trunc(float x)	{ return x  + 0x1.0p23f - 0x1.0p23f; }

	// floor(double)
	const double	dm 	= 6755399441055744.0;	//2^52 * 1.5,  uses limited precisicion to floor
	const double	dmd	= 1.5e-8;		//almost .5f = .5f + 1e^(number of exp bit)
	const double	dme	= .5f-dmd;		//almost .5f = .5f - 1e^(number of exp bit)

	double static inline	floor(double x)	{ return x - dme + dm - dm; }

////////////////////////////////////////////////////////////////////////////////////   INTEGER --> FP
	
	/*
	const double	 _double2fixmagic = 68719476736.0*1.5;     //2^36 * 1.5,  (52-_shiftamt=36) uses limited precisicion to floor
	//const int32	_shiftamt        = 16;                    //16.16 fixed point representation,

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
	*/

					    }
					    #endif // LVV_MATH_H

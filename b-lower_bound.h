
	const static unsigned long	N = 	10000;
	const float test_step = 0.2f;
	////////////   CREATE ARRAY
	//TYPE volatile  A[N];
	cout << "type: " << typeid(TYPE).name() << setprecision(10) << endl;

	array<TYPE, N,1> A; for (size_t i=A.ibg; i<A.ien; i++) { A[i]  =float(i); }

cout << "*** COMPARE  type:"  << typeid(TYPE).name() << endl;

for (int r=0; r<REPEAT; r++) {
	TYPE s=0;
	for (TYPE val=A.ibg+1; val<A.ien-1; val+=test_step) {
		s += *std::lower_bound(A.begin(), A.end(), val);  
		//PR3(val, *std::lower_bound(A.begin(), A.end(), val), std::lower_bound(A.begin(), A.end(), val));  
	}
	PRINT("std::lower_bound()	", s );
}


for (int r=0; r<REPEAT; r++) {
	TYPE s=0;
	for (TYPE val=A.ibg+1; val<A.ien-1; val+=test_step) {
		int	len = A.size();
		int	half;
		TYPE*	middle;
		TYPE*   first = A.begin();

		while (len > 0) {                                                                                                                                                 
		    half = len >> 1;
		    middle = first + half;
		    if (*middle < val) {
			first = middle;
			++first;
			len = len - half - 1;
		    }
		    else
		     	len = half;
		}

		s +=  *first;	// found result
	}
	PRINT("loop	", s );
}

for (int r=0; r<REPEAT; r++) {
	TYPE   s=0;
	TYPE   step = 1.0f;
	TYPE   dx;
	for (TYPE val=A.ibg+1; val<A.ien-1; val+=test_step) {
				assert(val >= A.ibg);
				assert(val <= A.ien+1);
		dx= val - A.front();
		int im = dx / step;
		s +=  A[A.ibg + im +1];
			//PR2(val, A[A.ibg+im+1]);  
	}
	PRINT("math	", s );
}


/*
	while (__len > 0) {                                                                                                                                                 
	    __half = __len >> 1;
	    __middle = __first;
	    std::advance(__middle, __half);
	    if (*__middle < __val)
	      {
	        __first = __middle;
	        ++__first;
	        __len = __len - __half - 1;
	      }
	    else
	      __len = __half;
	}
	return __first;
*/

//for (size_t r=0; r<REPEAT; r++) { PRINT("max<sse>:", A.max<sse>() ); }


#ifndef  CONVERT_CONDOR_H
#define  CONVERT_CONDOR_H

	#include <condor/Vector.h>
	
			template <typename T, int N, int B>
			array<T,N,B>&
	operator<<  (array<T,N,B>& A, CONDOR::Vector& cV)  {        // operator= should be member, so we are using operator<<
								assert(A.size()==cV.sz());  assert(A.ibegin()==0);  
		for (int i=A.ibegin(); i<A.iend(); i++)    A[i] = cV[i];
		return A;
	 };

			template <typename T, int N, int B>
			CONDOR::Vector&
	 operator<<  (CONDOR::Vector& cV, const array<T,N,B>& A)  {
		cV.setSize(A.size());				assert(A.size()==cV.sz());  assert(A.ibegin()==0);  
		for (int i=A.ibegin(); i<A.iend(); i++)    cV[i] = A[i];
		return cV;
	 };
#endif

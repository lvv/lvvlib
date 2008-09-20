 /************************************************************************
 *      function HJMIN - find local minimum of a given function
 *	   	        by the Hook-Jeevse method
 *
 * Input
 *	double hjmin(b,h0,funct)
 *	VECTOR b 			On input contains the initial
 *					guess to the minimum location
 *					On return has the vector
 *					specifying for the minimum location
 *	const VECTOR h0			Initial values for the steps along
 *					each directions
 *	double f(const VECTOR x)	Procedure to compute a function
 *					value at the specified point
 *
 * Output
 *	Hjmin returns the function value at the point of minimum
 *
 * Algorithm
 *	Hook-Jeevse method of direct search for a function minimum
 *	The method is of the 0. order (i.e. requiring no gradient computation)
 *	See
 *	B.Bondi. Methods of optimization. An Introduction - M.,
 *	"Radio i sviaz", 1988 - 127 p. (in Russian)
 *	
 *
 * Notes
 *	static VECTORs h and bas are used as work arrays. They are not
 *	destroyed (freed) on exit so that next call to Hjmin could use
 *	them if they are still appropriate for that call.
 *
 ************************************************************************/
 


	#include <cassert>
	#include <algorithm>
	#include <iterator>
		using namespace std;

	#include <lvv/array.h>
		using namespace lvv;
		using lvv::array;
	//#include <lvv/math.h>
	//using lvv::powi;

					// Examine the function f in the vicinity of the bas point
					// by making tentative steps fro/back along the every coordinate.
					// When the function is found to decrease, the point bas is correspondingly
					// updated. Examination() returns the minimal function value found in
					// the investigated region.

			template<typename vector_t> 
class hook_jeevs_min   { public: 

double min		(vector_t&  b, const vector_t& h0,   double  (*ff) (const  vector_t&))  {
	double  f_min;				   // Min function value found     

	// beforehand                   

	#define  EPSILON 0.000001
	const double	tau = 10 * EPSILON;	   // Termination criterium        
	const double	threshold = 1e-8;		   // Threshold for the function   

	// decay to be treated as significant                  
	const double	step_reduce_factor = 10;

	f   = ff;
	h   = h0;
	bas = b ;
	f_bas = f_min = (*f) (b);


	for (;;) {										   // Main iteration loop                            // b is a next approximation to min             
		if (examination() < f_min - threshold) {					   // Function falled markedly     
			do {									   // Perform search on pattern      // bas - pattern, b - new min appr 
				typename vector_t::iterator  pbas =  bas.begin();
				typename vector_t::iterator  pmin =  b.begin();

				for (int i = bas.ibegin();  i < bas.iend();  i++) {
					 double t = (*pbas - *pmin) + *pbas;

					*pmin++ = *pbas;
					*pbas++ = t;
				}
				f_min = f_bas;
				f_bas = (*f) (bas);
			}	while (examination() < f_min - threshold);	// Continue search until f doesn't  decrease         

			bas = b;
			f_bas = f_min;						// Save the best approx found   

		} else {							// Function didn't fall markedly 
			// upon examination near bas    
			int success = 1;					// Try to reduce the step       
			typename vector_t::iterator	ph   =  h.begin();
			typename vector_t::iterator	pbas =  bas.begin();

			for (int i = h.ibegin();  i < h.iend();  i++) {
				*ph /= step_reduce_factor;
				success &= (*ph++ / (1 + fabs(*pbas++)) < tau);
			}

			if (success) return f_min;
		}

	}
 }

  private:

	vector_t	 h;				//  Steps along axes        
	vector_t	 bas;				//  Base point              
	double		f_bas;				//  Function value at it    
	double		(*f) (const vector_t& X);	//  Function being minimized

double examination() {

	for (int  i = bas.ibegin();  i < bas.iend(); i++) {	// Perform step along a coordinate              
		 double basi_old = bas[i];		   // Old coordinate value         
		 double f_new;

		bas[i] = basi_old + h[i];
		f_new = (*f) (bas); 

		if	(f_new < f_bas)  {
			f_bas = f_new;								// Step caused f to decrease, OK 
		} else {
			bas[i] = basi_old - h[i];
			f_new = (*f) (bas); 
			if (f_new < f_bas) f_bas = f_new;
			else               bas[i] = basi_old;					 // No fall was found along this coord 
		}
	}
	return f_bas;
 }


 }; // class 

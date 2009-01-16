#include <iostream>
#include <cmath>
		template<typename T,int N>
	struct S {
		//volatile float f=1.00001f;
		T eval(T x) {
			//volatile unsigned n = 11;
			//return std::pow(x,N);
			return  ((x*x)*(x*x))*((x*x)*(x*x))*((x*x)*(x*x))*(x*x)/N  + x/N;
		}
	};

int main() {
	
	volatile float vf = 1.00001f;
	float f = vf;
	//S<float,10> s;
	//std::cout << s.eval(f);
	std::cout << (f*f)*(f*f);
}

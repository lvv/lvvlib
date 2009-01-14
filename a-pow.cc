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
	
	volatile float f = 1.00001f;
	S<float,10> s;
	std::cout << s.eval(f);
}

#include <lvv/check.h>
	using namespace lvv;

int main() {
	// Check basic math
	CHECK(1+2	== 3);		// eval expression;
	CHECK(2*2	== 4);		// prints pass/fail, line-number and expression
	CHECK(1/2	== 0.5);
	CHECK(4-2	== 2);

	CHECK_EXIT;			// prints failure if any test fails, success otherwise
}

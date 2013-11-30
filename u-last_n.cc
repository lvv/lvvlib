
#include <lvv/last_n.h>
#include <lvv/check.h>

int main() {

	last_n<int,3> last;
	for (int i=1; i<5; ++i)  { last.push_back(i);  /*__ i, last.ring;*/ };

	CHECK_ARE_EQUAL(last.prev(0), 4);
	CHECK_ARE_EQUAL(last.prev(1), 3);
	CHECK_ARE_EQUAL(last.prev(2), 2);

	CHECK_EXIT;
}

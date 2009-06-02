#include <iostream>
#include <lvv/timer.h>


int main () {

	for (int i = 100000; i <= 200000; ++i)
		lvv::progress_dots(i,100000,200000, "progress: ");
}
// vim:nu:

#include <iostream>
#include <lvv/lvv.h>


int main () {

     for (int i = 100000; i <= 200000; ++i)
        progress_dots(i,100000,200000, "progress: ");
}
// vim:nu:

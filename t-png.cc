#include <lvv/png.h>
#include <lvv/array.h>

int main   (int argc, char **argv) {
        if (argc != 2) abort_("Usage: program_name  <file_out>");

	const int W = 200; 
	const int H = 200; 
	const int CH = 4; 
	lvv::array<uint8_t, W*H*CH>  A;
	A = 255;
	for (int r = 0;   r<H;  r++)   {
		A[r*W*CH + r*CH+0] = 0;
		A[r*W*CH + r*CH+1] = 0;
		A[r*W*CH + r*CH+2] = 0;
	}
	
        array2png <H,W,CH>  (argv[1], &A[0]);
}

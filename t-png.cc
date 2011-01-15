#include <lvv/png.h>
#include <lvv/array.h>
using namespace lvv;

int main() {

	const int W = 200; 
	const int H = 200; 

	// A:  lvv::array
	{
	const int CH = 3;

		array<array<array<uint8_t,CH>,W>,H>	A;   A = 255;
		for (int r = 0;   r<H;  r++)      A[r][r] = 0;
		array2png ("t-a.png", A);
	}


	// B:  C-array 
	{
	const int CH = 3;

		array<uint8_t, W*H*CH>  B; B = 255;
		for (int r = 0;   r<H;  r++)   {
			B[r*W*CH + r*CH+0] = 0;
			B[r*W*CH + r*CH+1] = 0;
			B[r*W*CH + r*CH+2] = 0;
		}
		array2png <H,W,CH,PNG_COLOR_TYPE_RGB>  ("t-b.png", &B[0]);
	}
}

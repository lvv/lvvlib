#ifndef  LVV_PNG_H
#define  LVV_PNG_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
//#include <string.h>
#include <stdarg.h>
#include <stdint.h>

#include <png.h>


    namespace lvv {

		static void abort_(const char * s, ...) {
			va_list args;
			va_start(args, s);
			vfprintf(stderr, s, args);
			fprintf(stderr, "\n");
			va_end(args);
			abort();
		};

			

	template <int height, int width, int channel=4>  static
void array2png (char* file_name, uint8_t* A) {

		png_byte color_type = PNG_COLOR_TYPE_RGB_ALPHA;
		png_byte bit_depth = 8;

		png_structp png_ptr;
		png_infop info_ptr;

        /* create file */
        FILE *fp = fopen(file_name, "wb");
				if (!fp) abort_("[write_png_file] File %s could not be opened for writing", file_name);

        /* initialize stuff */
        png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
				if (!png_ptr) abort_("[write_png_file] png_create_write_struct failed");
        info_ptr = png_create_info_struct(png_ptr);
				if (!info_ptr) abort_("[write_png_file] png_create_info_struct failed");
				if (setjmp(png_jmpbuf(png_ptr))) abort_("[write_png_file] Error during init_io");
        png_init_io(png_ptr, fp);

	/* write header */
				if (setjmp(png_jmpbuf(png_ptr))) abort_("[write_png_file] Error during writing header");
        png_set_IHDR (png_ptr, info_ptr, width, height, bit_depth, color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
        png_write_info(png_ptr, info_ptr);

	// fill AP
	png_bytep AP[height];
	for (int r = 0;   r<height;  r++) 
		AP[r] = A + width*channel*r;


        /* write bytes */
				if (setjmp(png_jmpbuf(png_ptr))) abort_("[write_png_file] Error during writing bytes");
        png_write_image(png_ptr, AP);

        /* end write */
				if (setjmp(png_jmpbuf(png_ptr))) abort_("[write_png_file] Error during end of write");
        png_write_end(png_ptr, NULL);

        fclose(fp);
}



 };  // namespace lvv
    #endif // LVV_H

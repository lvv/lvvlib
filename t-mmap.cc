// Demonstrates how to use mmap
//
// Copyright (c) Michael Still 2004, released under the terms of the GNU GPL

#include <iostream>
using  namespace std;

#include "../lvv/mmap.h"
using lvv::mmap_read;
using lvv::mmap_write;


int main(int argc, char *argv[]) {

	// int
	int i=1;
	int ii=0;
	mmap_write("_i.mmap", i, sizeof(i));
	ii = *(int*)mmap_read("_i.mmap");
		cout << "ii=" << ii << endl;

	// array
	float f[3]={1.11, 2.22, 3.33};
	float *ff;
	mmap_write("_fa.mmap", *f, sizeof(f[0])*3);
	ff = (float*)mmap_read("_fa.mmap");
		cout << "ff[0]=" << ff[0] << endl;
		cout << "ff[1]=" << ff[1] << endl;
		cout << "ff[2]=" << ff[2] << endl;
}

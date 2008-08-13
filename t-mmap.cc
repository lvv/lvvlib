// Demonstrates how to use mmap
//
// Copyright (c) Michael Still 2004, released under the terms of the GNU GPL

#include <iostream>
using  namespace std;

#include "../lvv/mmap.h"
using lvv::mmap_read;
using lvv::mmap_write;


int main(int argc, char *argv[]) {

	int i=1;
	int ii=0;
	mmap_write("_i.mmap", i, sizeof(i));
	ii = *(int*)mmap_read("_i.mmap");
	cout << "ii=" << ii << endl;
}

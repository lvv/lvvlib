// Demonstrates how to use mmap
//
// Copyright (c) Michael Still 2004, released under the terms of the GNU GPL

#include <iostream>
using  namespace std;

#include <lvv/array.h>
using lvv::array;

#include <lvv/mmap.h>
using namespace lvv;
using lvv::mmap_read;
using lvv::mmap_write;


int main(int argc, char *argv[]) {

	cout  << "\n\n   *** int  write, read  ***   \n";
	int i=1;
	                mmap_write<int> ("/tmp/_i.mmap", i);
	int ii = *(int*)mmap_read       ("/tmp/_i.mmap");	// traditional  void * 
	int iii =       mmap_read<int>  ("/tmp/_i.mmap"); 	// templated ref
	cout << "ii="  << ii  << endl;
	cout << "iii=" << iii << endl;


	cout  << "\n\n   *** flat plain-array write, read  *** \n";
	float f[3]={1.11, 2.22, 3.33};
	mmap_write("/tmp/_fa.mmap", *f, sizeof(f[0])*3);


	float *ff, *fff;
	//ff = (float*)mmap_read("/tmp/_fa.mmap", MAP_PRIVATE);
	ff = (float*)mmap_read("/tmp/_fa.mmap");
		cout << "ff[0]=" << ff[0] << endl;
		cout << "ff[1]=" << ff[1] << endl;
		cout << "ff[2]=" << ff[2] << endl;

	//ff[1] = 11;     cout << "can modify _fa map "  << endl;

	cout << "\n\n   *** double lvv::array write, read ***  \n";
	typedef array<double, 3> array_t;
	array_t  d={{0.11, 0.22, 0.33}};
	mmap_write<array_t> ("/tmp/_da.mmap", d); 	// size is taken from array_t 
	array_t&  dd = mmap_read<array_t> ("/tmp/_da.mmap"); 
	cout << "array<double,3> d   " << d ;

	return 0;
}

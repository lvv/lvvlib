
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
	size_t n;
	                mmap_write<int> ("/tmp/_i.mmap", i);
	int ii = *(int*)mmap_read_ptr   ("/tmp/_i.mmap", n);	// traditional  void * 
	int iii =       mmap_read<int>  ("/tmp/_i.mmap"); 	// templated ref
	cout << "ii="  << ii  << endl;
	cout << "iii=" << iii << endl;


	cout  << "\n\n   *** flat plain-array write, read  *** \n";
	float f[3]={1.11, 2.22, 3.33};
	mmap_write("/tmp/_fa.mmap", f);


	float *F;
	F = mmap_read<float>("/tmp/_fa.mmap",n);
	
	for (size_t i=0;  i<n;  ++i) {
		cout << F[i] << ' ';
	};  
	cout << "   n=" << n << endl;


	//ff[1] = 11;     cout << "can modify _fa map "  << endl;

	cout << "\n\n   *** double lvv::array ***  \n";
	typedef lvv::array<double, 3> array_t;
	array_t  d={{0.11, 0.22, 0.33}};
	mmap_write<array_t> ("/tmp/_da.mmap", d); 	// size is taken from array_t 
	array_t&  dd = mmap_read<array_t> ("/tmp/_da.mmap"); 
	cout << "array<double,3> d  =" << d  << endl;
	cout << "array<double,3> dd =" << dd  << endl;

	////////////////////////////////////////////////// PART OF VECTOR<CHAR>
	
	{
	cout << "\n\n   *** vector char ***  \n";
	vector<char> A={'a','b','c','d'};
	mmap_write("/tmp/vector_char.mmap", *(A.data()),2);


	char *B;
	size_t B_size;
	B = mmap_read<char>("/tmp/vector_char.mmap",B_size);
	
	for (size_t i=0;  i<B_size;  ++i) {
		cout << B[i] << ' ';
	};  
	cout << "   B_size=" << B_size << endl;
	}
}

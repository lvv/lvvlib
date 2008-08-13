// Demonstrates how to use mmap
//
// Copyright (c) Michael Still 2004, released under the terms of the GNU GPL

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

#include <cstdlib>
#include <iostream>
using namespace std;

#include "lvv.h"
using namespace lvv;

void * mmap_read(char *name) {
	int 	src_fd = open(name, O_RDONLY);

	if (src_fd  < 0) {
		cerr  << "mmap_read error: couldn't open  \"" << name << "\"  file\n";
		exit(1);
	}
	
	struct stat sb;
	if (fstat(src_fd, &sb) < 0) {
		cerr << "mmap_read error: couldn't stat  \"" << name << "\"   file\n";
		close(src_fd);
		exit(3);
	}

	void *p =  mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, src_fd, 0);
	if  ( p == MAP_FAILED ) {
		cerr  << "mmap_read error: couldn't mmap  \"" << name << "\"  file\n";
		close(src_fd);
		exit(5);
	}

	return p;
}

			template<typename T>
void	mmap_write(char* name, T &obj, size_t size) {
	int	trg_fd = open(name, O_CREAT | O_RDWR, S_IRWXU);
	if (trg_fd  < 0) {
		cerr  << "mmap_write error: couldn't open  \"" << name << "\"  file\n";
		exit(2);
	}

	if (ftruncate(trg_fd, size) < 0) {
		cerr << "mmap_write error: couldn't allocate space for  \"" << name << "\" file\n";
		close(trg_fd);
		exit(4);
	}


	void *p = mmap(NULL, size, PROT_WRITE, MAP_SHARED, trg_fd, 0);
	if ( p == MAP_FAILED ) {
		cerr << "mmap_write error: couldn't mmap \"" << name << "\" file\n";
		close(trg_fd);
		exit(6);
	}

	/*	MAP_FIXED
	Don’t  interpret  addr  as  a hint: place the mapping at exactly that address.  addr must be a multiple of the page size.  If the
       	memory region specified by addr and len overlaps pages of any existing mapping(s), then the overlapped part of the existing  map‐
       	ping(s)  will  be discarded.  If the specified address cannot be used, mmap() will fail.  Because requiring a fixed address for a
       	mapping is less portable, the use of this option is discouraged. */

	if (memcpy(p, &obj, size) < 0) {
		cerr << "mmap_write error: couldn't memcpy() for \"" << name << "\" file\n";
		close(trg_fd);
		exit(8);
	}

	if (munmap(p, size) < 0) {
		cerr << "mmap_write error: couldn't munmap() for \"" << name << "\" file\n";
		close(trg_fd);
		exit(10);
	}
}

int main(int argc, char *argv[]) {

	int i=1;
	int ii=0;
	mmap_write("_i.mmap", i, sizeof(i));
	ii = *(int*)mmap_read("_i.mmap");
	PR1(ii);
}

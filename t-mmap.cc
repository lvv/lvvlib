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
#include <iostream>
using namespace std;


int main(int argc, char *argv[]) {
	int     src_fd, trg_fd;
	char   *src_file, *trg_file;
	struct stat sb;

	if ((src_fd = open(argv[1], O_RDONLY)) < 0) {
		printf("Backing store: couldn't open the src_ file\n");
		return 0;
	}

	trg_fd = open(argv[2], O_CREAT | O_RDWR, S_IRWXU);
	if (trg_fd  < 0) {
		printf("Backing store: couldn't open the trg_ file\n");
		close(src_fd);
		return 0;
	}

	if (fstat(src_fd, &sb) < 0) {
		cerr << "output: couldn't stat the src_ file\n";
		close(src_fd);
		close(trg_fd);
		return 0;
	}

	if (ftruncate(trg_fd, sb.st_size) < 0) {
		printf("output: couldn't allocate space for trg_ data\n");
		close(src_fd);
		close(trg_fd);
		return 0;
	}

	src_file = (char *) mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, src_fd, 0);
	if (src_file  == MAP_FAILED) {
		printf("output: couldn't mmap the src_ file\n");
		close(src_fd);
		close(trg_fd);
		return 0;
	}

	trg_file = (char *) mmap(NULL, sb.st_size, PROT_WRITE, MAP_SHARED, trg_fd, 0);
	if ( trg_file == MAP_FAILED ) {
		printf("output: couldn't mmap the trg_ file\n");
		close(src_fd);
		close(trg_fd);
		return 0;
	}

	if (memcpy(trg_file, src_file, sb.st_size) < 0) {
		printf("output: copy failed\n");
		close(src_fd);
		close(trg_fd);
		return 0;
	}

	if (munmap(src_file, sb.st_size) < 0) {
		printf("output: couldn't munmap the src_ file\n");
		close(src_fd);
		close(trg_fd);
		return 0;
	}

	if (munmap(trg_file, sb.st_size) < 0) {
		printf("output: couldn't munmap the trg_ file\n");
		close(src_fd);
		close(trg_fd);
		return 0;
	}

	close(src_fd);
	close(trg_fd);
}

// mmap(2) wrapper
// Part of lvvlib - https://github.com/lvv/lvvlib
// Copyright (c) 2000-2013
// Leonid Volnitsky (Leonid@Volnitsky.com)


	#include <string.h>
	#include <errno.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <sys/mman.h>
	#include <unistd.h>
	#include <fcntl.h>

	#include <cstdlib>
	#include <iostream>
	#include <stdexcept>
	using  std::cerr;
	namespace lvv {

	struct  no_file: std::exception {};
	struct  no_free_space: std::exception {};
	struct  open_error: std::exception {};
	struct  io_error: std::exception {};

template<int SHARING=MAP_PRIVATE> void * mmap_read_ptr  (const char *path, size_t& n)   {

	int 	src_fd = open(path, O_RDWR);

	if (src_fd  < 0) {
		cerr  << "mmap_read error: couldn't open  \"" << path << "\"  file\n";
		throw no_file();
	}
	
	struct stat sb;

	// get file size
	if (fstat(src_fd, &sb) < 0) {
		cerr << "mmap_read error: couldn't stat  \"" << path << "\"   file\n";
		close(src_fd);
		throw io_error();
	}

	n = sb.st_size;

	void *p =  mmap(NULL, n, PROT_READ | PROT_WRITE , SHARING, src_fd, 0);
	//void *p =  mmap(NULL, sb.st_size , PROT_READ, SHARING, src_fd, 0);

	if  ( p == MAP_FAILED ) {
		cerr  << "mmap_read error: couldn't mmap  \"" << path << "\"  file\n";
		close(src_fd);
		throw io_error();
	}

	return p;
 }

template<typename MMAPED_TYPE, int SHARING=MAP_SHARED>    MMAPED_TYPE&   mmap_read(const char* path)               {
	size_t unused;   
	return  *(MMAPED_TYPE*) mmap_read_ptr<SHARING>(path, unused);
 };

template<typename REC_T,       int SHARING=MAP_SHARED>    REC_T*         mmap_read(const char* path, size_t& n)    {
	size_t n_bytes;  
	auto res =  (REC_T*)       mmap_read_ptr<SHARING>(path, n_bytes);
	n = n_bytes/sizeof(REC_T);
	return res;
 };


template<typename T> void	mmap_write(const char* path, T &obj) {	// write an object

	size_t size=sizeof(T);
	unlink(path);

	int	trg_fd = open(path, O_CREAT | O_RDWR, S_IRWXU);
	if (trg_fd  < 0) {
		cerr  << "mmap_write error: couldn't open  \"" << path << "\"  file\n";
		//exit(2);
		throw open_error();
	}

	if (ftruncate(trg_fd, size) < 0) {
		cerr << "mmap_write error: couldn't allocate space for  \"" << path << "\" file\n";
		close(trg_fd);
		//exit(4);
		throw no_free_space();
	}


	void *p = mmap(NULL, size, PROT_WRITE, MAP_SHARED, trg_fd, 0);
	if ( p == MAP_FAILED ) {
		cerr << "mmap_write error: couldn't mmap \"" << path << "\" file\n";
		close(trg_fd);
		//exit(6);
		throw io_error();
	}

	/*	MAP_FIXED
	Don’t  interpret  addr  as  a hint: place the mapping at exactly that address.  addr must be a multiple of the page size.  If the
       	memory region specified by addr and len overlaps pages of any existing mapping(s), then the overlapped part of the existing  map‐
       	ping(s)  will  be discarded.  If the specified address cannot be used, mmap() will fail.  Because requiring a fixed address for a
       	mapping is less portable, the use of this option is discouraged. */

	if (memcpy(p, &obj, size) < 0) {
		cerr << "mmap_write error: couldn't memcpy() for \"" << path << "\" file\n";
		close(trg_fd);
		//exit(8);
		throw std::exception();
	}

	if (munmap(p, size) < 0) {
		cerr << "mmap_write error: couldn't munmap() for \"" << path << "\" file\n";
		close(trg_fd);
		//exit(10);
		throw std::exception();
	}
 }

template<typename REC_T> void	mmap_write(const char* path, REC_T* rec, size_t n) {	// wirte array REC_t[n]

	size_t  size  = n * sizeof(REC_T);

	unlink(path);

	int	trg_fd = open(path, O_CREAT | O_RDWR, S_IRWXU);
	if (trg_fd  < 0) {
		cerr  << "mmap_write error: couldn't open  \"" << path << "\"  file\n";
		throw open_error();
	}

	if (ftruncate(trg_fd, size) < 0) {
		cerr << "mmap_write error: couldn't allocate space for  \"" << path << "\" file\n";
		close(trg_fd);
		throw no_free_space();
	}


	void *p = mmap(NULL, size, PROT_WRITE, MAP_SHARED, trg_fd, 0);
	if ( p == MAP_FAILED ) {
		cerr << "mmap_write error: couldn't mmap \"" << path << "\" file\n";
		close(trg_fd);
		//exit(6);
		throw io_error();
	}

	if (memcpy(p, rec, size) < 0) {
		cerr << "mmap_write error: couldn't memcpy() for \"" << path << "\" file\n";
		close(trg_fd);
		//exit(8);
		throw std::exception();
	}

	if (munmap(p, size) < 0) {
		cerr << "mmap_write error: couldn't munmap() for \"" << path << "\" file\n";
		close(trg_fd);
		//exit(10);
		throw std::exception();
	}
 }

 } // namespace lvv

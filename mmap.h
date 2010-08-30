
	// mmap wrapper 

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

void * mmap_read  ( const char *name,  int flags=MAP_SHARED)   {

	int 	src_fd = open(name, O_RDONLY);
	//int 	src_fd = open(name, O_RDWR);

	if (src_fd  < 0) {
		cerr  << "mmap_read error: couldn't open  \"" << name << "\"  file\n";
		//exit(1);
		throw no_file();
	}
	
	struct stat sb;

	if (fstat(src_fd, &sb) < 0) {
		cerr << "mmap_read error: couldn't stat  \"" << name << "\"   file\n";
		close(src_fd);
		throw io_error();
		//exit(3);
	}

	//void *p =  mmap(NULL, sb.st_size , PROT_READ | PROT_WRITE , flags, src_fd, 0);
	void *p =  mmap(NULL, sb.st_size , PROT_READ, flags, src_fd, 0);

	if  ( p == MAP_FAILED ) {
		cerr  << "mmap_read error: couldn't mmap  \"" << name << "\"  file\n";
		close(src_fd);
		//exit(5);
		throw io_error();
	}

	return p;
 }

template<typename T>    T&   mmap_read(const char* name, int flags=MAP_SHARED)     { return  *(T*)mmap_read(name, flags); };


			template<typename T>
void	mmap_write(const char* name, T &obj, size_t size=sizeof(T)) {

	unlink(name);

	int	trg_fd = open(name, O_CREAT | O_RDWR, S_IRWXU);
	if (trg_fd  < 0) {
		cerr  << "mmap_write error: couldn't open  \"" << name << "\"  file\n";
		//exit(2);
		throw open_error();
	}

	if (ftruncate(trg_fd, size) < 0) {
		cerr << "mmap_write error: couldn't allocate space for  \"" << name << "\" file\n";
		close(trg_fd);
		//exit(4);
		throw no_free_space();
	}


	void *p = mmap(NULL, size, PROT_WRITE, MAP_SHARED, trg_fd, 0);
	if ( p == MAP_FAILED ) {
		cerr << "mmap_write error: couldn't mmap \"" << name << "\" file\n";
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
		cerr << "mmap_write error: couldn't memcpy() for \"" << name << "\" file\n";
		close(trg_fd);
		//exit(8);
		throw exception();
	}

	if (munmap(p, size) < 0) {
		cerr << "mmap_write error: couldn't munmap() for \"" << name << "\" file\n";
		close(trg_fd);
		//exit(10);
		throw exception();
	}
 }

 } // namespace lvv

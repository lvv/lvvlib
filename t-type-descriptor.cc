 #include <iostream>
 #include <lvv/meta.h>
	using lvv::type_descriptor;

 int main() {
     std::cout
		<< type_descriptor<int>() << "\n"
		<< type_descriptor<unsigned>() << "\n"
		<< type_descriptor<unsigned char *>() << "\n"
		<< type_descriptor<char *>() << "\n"
		<< type_descriptor<float>() << "\n"
		<< type_descriptor<long const * &>() << "\n"
		<< type_descriptor<short[10]>() << "\n"
		<< type_descriptor<volatile int>() << "\n"
		<< type_descriptor<const volatile long *&>() << "\n"
		<< type_descriptor<const volatile long *const&>() << std::endl;


     return 0;
 }

